#include "connection.h"

#include <QtNetwork>

namespace network {

Connection::Connection()
{
    tcpSocket = new QTcpSocket(this);
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_9);

    connect(tcpSocket, &QIODevice::readyRead, this, &Connection::readHost);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
               this, &Connection::displayError);


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

        if (!tcpServer->listen(QHostAddress(QHostAddress::LocalHost),50000))
        {
            qDebug() << tcpServer->errorString();
            //tcpServer->close();
            return;
        }
        QString ipAddress;
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
        // use the first non-localhost IPv4 address
        for (int i = 0; i < ipAddressesList.size(); ++i)
        {
            if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address())
            {
                ipAddress = ipAddressesList.at(i).toString();
                break;
            }
        }
        // if we did not find one, use IPv4 localhost
        if (ipAddress.isEmpty())
            ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        qDebug() << "The server is running on\n\nIP: " <<  QHostAddress(QHostAddress::LocalHost).toString()
                 <<" \nport: " <<tcpServer->serverPort();
}

void Connection::handleNewConnection()
{
     QByteArray block;
     QDataStream out(&block, QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_9);

     QString * sendIt = new QString("TEST RESPONSE FROM HOST");

     out << sendIt;

     //QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
     /**          very interesting solution btw xD              **/
     if(tcpSocket)
     delete tcpSocket;
     tcpSocket = tcpServer->nextPendingConnection();
     connect(tcpSocket, &QAbstractSocket::disconnected,
             tcpSocket, &QObject::deleteLater);

     tcpSocket->write(block);
     tcpSocket->disconnectFromHost();
     delete sendIt;
}

void Connection::joinHost(QString hostName,
                          int port)
{
    tcpSocket->connectToHost((QString)hostName,
                             port);
}

void Connection::readHost()
{
    in.startTransaction();

    QString Message;
    in >> Message;

    if (!in.commitTransaction())
    {   qDebug() << "error occured during transaction";
        return;
    }

    qDebug() << Message;
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
    tcpServer->close();
    tcpSocket->close();
}

} //network
