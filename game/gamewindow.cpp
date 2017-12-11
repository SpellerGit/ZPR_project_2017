#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <memory>
#include <windows.h>
#include "gamewindow.h"
#include "ui_gamewindow.h"

namespace game {
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);


    scene->installEventFilter(this);
    QObject::connect(ui->exitButton, SIGNAL (released()), this, SLOT (handleExit()));

}

void GameWindow::updateDisplay()
{
     qDebug() <<"update display on window";
     gdata->player->setPos(gdata->player->posX,gdata->player->posY);

     if(gdata->bullet!=nullptr)
     gdata->bullet->setPos(gdata->bullet->posX,gdata->bullet->posY);

     /*Potentially this way we might try to keep many bullet*/
     /*for (int i=0; i<gdata->items.size(); i++ )
     {
          gdata->items[i].setPos(gdata->items[i].posX,gdata->items[i].posY);
     }*/
}

QGraphicsScene * GameWindow::getScenePointer() const
{
    return scene;
}

void GameWindow::setData(std::shared_ptr<GameData> gamedata)
{
    qDebug() <<"setDATA";
    gdata = gamedata;
    if(gdata->background==nullptr)
        qDebug() <<"nullptr";
    scene->addItem(gdata->background);
    scene->addItem(gdata->player);
}

void GameWindow::showEvent(QShowEvent *)
{
    qDebug() << "showEvent";
}

bool GameWindow::eventFilter(QObject *target, QEvent *event)
{
 qDebug() << event->type();
    if (target == scene)
      {
        switch (event->type()) //formating......
        {
        case QEvent::GraphicsSceneMousePress:
        {
            QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
            const QPointF position = me->pos();
            gdata->setShootingPos(position.x(),position.y()); //should this be here?
            gdata->addBullet();
            scene->addItem(gdata->bullet);
            return true;
        }
        case QEvent::GraphicsSceneMouseMove:
        {

        }
        case QEvent::KeyPress:
        {
            QKeyEvent * key = static_cast<QKeyEvent*>(event);
            switch (key->key())
            {
                case Qt::Key_A:
                     gdata->action = MOVE_LEFT;
                     break;
                case Qt::Key_D:
                     gdata->action = MOVE_RIGHT;
                     break;
                case Qt::Key_W:
                     gdata->action = JUMP;
                     break;
                default:
                     break;
            }
            return true;
        }
        default:
            return false;
         }
      }
    else
    return GameWindow::eventFilter(target, event);
}

void GameWindow::handleExit()
{
   this->close();
}

GameWindow::~GameWindow()
{
    qDebug() << "dstry";
    delete ui;
}

} //namespace game
