#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QPolygon>
#include <QTimer>
#include <windows.h>

class player: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    player(QObject *parent = 0);
signals:
    //сигнал для создания пули
    void signalBullet(QPointF startPos, QPointF endPos);

    //сигнал на завершение игры
    void signalCheckGameOver();
    void signalCheckWin();
public slots:
    //слот для получения инфы о положении курсора
    void slotTarget(QPointF point);

    //слот для обработки разрешения стрельбы
    void slotShot(bool shot_);
private slots:
    void slotGameTimer(); //игровой слот
    void slotBulletTimer(); //слот для пули
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    bool shot_;
    QTimer *bulletTimer; //таймер пули
    QTimer *gameTimer; //игровой таймер
    QPointF target; //положение курсора
};

#endif // PLAYER_H
