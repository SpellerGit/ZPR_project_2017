#include <QDebug>
#include <QImage>
#include "gamewindow.h"
#include "ui_gamewindow.h"

namespace game {
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QImage image(":/images/image1.jpg");
    if(image.isNull())
        qDebug() <<"Could not load the file!";
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image,0));
    QGraphicsScene * scene = new QGraphicsScene(this);
    scene->addItem(item);
    ui->gameView->setScene(scene);

    QObject::connect(ui->exitButton, SIGNAL (released()), this, SLOT (handleExit()));

}

void GameWindow::handleExit()
{
   this->close();
}

GameWindow::~GameWindow()
{
    delete item;
    qDebug() << "dstry";
    delete ui;
}

} //namespace game
