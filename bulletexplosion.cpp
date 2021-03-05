#include "bulletexplosion.h"


bulletExplosion::bulletExplosion(QPointF point, QObject *parent):
    QObject(parent), QGraphicsItem()
{
    this->setPos(point); //установка позиции взрыва
    currentFrame = 0;
    spriteExplosion = new QPixmap(":/explosion_sheet.png");

    explosionTimer = new QTimer();
    connect(explosionTimer, &QTimer::timeout, this, &bulletExplosion::nextFrame);
    explosionTimer->start(25);
}

int bulletExplosion::type() const
{
    return Type;
}

void bulletExplosion::nextFrame()
{
    currentFrame += 20; //движение коодинаты х для следующего кадра
    if (currentFrame >= 300)
        this->deleteLater(); //удаление объекта, когда кончились кадры
    else
        this->update(-10, -10, 20, 20); //обновление граф. объекта
}

void bulletExplosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //отрисовка 1 кадра взрыва
    painter->drawPixmap(-10, -10, *spriteExplosion, currentFrame, 0, 20, 20);
}

QRectF bulletExplosion::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}
