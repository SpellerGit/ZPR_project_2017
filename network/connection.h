#ifndef CONNECTION_H
#define CONNECTION_H

#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include "game/movingitem.h"

namespace network{

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    ~Connection();
    void host();
    void joinHost(QString name,
                  int port);
public slots:
    void sendAction(game::user_action a);

private slots:
    void readHost();
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void handleNewConnection();

signals:
    void startGameSignal(QString type);
    void receiveAction(game::user_action a);

private:
    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QNetworkSession *networkSession = nullptr;
    //QString hostName=nullptr;
    //int port;
};

} // network

#endif // CONNECTION_H
