#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <bulletexplosion.h>

class bullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    bullet(QPointF startPos, QPointF endPos, QObject *parent = 0);

    //установка callBack функции
    void setCallBackFunc(void (*func)(QGraphicsItem *item));
private:
    //объявление сигнатуры callBack функции
    void (*callBackFunc)(QGraphicsItem *item);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timerBullet;
    QGraphicsItem *hero;
private slots:
    void slotTimerBullet();
};

#endif // BULLET_H
