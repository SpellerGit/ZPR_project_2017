#ifndef GAMELOBBY_H
#define GAMELOBBY_H

#include <QWidget>
#include <memory>
#include "network/connection.h"

namespace Ui {
class GameLobby;
}

class GameLobby : public QWidget
{
    Q_OBJECT
public:
    explicit GameLobby(QWidget *parent = 0);
    ~GameLobby();
    void setConnection(std::shared_ptr<network::Connection> con);

private slots:
    void joinGame();
    void hostGame();

private:
    std::shared_ptr<network::Connection> connection;
    Ui::GameLobby* ui;
};


#endif // GAMELOBBY_H
