#include "customscene.h"

customScene::customScene(QObject *parent) :
    QGraphicsScene()
{
}

void customScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalTargetCoordinate(event->scenePos());
}

void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(true);
}

void customScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalShot(false);
}
