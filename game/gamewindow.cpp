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

   // QImage image = QImage(":/images/image1.png");
  //  image2 = QImage(":/images/image3.png");
  //  if(image.isNull())
   //     qDebug() <<"Could not load the file!";
   // QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(image,0));
  //  item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2,0));
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);
   // scene->addItem(item);
  //  scene->addItem(item2);
   // item2->setPos(QPointF(300,600));


    scene->installEventFilter(this);
    QObject::connect(ui->exitButton, SIGNAL (released()), this, SLOT (handleExit()));
  //  QTimer::singleShot(1000, this, SLOT(showFullScreen()));
  //  ui->gameView->fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);

}

void GameWindow::update()
{   //do smth with this...
     qDebug() <<"update display on window";
     if(gdata->player!=nullptr)
     gdata->player->setPos(gdata->player->posX,gdata->player->posY); // ::thinking::
     else
         qDebug() <<"is null";
}

QGraphicsScene * GameWindow::getScenePointer() const
{
    return scene;
}

void GameWindow::setData(std::shared_ptr<GameData> gamedata)
{
    gdata = gamedata;
    scene->addItem(gdata->background);
    scene->addItem(gdata->player);
    scene->update();
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
          /*  qDebug() << "PRESS";
            QGraphicsSceneMouseEvent * me = static_cast<QGraphicsSceneMouseEvent*>(event);
            const QPointF position = me->scenePos();
            item2->setPos(QPointF(position.x(),position.y()));
            qDebug() << me->scenePos();
            return true;*/
        }
        case QEvent::GraphicsSceneMouseMove:
        {
            /*QGraphicsSceneMouseEvent * me = static_cast<QGraphicsSceneMouseEvent*>(event);
            //const QPointF position = me->pos();
           // qDebug() << me2->scenePos();*/
           // return true;
        }
        case QEvent::KeyPress:
        {
            //qDebug() << "Pressed key button!";
            //const QPointF position2 = item2->scenePos();
            QKeyEvent * key = static_cast<QKeyEvent*>(event);
            switch (key->key())
            {
              /*  case Qt::Key_W:
                    item2->setPos(QPointF(position2.x(),position2.y()-2));
                     break;
                case Qt::Key_S:
                    item2->setPos(QPointF(position2.x(),position2.y()+2));
                     break;*/
                case Qt::Key_A:
                   // item2->setPos(QPointF(position2.x()-4,position2.y()));
                     gdata->action = MOVE_LEFT;
                     gdata->player->setPos(100,100);
                     break;
                case Qt::Key_D:
                   // item2->setPos(QPointF(position2.x()+4,position2.y()));
                     gdata->action = MOVE_RIGHT;
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
    //or maybe rather throw exception that will delete loop?
    qDebug() << "dstry";
    delete ui;
}

} //namespace game
