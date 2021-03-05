#include "player.h"
#include "game.h"
#include <math.h>
#include <algorithm>

static double twoPi = 2.0 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += twoPi;
    while (angle > twoPi)
        angle -= twoPi;
    return angle;
}

player::player(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setTransformOriginPoint(25, 25);
    setRotation(0); //дефолтный разворот игрока

    target = QPointF(0, 0); //начальное положение курсора
    shot_ = false;

    gameTimer = new QTimer(); //инициализация игрового таймера

    //подключение сигнала от таймера к слоту обработки этого таймера
    connect(gameTimer, &QTimer::timeout, this, &player::slotGameTimer);
    gameTimer->start(5); //запуск таймера

    bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, this, &player::slotBulletTimer);
    bulletTimer->start(1000/6); //6 выстрелов в секунду
}

void player::slotTarget(QPointF point)
{
    //определение расстояния до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    //определение угла поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = twoPi - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

    //в зависимости где (справа\слева) находится курсор устанавливаем направление поворота героя
    if (angleToTarget >= 0 && angleToTarget < M_PI)
    {
        //поворот налево
        setRotation(rotation() - angleToTarget * 180 / M_PI);
    }
    else if (angleToTarget <= twoPi && angleToTarget > M_PI)
    {
        //поворот направо
        setRotation(rotation() + (angleToTarget - twoPi) * (-180) / M_PI);
    }
}

void player::slotGameTimer()
{
    //передвижения игрока
    if (GetAsyncKeyState('A'))
    {
        this->setX(this->x() - 5);
        if(!scene()->collidingItems(this).isEmpty())
        {
            this->setX(this->x() + 5);
        }
    }
    if (GetAsyncKeyState('D'))
    {
        this->setX(this->x() + 5);
        if(!scene()->collidingItems(this).isEmpty())
        {
            this->setX(this->x() - 5);
        }
    }
    if (GetAsyncKeyState('W'))
    {
        this->setY(this->y() - 5);
        if(!scene()->collidingItems(this).isEmpty())
        {
            this->setY(this->y() + 5);
        }
    }
    if (GetAsyncKeyState('S'))
    {
        this->setY(this->y() + 3);
        if(!scene()->collidingItems(this).isEmpty())
        {
            this->setY(this->y() - 5);
        }
    }

    //проверка выхода за границы поля
    if (this->x() - 70 < 0)
    {
        this->setX(70);
    }
    if (this->x() + 70 > 1280)
    {
        this->setX(1280 - 70);
    }
    if (this->y() - 70 < 0)
    {
        this->setY(70);
    }
    if (this->y() + 70 > 720)
    {
        this->setY(720 - 70);
    }

    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));

    //определение угла поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = twoPi - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

    //в зависимости где (справа\слева) находится курсор устанавливаем направление поворота героя
    if (angleToTarget >= 0 && angleToTarget < M_PI)
    {
        //поворот налево
        setRotation(rotation() - angleToTarget * 180 / M_PI);
    }
    else if (angleToTarget <= twoPi && angleToTarget > M_PI)
    {
        //поворот направо
        setRotation(rotation() + (angleToTarget - twoPi) * (-180) / M_PI);
    }

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                               << mapToScene(0, 0)
                                                               << mapToScene(-1, -1)
                                                               << mapToScene(1, -1));
    foreach (QGraphicsItem *item, foundItems)
    {
        if (item == this)
            continue;
        if (std::find(game::targets.begin(), game::targets.end(), item) != game::targets.end())
        {
            emit signalCheckGameOver();
        }
    }
}

void player::slotBulletTimer()
{
    if (shot_)
    {
        emit signalBullet(mapToScene(0, -35), target);
    }
}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(QRectF(0, 0, 50, 50), QImage(":/player.png"));

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF player::boundingRect() const
{
    return QRectF(-5, -5, 60, 60);
}

QPainterPath player::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void player::slotShot(bool shot)
{
    this->shot_ = shot; //получение разрешения/запрета на стрельбу
}
