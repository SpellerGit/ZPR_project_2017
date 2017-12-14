#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <memory>
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
     checkCollisions(); //not so clean looking doing it here i suppose

    // qDebug() <<"update display on window";
     gdata->player->setPos(gdata->player->posX,gdata->player->posY);

    // if(gdata->bullet!=nullptr)
    // gdata->bullet->setPos(gdata->bullet->posX,gdata->bullet->posY);

     if(!gdata->bullets.empty())
         for(auto &i : gdata->bullets)
         {
             i->setPos(i->posX,i->posY);
         }

     /*Potentially this way we might try to keep many bullet*/
     /*for (int i=0; i<gdata->items.size(); i++ )
     {
          gdata->items[i].setPos(gdata->items[i].posX,gdata->items[i].posY);
     }*/
}

void GameWindow::checkCollisions()
{
     //what if there are multiple collisions?
     //only collision in y axis for now
     //also make it look cleaner in future
    auto itemCollidingPlayer = scene->collidingItems(gdata->player);

    if(gdata->player->speedY>0)
    if(!itemCollidingPlayer.empty())
    {
        for(auto i : itemCollidingPlayer)
        {
            if (i != gdata->background)
            {
                qDebug()<<"collision detected!";
                qDebug()<<"/";
                qDebug()<<"/";
                qDebug()<<"/";
                qDebug()<<"/";


                if(gdata->player->y()+gdata->player->boundingRect().height()>i->y()
                && gdata->player->y()+gdata->player->boundingRect().height()<i->y()+25
                && gdata->player->y()+gdata->player->boundingRect().height()<i->y()+i->boundingRect().height())
                {
                    gdata->player->speedY=0;
                    gdata->player->posY=
                    i->y()-gdata->player->boundingRect().height()+1;
                    //Why is there +1? Because if we dont add+1, then in next frame there will not be any
                    //collisions detected, and player will go down again, then collision will be detected and player
                    //will go back up. In other words player would oscilate up and down.
                }
               else if(i->y()+i->boundingRect().height()>gdata->player->y()
                    && i->y()+i->boundingRect().height()<gdata->player->y()+25)
                     //For some reason there is problem with detecting collisions when moving up
                     //It seems that collision would not be detected until Y speed eqauls 0
                {
                    qDebug() << " UPSIDE !";
                    gdata->player->speedY=0;
                    gdata->player->posY=//700;
                         i->y()+i->boundingRect().height();

               }
                else if(gdata->player->x()<i->x())
                {
                    gdata->player->speedX=0;
                    gdata->player->posX=
                        i->x()-gdata->player->boundingRect().width();
                    qDebug() <<"collision x RIGHT";
                }
                else if(gdata->player->x()>i->x())
                {
                    qDebug() <<"collision x LEFT";
                    gdata->player->speedX=0;
                    gdata->player->posX=
                    i->x()+i->boundingRect().width();
                }


            }
        }
    }
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
    scene->addItem(gdata->background); //view->addBackground method or something like that
    scene->addItem(gdata->player);

    for(auto &i : gdata->tiles)
    {
        scene->addItem(i);
        i->setPos(i->posX,i->posY);
    }
}

void GameWindow::showEvent(QShowEvent *)
{
    qDebug() << "showEvent";
}

bool GameWindow::eventFilter(QObject *target, QEvent *event)
{
// qDebug() << event->type();
    if (target == scene)
      {
        switch (event->type())
        {
        case QEvent::GraphicsSceneMousePress:
        {
            QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
            const QPointF position = me->scenePos();
            movingItem * bullet = gdata->addBullet(position.x(),position.y()); //shoudl this be here
            scene->addItem(bullet);
            bullet->setPos(gdata->player->posX,gdata->player->posY);
            gdata->bullets.push_back(bullet);
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
                case Qt::Key_Space:
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
