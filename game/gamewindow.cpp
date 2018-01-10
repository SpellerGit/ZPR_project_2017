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
     checkCollisions();

    // gdata->player->setPos(gdata->player->posX,gdata->player->posY);


     if(!gdata->bullets.empty())
         for(auto &i : gdata->bullets)
         {
             i->setPos(i->x(),i->y());
         }
}

void GameWindow::checkCollisions()
{
   // qDebug() << "check with x speed " << gdata->player->speedX ;

    float vx = (float)gdata->player->speedX;    //nice cast btw
    float vy = (float)gdata->player->speedY;
    float normalisedX =0;
    float normalisedY =0;

    /**Normalisation**\
     * We want to be checking each pixel traveled, so we must be moving per 1 pixel, therefore
     * we normalise velocity values to max 1*/

    if(abs(vx)>=abs(vy))
    {
        normalisedX=vx/abs(vx);
        normalisedY=vy/abs(vx);
    }
    else
    {
        normalisedY=vy/abs(vy);
        normalisedX=vx/abs(vy);
    }

    float movedX=0;
    float movedY=0;

    int startPosX = gdata->player->x();
    int startPosY = gdata->player->y();

    //qDebug() << "to while";
    while(abs(movedX)<abs(vx) || abs(movedY)<abs(vy))
    {
        //qDebug() << "movedX " << abs(movedX) << " vx " << abs(vx) << " movedY " << abs(movedY) << " vy " <<abs(vy);
        movedX+=normalisedX;
        movedY+=normalisedY;

        int posX = startPosX+movedX; // caution : (int)float
        int posY = startPosY+movedY;

        gdata->player->setPos(posX,posY);

        //Collision checking

        auto itemCollidingPlayer = scene->collidingItems(gdata->player);

        if(!itemCollidingPlayer.empty())
        {
            for(auto i : itemCollidingPlayer)
            {
              //  qDebug() << "collision detected ||| tile loc " << i->y() << " player ovrall loc " << gdata->player->y()+gdata->player->boundingRect().height() -1;
                if (i->y()==gdata->player->y()+gdata->player->boundingRect().height() - 1)
                {
                    gdata->player->speedY=0;
                    vy=0;
                    normalisedY=0;
                    gdata->player->setPos(gdata->player->x(),  gdata->player->y()-1);
                }
                else if (i->y()+i->boundingRect().height()==gdata->player->y() + 1)
                {
                    gdata->player->speedY=0;
                    vy=0;
                    normalisedY=0;
                    gdata->player->setPos(gdata->player->x(),  gdata->player->y()+1);
                }
                else if (i->x()==gdata->player->x()+gdata->player->boundingRect().width() - 1)
                {
                    gdata->player->speedX=0;
                    vx=0;
                    normalisedX=0;
                    gdata->player->setPos(gdata->player->x()-1,gdata->player->y());
                }
                else if (i->x()+i->boundingRect().width()==gdata->player->x() + 1)
                {
                    gdata->player->speedX=0;
                    vx=0;
                    normalisedX=0;
                    gdata->player->setPos(gdata->player->x()+1,gdata->player->y());
                }
            }
        }

    }



    /** TRY TO DO SAME FOR BULLETS, L8R CLEAR REDUNDANT CODE**/



    // qDebug() << "check with x speed " << gdata->player->speedX ;
    if(!gdata->bullets.empty())
        for(auto &i : gdata->bullets)
        {
            float vx = (float)i->speedX;    //nice cast btw
            float vy = (float)i->speedY;
            float normalisedX =0;
            float normalisedY =0;

             /**Normalisation**\
              * We want to be checking each pixel traveled, so we must be moving per 1 pixel, therefore
              * we normalise velocity values to max 1*/

            if(abs(vx)>=abs(vy))
            {
                normalisedX=vx/abs(vx);
                normalisedY=vy/abs(vx);
            }
            else
            {
                normalisedY=vy/abs(vy);
                normalisedX=vx/abs(vy);
            }

            float movedX=0;
            float movedY=0;

            int startPosX = i->x();
            int startPosY = i->y();


             //qDebug() << "to while";
            while(abs(movedX)<abs(vx) || abs(movedY)<abs(vy))
            {
                 //qDebug() << "movedX " << abs(movedX) << " vx " << abs(vx) << " movedY " << abs(movedY) << " vy " <<abs(vy);
                movedX+=normalisedX;
                movedY+=normalisedY;

                int posX = startPosX+movedX; // caution : (int)float
                int posY = startPosY+movedY;

                i->setPos(posX,posY);

                 //Collision checking

                auto itemCollidingBullet = scene->collidingItems(i);

                if(!itemCollidingBullet.empty())
                {
                    for(auto j : itemCollidingBullet)
                    {
                        if(dynamic_cast<movingItem*>(j)->destroyed())
                            scene->removeItem(j);
                    }
                    i->destroyed();
                    scene->removeItem(i);
                    break;
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
    gdata = gamedata;

    ui->gameView->setBackgroundBrush(QPixmap(":/images/background1.bmp"));
    scene->addItem(gdata->player);

    for(auto &i : gdata->tiles)
    {
        scene->addItem(i);
        i->setPos(i->posX,i->posY);
    }
}

bool GameWindow::eventFilter(QObject *target, QEvent *event)
{
   //  qDebug() << event->type();
    if (target == scene)
    {
        switch (event->type())
        {
            case QEvent::GraphicsSceneMousePress:
            {
                QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
                shoot(me);
                return true;
            }
            case QEvent::KeyPress:
            {
                QKeyEvent * key = static_cast<QKeyEvent*>(event);
                switch (key->key())
                {
                    case Qt::Key_A:
                         gdata->setAction(MOVE_LEFT);
                         break;
                    case Qt::Key_D:
                         gdata->setAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Space:
                         gdata->setAction(JUMP);
                         break;
                    default:
                         break;
                }
                return true;
            }
            case QEvent::KeyRelease:
            {
                QKeyEvent * key = static_cast<QKeyEvent*>(event);
                switch (key->key())
                {
                    case Qt::Key_A:
                         gdata->releaseAction(MOVE_LEFT);
                         break;
                    case Qt::Key_D:
                         gdata->releaseAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Space:
                         gdata->releaseAction(JUMP);
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

void GameWindow::shoot(QGraphicsSceneMouseEvent* event)
{
    const QPointF position = event ->scenePos();
    movingItem * bullet = gdata->addBullet(position.x(),position.y()); //shoudl this be here
    scene->addItem(bullet);
    gdata->bullets.push_back(bullet);
}

void GameWindow::handleExit()
{
   this->close();
}

GameWindow::~GameWindow()
{
    delete ui;
}

} //namespace game
