/********************************************************************************
** GameLobby generated from reading UI file 'gamelobby.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMELOBBY_H
#define UI_GAMELOBBY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameLobby
{
public:
    QPushButton *hostButton;
    QLineEdit *hostAdress;
    QLineEdit *port;
    QPushButton *joinButton;
    QLineEdit *hostNameLine;
    QLineEdit *portLine;

    void setupUi(QWidget *GameLobby)
    {
        if (GameLobby->objectName().isEmpty())
            GameLobby->setObjectName(QStringLiteral("GameLobby"));
        GameLobby->resize(400, 300);
        hostButton = new QPushButton(GameLobby);
        hostButton->setObjectName(QStringLiteral("hostButton"));
        hostButton->setGeometry(QRect(30, 10, 341, 91));
        hostAdress = new QLineEdit(GameLobby);
        hostAdress->setObjectName(QStringLiteral("hostAdress"));
        hostAdress->setGeometry(QRect(100, 130, 251, 31));
        port = new QLineEdit(GameLobby);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(100, 160, 251, 31));
        joinButton = new QPushButton(GameLobby);
        joinButton->setObjectName(QStringLiteral("joinButton"));
        joinButton->setGeometry(QRect(110, 200, 171, 61));
        hostNameLine = new QLineEdit(GameLobby);
        hostNameLine->setObjectName(QStringLiteral("hostNameLine"));
        hostNameLine->setGeometry(QRect(40, 130, 61, 31));
        portLine = new QLineEdit(GameLobby);
        portLine->setObjectName(QStringLiteral("portLine"));
        portLine->setGeometry(QRect(40, 160, 61, 31));

        retranslateUi(GameLobby);

        QMetaObject::connectSlotsByName(GameLobby);
    } // setupUi

    void retranslateUi(QWidget *GameLobby)
    {
        GameLobby->setWindowTitle(QApplication::translate("GameLobby", "GameLobby", Q_NULLPTR));
        hostButton->setText(QApplication::translate("GameLobby", "Host Serwer", Q_NULLPTR));
        joinButton->setText(QApplication::translate("GameLobby", "Join serwer", Q_NULLPTR));
        hostNameLine->setText(QApplication::translate("GameLobby", "Host name", Q_NULLPTR));
        portLine->setText(QApplication::translate("GameLobby", "Port", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameLobby: public Ui_GameLobby {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMELOBBY_H
