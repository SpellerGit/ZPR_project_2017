#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
//#include <QKeyEvent>
#include "gamewindow.h"
#include "ui_gamewindow.h"

namespace game {
GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    image = QImage(":/images/image1.png");
    image2 = QImage(":/images/image3.png");
    if(image.isNull())
        qDebug() <<"Could not load the file!";
    item = new QGraphicsPixmapItem(QPixmap::fromImage(image,0));
    item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2,0));
    scene = new QGraphicsScene(this);
    scene->addItem(item);
    scene->addItem(item2);
    item2->setPos(QPointF(300,600));

    //this->installEventFilter(this);
    scene->installEventFilter(this);

    ui->gameView->setScene(scene);

    this->showMaximized();

    QObject::connect(ui->exitButton, SIGNAL (released()), this, SLOT (handleExit()));
}


bool GameWindow::eventFilter(QObject *target, QEvent *event)
{

    if (target == scene)
      {
          if (event->type() == QEvent::GraphicsSceneMousePress) //change to switch
          {
              QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
              //const QPointF position = me->pos();
             // QPixmap *pix = new QPixmap(10,10);
             //QGraphicsPixmapItem* item(scene->addPixmap(*pix)); // Save the returned item
            //  QPainter *paint = new QPainter(pix);
             // paint->setPen(*(new QColor(255,34,255,255)));
              const QPointF position = me->scenePos();
             // paint->drawRect(position.x(),position.y(),50,50);
            //  scene->clear();
            //  scene->addItem(item);
            //  QImage image(":/images/image3.png");
            //  item->setPixmap(QPixmap::fromImage(image)); // Added this line
              item2->setPos(QPointF(position.x(),position.y()));
              return true;
          }
          else if (event->type() == QEvent::GraphicsSceneMouseMove)
          {
              QGraphicsSceneMouseEvent* me = static_cast<QGraphicsSceneMouseEvent*>(event);
              //const QPointF position = me->pos();
              qDebug() << me->scenePos();
              return true;
          }
         // else if (event->type() == QEvent::KeyPress)
          //{
              //qDebug() << "Pressed key button!";
           //   const QPointF position = item2->scenePos();
            //  QKeyEvent* key = static_cast<QKeyEvent*>(event);
           //   if(key->key()==Qt::Key_W)
            //      item2->setPos(QPointF(position.x(),position.y()+1));
            //  return true;
          //}
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
