#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <customscene.h>
#include <player.h>
#include <bullet.h>
#include <littleEnemy.h>
#include <bigEnemy.h>

static int countOfEnemies;

class game: public QGraphicsView
{
public:
    game(QWidget *parent=0);
    customScene *scene;
    static QList<QGraphicsItem *> targets;
    static void setCount(int i) {countOfEnemies = i;};
    static int getCount() {return countOfEnemies;};
private slots:
    void slotBullet(QPointF startPos, QPointF endPos);
    void slotGameOver();
    void slotWin();
private:
    static void slotHitTarget(QGraphicsItem *item); //callBack функция
    void drawWalls();
    void spawnEnemies();
    player *myPlayer;
    bigEnemy *newBigEnemy1;
    bigEnemy *newBigEnemy2;
    littleEnemy *newLittleEnemy1;
    littleEnemy *newLittleEnemy2;
    littleEnemy *newLittleEnemy3;
    littleEnemy *newLittleEnemy4;
};

#endif // GAME_H
