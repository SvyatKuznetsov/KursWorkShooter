#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class customScene: public QGraphicsScene
{
    Q_OBJECT
public:
    customScene(QObject *parent = 0);
signals:
    //сигнал для передачи координат положения курсора мыши
    void signalTargetCoordinate(QPointF point);

    //сигнял, разрешающий на стрельбу
    void signalShot(bool shot);
private:
    //в этой функции производится отслеживание положения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //функции на реагирования кликов мышки
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
