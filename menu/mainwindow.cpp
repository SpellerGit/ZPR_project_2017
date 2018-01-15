#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game/gamemanager.h"
#include <memory>
#include <QtWidgets>
#include <QWidget>
#include <QDebug>
#include <QCoreApplication>
#include <QObject>
#include <QApplication>
#include <QString>

//Of memory handling with QT objects, per SO (https://stackoverflow.com/questions/19331396/how-does-qt-delete-objects-and-what-is-the-best-way-to-store-qobjects)
//The pattern requires that the composite object
//takes ownership of the children so, as long as the
//parenting has been done, you can be assured that the
//child QObjects will be destroyed when the parent is destroyed.

//Standard practice is to create child objects in heap memory
//and parent them immediately. If you don't parent immediately,
//you can explicitly parent using the setParent() function, or else
//parenting will be done automatically when you add the widget to
//a parent widget, either using addWidget() or addLayout().

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gamedata = nullptr;

    ui->setupUi(this);

    QObject::connect(ui->button1, SIGNAL (released()), this, SLOT (handleButton()));
    QObject::connect(ui->button2, SIGNAL (released()), this, SLOT (handleSelectMap()));
    QObject::connect(ui->hostbutton, SIGNAL (released()), this, SLOT (handleNetwork()));

    connection = std::shared_ptr<network::Connection>(new network::Connection());

}

void MainWindow::handleButton()
{
    this->hide();
    mngr = std::unique_ptr<game::GameManager>(new game::GameManager());
    if(gamedata==nullptr)
    {
        mngr->startGame();
    }
    else
    {
        mngr->startGame(gamedata);
    }
    qDebug() << "clicked Button1";
}

void MainWindow::handleSelectMap()
{

    mngr = std::unique_ptr<game::GameManager>(new game::GameManager());
    gamedata = std::shared_ptr<game::GameData>(new game::GameData()); // i used the overloaded contructor
    gamedata->loadmap();

    qDebug() << "clicked SelectMap";

}

void MainWindow::handleNetwork()
{
    this->hide();
    mngr = std::unique_ptr<game::GameManager>(new game::GameManager());
    mngr->setConnection(connection);
    lobby = std::unique_ptr<GameLobby>(new GameLobby());
    lobby->setConnection(connection);
}


MainWindow::~MainWindow()
{
     qDebug() << "dstry main";
     delete ui;
}


