#include "gamelobby.h"
#include "ui_gamelobby.h"

GameLobby::GameLobby(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::GameLobby)
{
      ui->setupUi(this);
      this->show();
      ui->hostNameLine->setReadOnly(true);
      ui->portLine->setReadOnly(true);

      QObject::connect(ui->hostButton, SIGNAL (released()), this, SLOT (hostGame()));
      QObject::connect(ui->joinButton, SIGNAL (released()), this, SLOT (joinGame()));

      connection = std::unique_ptr<network::Connection>(new network::Connection());
}

void GameLobby::hostGame()
{
    qDebug() <<"hst";
    connection->host();
}

void GameLobby::joinGame()
{
    qDebug() <<"jin " << ui->hostAdress->text() << " prt " <<ui->port->text().toInt();
    connection->joinHost(ui->hostAdress->text(),ui->port->text().toInt());
}

GameLobby::~GameLobby()
{
    delete ui;
}

