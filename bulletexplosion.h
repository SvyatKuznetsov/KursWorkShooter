#ifndef BULLETEXPLOSION_H
#define BULLETEXPLOSION_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class bulletExplosion: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    bulletExplosion(QPointF point, QObject *parent = 0);
    enum {Type = UserType + 1}; //переопределение типа граф. объекта взрыва, чтоб пуля могла игнорировать этот объект
    int type() const; //переопределение функции для получения типа объекта
private slots:
    void nextFrame(); //слот для перелистывания кадров
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QTimer *explosionTimer; //таймер для анимации взрыва
    QPixmap *spriteExplosion; //спрайт
    int currentFrame; //координата текущего кадра в спрайте
};

#endif // BULLETEXPLOSION_H
