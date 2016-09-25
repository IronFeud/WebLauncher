#include "webthread.h"

WebThread::WebThread(QObject *parent) : QObject(parent)
{
    QWebServer *webs = new QWebServer();
    webs->moveToThread(&work);
    connect(webs, SIGNAL(startingProcess(qint16)), this, SLOT(fromWebStartingProcess(qint16)));
    connect(this, SIGNAL(toWebTimer(bool)), webs, SLOT(setTimer(bool)));
    connect(this, SIGNAL(toWebAddItem(QString)), webs, SLOT(addItem(QString)));
    connect(this, SIGNAL(toWebDelLastItem()), webs, SLOT(delLast()));
    work.start();
}

void WebThread::fromGuiTimer(bool i)
{
    emit toWebTimer(i);
}

void WebThread::fromGuiAddItem(QString i)
{
    emit toWebAddItem(i);
}

void WebThread::fromGuiDelItem(qint16 i)
{
    emit toWebDelItem(i);
}

void WebThread::fromGuiSetPort(quint16 i)
{
    emit toWebSetPort(i);
}

void WebThread::fromGuiDelLastItem()
{
    emit toWebDelLastItem();
}

void WebThread::fromWebStartingProcess(qint16 q)
{
    emit toGuiStartingProcess(q);
}
