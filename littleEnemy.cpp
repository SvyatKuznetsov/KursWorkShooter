#include "littleEnemy.h"
#include "game.h"
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

littleEnemy::littleEnemy(QGraphicsItem *target, QObject *parent)
{
    angle_ = 0;
    setRotation(angle_);
    this->target = target;
    health_ = 30;
    maxHealth_ = health_;

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &littleEnemy::slotGameTimer);
    timer->start(30);
}

void littleEnemy::hitEnemy(int damage)
{
    health_ -= damage;
    this->update(QRectF(-10, -30, 50, 85));
    if (health_ <= 0)
    {
        int count = game::getCount();
        game::setCount(--count);
        if (game::getCount() == 0)
        {
            emit signalCheckWin();
        }
        this->deleteLater();
    }
}

QRectF littleEnemy::boundingRect() const
{
    return QRectF(-10, -30, 50, 85);
}

QPainterPath littleEnemy::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void littleEnemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //враг
    painter->drawImage(QRectF(-10, -20, 50, 75), QImage(":/ghost.png"));

    //полоска хп
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(-5, -30, (int) 40 * health_ / maxHealth_, 3);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void littleEnemy::slotGameTimer()
{
    // Определяем расстояние до игрока
    QLineF lineToTarget(QPointF(0, 0), mapFromItem(target, 0, 0));
    // Угол поворота в направлении к игроку
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = twoPi - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

    /* В Зависимости от того, слева или справа находится игрок от врага,
     * устанавливаем направление поворота паука в данном тике таймера
     * Скорость разворота зависит от угла, на который необходимо повернуться пауку
    * */
    if (angleToTarget > 0 && angleToTarget < M_PI)
    {
       // Rotate left
        if (angleToTarget > twoPi / 5)
        {
            angle_ = -15;
        } else if(angleToTarget > M_PI / 10)
        {
            angle_ = -5;
        } else {
            angle_ = -1;
        }
    } else if (angleToTarget <= twoPi && angleToTarget > (twoPi - M_PI)) {
        // Rotate right
        if (angleToTarget < (twoPi - M_PI / 5))
        {
            angle_ = 15;
        }
        else if (angleToTarget < (twoPi - M_PI / 10))
        {
            angle_ = 5;
        }
        else
        {
            angle_ = 1;
        }
    }
    else if (angleToTarget == 0)
    {
        angle_ = 0;
    }

    setRotation(rotation() + angle_); // Разворачиваемся

    if(lineToTarget.length() >= 40)
    {
        if(scene()->collidingItems(this).isEmpty())
        {
            setPos(mapToParent(0, -2));
        }
        else
        {
            setPos(mapToParent(0, 0));
        }
        update(QRectF(-20, -10, 85, 160));
    }

    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-1, -1)
                                                           << mapToScene(1, -1));
    foreach (QGraphicsItem *item, foundItems)
    {
        if (item == this)
        {
            continue;
        }
        if (item == target)
        {
            emit signalCheckGameOver();
        }
    }

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
}

