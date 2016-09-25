#include "qwebserver.h"

QWebServer::QWebServer(QObject *parent) : QTcpServer(parent)
{
    if(listen(QHostAddress::Any, 80)) {
        //qDebug() << "Ok";
    } else {
        //qDebug() << "Bad" << errorString();
    }
}

void QWebServer::incomingConnection(int handle)
{
    QTcpSocket* socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

void QWebServer::onReadyRead()
{
    QString response = "HTTP/1.1 200 OK\r\n\r\n%1";
    QString indexpage = "<!DOCTYPE HTML><html><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>WebLauncher</title>"
            "<style> .button { width: 100%; background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center;"
            "text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }</style>"
            "<script>function proceed (ty) {  if (window.XMLHttpRequest) { xmlhttp=new XMLHttpRequest(); } else { xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\"); }"
            "xmlhttp.open(\"POST\",\"?prog=\"+ty,true); xmlhttp.send(); }</script></head><body>";
    QString pastbody = "</body></html>";
    QString buttonTag = "<input type=\"button\" class=\"button\" value=\"%1\" onclick=\"proceed(%2)\">";
    QString timerTag = "<input type=\"button\" class=\"button\" value=\"Start Timer\" onclick=\"proceed('t')\">";
    //read all
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    QString request = socket->readAll();
    QStringList ftr = request.split(" ");
    if(ftr.at(0) == "POST") {
        //button pushed
        QString post = ftr.at(1);
        QStringList compost = post.split("=");
        QString mun = compost.at(1);
        qint16 numberCom;
        if(mun == "t") {
            emit startingProcess(-1);
        } else {
            numberCom = mun.toInt();
            emit startingProcess(numberCom - 1);
        }
        socket->write(response.arg(mun).toUtf8());
    } else if(ftr.at(1) == "/") {
        //request page
        QString buttonsTags;
        //qDebug() << commands.count();
        //if(commands.count() != 0) {
            for(qint16 q = 1; q <= commands.count(); q++) {
                //qint16 g = q + 1;
                //qDebug() << buttonsTags;
                buttonsTags.append(buttonTag.arg(commands.at(q - 1), QString::number(q)));
                //qDebug() << buttonsTags;
            }
        //}
        //qDebug() << buttonsTags;
        QString page;
        page.append(indexpage);
        if(hasTimer == true) {
            //page.append(timerTag);
        }
        page.append(buttonsTags);
        page.append(pastbody);
        //qDebug() << page;
        socket->write(response.arg(page).toUtf8());
    }

    socket->disconnectFromHost();
}

void QWebServer::onDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    socket->close();
    socket->deleteLater();
}

void QWebServer::setPortListen(quint16 i)
{
    close();
    if(listen(QHostAddress::Any, i)) {
        //qDebug() << "Ok";
    } else {
        //qDebug() << "Bad" << errorString();
    }
}

void QWebServer::setTimer(bool i)
{
    hasTimer = i;
}

void QWebServer::addItem(QString i)
{
    commands.append(i);
    //commands.last() = i;
}

void QWebServer::delItem(qint16 i)
{
    //
}

void QWebServer::delLast()
{
    commands.removeLast();
}
