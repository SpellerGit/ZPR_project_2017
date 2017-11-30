/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWindow
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *exitButton;
    QGraphicsView *gameView;

    void setupUi(QWidget *GameWindow)
    {
        if (GameWindow->objectName().isEmpty())
            GameWindow->setObjectName(QStringLiteral("GameWindow"));
        GameWindow->resize(1850, 850);
        verticalLayout = new QVBoxLayout(GameWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        exitButton = new QPushButton(GameWindow);
        exitButton->setObjectName(QStringLiteral("exitButton"));

        verticalLayout->addWidget(exitButton);

        gameView = new QGraphicsView(GameWindow);
        gameView->setObjectName(QStringLiteral("gameView"));

        verticalLayout->addWidget(gameView);


        retranslateUi(GameWindow);

        QMetaObject::connectSlotsByName(GameWindow);
    } // setupUi

    void retranslateUi(QWidget *GameWindow)
    {
        GameWindow->setWindowTitle(QApplication::translate("GameWindow", "Form", Q_NULLPTR));
        exitButton->setText(QApplication::translate("GameWindow", "Exit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameWindow: public Ui_GameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
