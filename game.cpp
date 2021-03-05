#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>

game::game(QWidget *parent)
{
    setCount(6);
    scene = new customScene();
    scene->setSceneRect(0,0,1280,720);

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1280, 720);
    setBackgroundBrush(QBrush(QImage(":/bg.png")));

    //стены
    drawWalls();

    myPlayer = new player();
    myPlayer->setPos(100, 200);
    myPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    myPlayer->setFocus();
    scene->addItem(myPlayer);

    //кастомный прицел в игре
    QCursor cursor = QCursor(QPixmap(":/aim.png"));
    setCursor(cursor);

    setMouseTracking(true); //разрешения отслеживания мыши без необходимости нажатия на кнопку мыши
    connect(scene, &customScene::signalTargetCoordinate, myPlayer, &player::slotTarget);
    connect(scene, &customScene::signalShot, myPlayer, &player::slotShot);
    connect(myPlayer, &player::signalBullet, this, &game::slotBullet);
    connect(myPlayer, &player::signalCheckGameOver, this, &game::slotGameOver);
    connect(myPlayer, &player::signalCheckWin, this, &game::slotWin);

    spawnEnemies();

    show();
}

void game::slotBullet(QPointF startPos, QPointF endPos)
{
    bullet *newBullet = new bullet(startPos, endPos);
    newBullet->setCallBackFunc(slotHitTarget);
    scene->addItem(newBullet);
}

void game::slotGameOver()
{
    QMessageBox::warning(this, "GameOver", "Вы были убиты");
    game::close();
    disconnect(scene, &customScene::signalTargetCoordinate, myPlayer, &player::slotTarget);
    disconnect(scene, &customScene::signalShot, myPlayer, &player::slotShot);
    disconnect(myPlayer, &player::signalBullet, this, &game::slotBullet);
    disconnect(myPlayer, &player::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy1, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy1, &bigEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newBigEnemy2, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy2, &bigEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy1, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy1, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy2, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy2, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy3, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy3, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy4, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy4, &littleEnemy::signalCheckWin, this, &game::slotWin);
    myPlayer->deleteLater();
    foreach (QGraphicsItem *target, targets)
    {
        scene->removeItem(target);
        targets.removeOne(target);
        delete target;
    }
}

void game::slotWin()
{
    QMessageBox::warning(this, "GameOver", "Всех убил, красава");
    game::close();
    disconnect(scene, &customScene::signalTargetCoordinate, myPlayer, &player::slotTarget);
    disconnect(scene, &customScene::signalShot, myPlayer, &player::slotShot);
    disconnect(myPlayer, &player::signalBullet, this, &game::slotBullet);
    disconnect(myPlayer, &player::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy1, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy1, &bigEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newBigEnemy2, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newBigEnemy2, &bigEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy1, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy1, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy2, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy2, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy3, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy3, &littleEnemy::signalCheckWin, this, &game::slotWin);
    disconnect(newLittleEnemy4, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    disconnect(newLittleEnemy4, &littleEnemy::signalCheckWin, this, &game::slotWin);
    myPlayer->deleteLater();
    foreach (QGraphicsItem *target, targets)
    {
        scene->removeItem(target);
        targets.removeOne(target);
        delete target;
    }
}

void game::slotHitTarget(QGraphicsItem *item)
{
    foreach (QGraphicsItem *targ, targets)
    {
        if (item == targ)
        {
            enemy *en = qgraphicsitem_cast<enemy *>(targ);
            en->hitEnemy(qrand() % ((3 + 1) - 1) + 1);
        }
    }
}

void game::drawWalls()
{
    scene->addRect(0, 0, 45, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(45, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(135, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(225, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(315, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(405, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(495, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(585, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(675, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(765, 0, 95, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(770, 90, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(770, 180, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(860, 180, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1130, 180, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 0, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 90, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 180, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 270, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 360, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 450, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 540, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1220, 720, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1130, 450, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1130, 540, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(1130, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(770, 450, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(770, 540, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(770, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(860, 450, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(860, 540, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(860, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(0, 630, 45, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(45, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(135, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(225, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(315, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(405, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(495, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(585, 630, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(675, 630, 95, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(320, 270, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(320, 360, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(320, 450, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
    scene->addRect(320, 540, 91, 91, QPen(Qt::NoPen), QBrush(Qt::NoBrush));
}

void game::spawnEnemies()
{
    newBigEnemy1 = new bigEnemy(myPlayer);
    scene->addItem(newBigEnemy1);
    newBigEnemy1->setPos(1020, 150);
    targets.append(newBigEnemy1);

    newBigEnemy2 = new bigEnemy(myPlayer);
    scene->addItem(newBigEnemy2);
    newBigEnemy2->setPos(970, 500);
    targets.append(newBigEnemy2);

    newLittleEnemy1 = new littleEnemy(myPlayer);
    scene->addItem(newLittleEnemy1);
    newLittleEnemy1->setPos(1150, 350);
    targets.append(newLittleEnemy1);

    newLittleEnemy2 = new littleEnemy(myPlayer);
    scene->addItem(newLittleEnemy2);
    newLittleEnemy2->setPos(670, 570);
    targets.append(newLittleEnemy2);

    newLittleEnemy3 = new littleEnemy(myPlayer);
    scene->addItem(newLittleEnemy3);
    newLittleEnemy3->setPos(670, 200);
    targets.append(newLittleEnemy3);

    newLittleEnemy4 = new littleEnemy(myPlayer);
    scene->addItem(newLittleEnemy4);
    newLittleEnemy4->setPos(450, 350);
    targets.append(newLittleEnemy4);

    connect(newBigEnemy1, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newBigEnemy1, &bigEnemy::signalCheckWin, this, &game::slotWin);
    connect(newBigEnemy2, &bigEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newBigEnemy2, &bigEnemy::signalCheckWin, this, &game::slotWin);
    connect(newLittleEnemy1, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newLittleEnemy1, &littleEnemy::signalCheckWin, this, &game::slotWin);
    connect(newLittleEnemy2, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newLittleEnemy2, &littleEnemy::signalCheckWin, this, &game::slotWin);
    connect(newLittleEnemy3, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newLittleEnemy3, &littleEnemy::signalCheckWin, this, &game::slotWin);
    connect(newLittleEnemy4, &littleEnemy::signalCheckGameOver, this, &game::slotGameOver);
    connect(newLittleEnemy4, &littleEnemy::signalCheckWin, this, &game::slotWin);
}

QList<QGraphicsItem *> game::targets;
