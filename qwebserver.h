#ifndef QWEBSERVER_H
#define QWEBSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include <QList>
#include <QStringList>
#include "qcomstring.h"
//#include <QHostAddress>


class QWebServer : public QTcpServer
{
    Q_OBJECT
public:
    QWebServer(QObject *parent = 0);
    //QList<QComString*> commands;
    //QList<QString*> commands;
    QStringList commands;
    bool hasTimer;
    void incomingConnection(int handle);
signals:
    void startingTimer(bool);
    void startingProcess(qint16);
public slots:
    void onReadyRead();
    void onDisconnected();
    void setPortListen(quint16);
    void setTimer(bool);
    void addItem(QString);
    void delItem(qint16);
    void delLast();
};

#endif // QWEBSERVER_H
