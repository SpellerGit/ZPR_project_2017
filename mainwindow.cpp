#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <QtWidgets>
#include <QWidget>
#include <QDebug>
#include <QCoreApplication>
#include <QObject>
#include <QApplication>

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
    ui->setupUi(this);

    qDebug() << "fsfsd";

    QWidget * wdg = new QWidget(this);
    button1 = new QPushButton("some button",wdg);
    setCentralWidget(wdg);

    QObject::connect(button1, SIGNAL (released()), this, SLOT (handleButton()));

}

void MainWindow::handleButton()
{
    qDebug() << "clicked";
}

MainWindow::~MainWindow()
{
    delete ui;
}
