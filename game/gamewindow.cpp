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
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);


    scene->installEventFilter(this);
    QObject::connect(ui->exitButton, SIGNAL (released()), this, SLOT (handleExit()));

}

void GameWindow::updateDisplay()
{
     checkCollisions();

    // gdata->players[i]->setPos(gdata->players[i]->posX,gdata->players[i]->posY);


     ui->gameView->centerOn(gdata->players[0]);

}

void GameWindow::checkCollisions()
{
   // qDebug() << "check with x speed " << gdata->players[i]->speedX ;

    for(auto &j : gdata->players)
    {
        float vx = (float)j->speedX;    //nice cast btw
        float vy = (float)j->speedY;
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

        int startPosX = j->x();
        int startPosY = j->y();

        //qDebug() << "to while";
        while(abs(movedX)<abs(vx) || abs(movedY)<abs(vy))
        {
            //qDebug() << "movedX " << abs(movedX) << " vx " << abs(vx) << " movedY " << abs(movedY) << " vy " <<abs(vy);
            movedX+=normalisedX;
            movedY+=normalisedY;

            int posX = startPosX+movedX; // caution : (int)float
            int posY = startPosY+movedY;

            j->setPos(posX,posY);

            //Collision checking

            auto itemCollidingplayer = scene->collidingItems(j);

            if(!itemCollidingplayer.empty())
            {
                for(auto i : itemCollidingplayer)
                {
                  //  qDebug() << "collision detected ||| tile loc " << i->y() << " players[i] ovrall loc " << j->y()+j->boundingRect().height() -1;
                    if (i->y()==j->y()+j->boundingRect().height() - 1)
                    {
                        j->speedY=0;
                        vy=0;
                        normalisedY=0;
                        j->setPos(j->x(),  j->y()-1);
                    }
                    else if (i->y()+i->boundingRect().height()==j->y() + 1)
                    {
                        j->speedY=0;
                        vy=0;
                        normalisedY=0;
                        j->setPos(j->x(),  j->y()+1);
                    }
                    else if (i->x()==j->x()+j->boundingRect().width() - 1)
                    {
                        j->speedX=0;
                        vx=0;
                        normalisedX=0;
                        j->setPos(j->x()-1,j->y());
                    }
                    else if (i->x()+i->boundingRect().width()==j->x() + 1)
                    {
                        j->speedX=0;
                        vx=0;
                        normalisedX=0;
                        j->setPos(j->x()+1,j->y());
                    }
                }
            }
        }
    }



    /** TRY TO DO SAME FOR BULLETS, L8R CLEAR REDUNDANT CODE**/



    // qDebug() << "check with x speed " << j->speedX ;
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


    ui->gameView->setBackgroundBrush(QPixmap(gdata->background));
    qDebug() << gdata->background;
    for(auto i : gdata->players)
    scene->addItem(i);

    for(auto &i : gdata->tiles)
    {
        scene->addItem(i);
        i->setPos(i->posX,i->posY);
        qDebug() << " Tile added, possition X :" << i->posX << " possition Y: "<< i->posY;
    }
}

bool GameWindow::eventFilter(QObject *target, QEvent *event)
{
    //qDebug() << event->type();//BUG ALLERT: if gamewindow does not have focus, and it acquires focus
    if (target == scene)        //with arrow button, the app will not receive arrow pressed event, but will
    {                           //receive arrow released event hence the app crashes
        switch (event->type())
        {
            case QEvent::GraphicsSceneMousePress:
            {
                QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
                shoot(me,0);
                return true;
            }
            case QEvent::KeyPress:
            {
                QKeyEvent * key = static_cast<QKeyEvent*>(event);
                switch (key->key())
                {
                    case Qt::Key_A:
                         gdata->players[0]->setAction(MOVE_LEFT);
                         break;
                    case Qt::Key_D:
                         gdata->players[0]->setAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Space:
                         gdata->players[0]->setAction(JUMP);
                         break;

                    case Qt::Key_Left:
                         gdata->players[1]->setAction(MOVE_LEFT);
                         break;
                    case Qt::Key_Right:
                         gdata->players[1]->setAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Up:
                         gdata->players[1]->setAction(JUMP);
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
                         gdata->players[0]->releaseAction(MOVE_LEFT);
                         break;
                    case Qt::Key_D:
                         gdata->players[0]->releaseAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Space:
                         gdata->players[0]->releaseAction(JUMP);
                         break;

                    case Qt::Key_Left:
                         gdata->players[1]->releaseAction(MOVE_LEFT);
                         break;
                    case Qt::Key_Right:
                         gdata->players[1]->releaseAction(MOVE_RIGHT);
                         break;
                    case Qt::Key_Up:
                         gdata->players[1]->releaseAction(JUMP);
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

void GameWindow::shoot(QGraphicsSceneMouseEvent* event,
                       int playerNumber)
{
    const QPointF position = event ->scenePos();
    movingItem * bullet = gdata->addBullet(position.x(),position.y(),playerNumber); //shoudl this be here
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
