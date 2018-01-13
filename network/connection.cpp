#include "connection.h"
#include <QtNetwork>

namespace network {

Connection::Connection()
{
    /*tcpSocket = new QTcpSocket(this);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);

    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
               this, &Connection::displayError);*/


    /* this code idk, copied it from http://doc.qt.io/qt-5/qtnetwork-fortuneclient-client-cpp.html
       seems that manager is of use, TODO see what is its actual role in network connection*/
    QNetworkConfigurationManager manager;
      if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
      {
          // Get saved network configuration
          QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
          settings.beginGroup(QLatin1String("QtNetwork"));
          const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
          settings.endGroup();

          // If the saved network configuration is not currently discovered use the system default
          QNetworkConfiguration config = manager.configurationFromIdentifier(id);
          if ((config.state() & QNetworkConfiguration::Discovered) !=
              QNetworkConfiguration::Discovered)
          {
              config = manager.defaultConfiguration();
          }

          networkSession = new QNetworkSession(config, this);
          connect(networkSession, &QNetworkSession::opened, this, &Connection::sessionOpened);

          networkSession->open();
      }

}

void Connection::host()
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Connection::handleNewConnection);


        QHostAddress ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address())
            {
                ipAddress = ipAddressesList.at(i);
                break;
            }
        }

        if (!tcpServer->listen(ipAddress,55000))
        {
            qDebug() << tcpServer->errorString();
            //tcpServer->close();
            return;
        }

        qDebug() << "The server is running on\n\nIP: " <<  ipAddress.toString()
                 <<" \nport: " <<tcpServer->serverPort();

}

void Connection::handleNewConnection()
{
     qDebug() <<"new connection!";
     QByteArray block;
     QDataStream out(&block, QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_9);

     QString sendIt("10");

     qDebug()<<"will now send " <<sendIt;

     out << sendIt;

     tcpSocket = tcpServer->nextPendingConnection();

     in.setDevice(tcpSocket);
     in.setVersion(QDataStream::Qt_5_9);

     connect(tcpSocket, &QIODevice::readyRead, this, &Connection::readHost);
     connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                this, &Connection::displayError);

     tcpSocket->write(block);

     qDebug()<<"will now emit start game signal";
     emit startGameSignal("HOST");
     //tcpSocket->disconnectFromHost();
}

void Connection::joinHost(QString hostName,
                          int port)
{
    tcpSocket = new QTcpSocket(this);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);

    connect(tcpSocket, &QIODevice::readyRead, this, &Connection::readHost);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
               this, &Connection::displayError);

    tcpSocket->connectToHost((QString)hostName,
                             port);
}

void Connection::readHost()
{
    qDebug() <<"readHost";
    in.startTransaction();

    QString message;
    in >> message;

    if (!in.commitTransaction())
    {   qDebug() << "error occured during transaction";
        return;
    }

    qDebug() << message;

    int messageInt = message.toInt();
    if(messageInt>=0 && messageInt<=7)
        emit receiveAction((game::user_action)messageInt);

    if(messageInt==10)
        emit startGameSignal(QString("CLIENT"));

}

void Connection::sendAction(game::user_action a)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    qDebug()<<"will now send " <<QString::number(int(a));

    out << QString::number(int(a));

    tcpSocket->write(block);
}

void Connection::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                                    "host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() <<"The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.";
        break;
    default:
       qDebug() << "The following error occurred: " <<
                                 tcpSocket->errorString();
    }
}

void Connection::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

Connection::~Connection()
{
    tcpSocket->disconnectFromHost();
    tcpServer->close();
    tcpSocket->close();
    delete tcpSocket;
}

} //network
