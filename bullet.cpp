#include "bullet.h"
#include <math.h>

static const double twoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += twoPi;
    while (angle > twoPi)
        angle -= twoPi;
    return angle;
}

bullet::bullet(QPointF startPos, QPointF endPos, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->setRotation(0);
    this->setPos(startPos);

    //определение траектории полута пули
    QLineF lineToTarget(startPos, endPos);

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

    //инициализация полётного таймера
    timerBullet = new QTimer();

    //его подключение к слоту для обработки полета пули
    connect(timerBullet, &QTimer::timeout, this, &bullet::slotTimerBullet);
    timerBullet->start(7);
}

void bullet::setCallBackFunc(void (*func)(QGraphicsItem *))
{
    callBackFunc = func;
}

QRectF bullet::boundingRect() const
{
    return QRectF(0, 0, 10, 20);
}

void bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(QRectF(0, 0, 10, 20), QImage(":/bullet.png"));

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void bullet::slotTimerBullet()
{
    setPos(mapToParent(0, -10));

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                                << mapToScene(0, 0)
                                                                << mapToScene(-1, -1)
                                                                << mapToScene(1, -1));
    //проверка всех элементов
    foreach (QGraphicsItem *item, foundItems)
    {
        if (item == this || item == hero || item->type() == (UserType + 1))
            continue;
        bulletExplosion *newBullerExplosion = new bulletExplosion(this->pos());
        scene()->addItem(newBullerExplosion);
        callBackFunc(item); // вызов callBack функции
        this->deleteLater(); //уничтожение пули
    }

    if(this->x() < 0)
    {
        this->deleteLater();
    }
    if(this->x() > 1280)
    {
        this->deleteLater();
    }
    if(this->y() < 0)
    {
       this->deleteLater();
    }
    if(this->y() > 720)
    {
       this->deleteLater();
    }
}
