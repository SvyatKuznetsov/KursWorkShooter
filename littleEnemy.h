#ifndef LITTLEENEMY_H
#define LITTLEENEMY_H

#include "enemy.h"
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class littleEnemy: public enemy
{
    Q_OBJECT
public:
    littleEnemy(QGraphicsItem *target, QObject *parent = 0);
    void hitEnemy(int damage);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    void signalCheckGameOver();
    void signalCheckWin();
private slots:
    void slotGameTimer();
private:
    QPainterPath shape() const;
    qreal angle_;
    QTimer *timer;
    QGraphicsItem *target;
    int health_;
    int maxHealth_;
};

#endif // LITTLEENEMY_H
