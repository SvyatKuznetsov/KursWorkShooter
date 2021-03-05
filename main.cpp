#include <QApplication>
#include "game.h"

game *myGame;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    myGame = new game();
    myGame->show();

    return a.exec();
}
