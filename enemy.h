#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QImage>

class enemy: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    virtual ~enemy() = default;

    //функция нанесения урона
    virtual void hitEnemy(int damage) = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};

#endif // ENEMY_H
