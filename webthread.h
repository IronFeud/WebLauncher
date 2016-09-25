#ifndef WEBTHREAD_H
#define WEBTHREAD_H

#include <QObject>
#include <QThread>
#include "qwebserver.h"

class WebThread : public QObject
{
    Q_OBJECT
    QThread work;
public:
    explicit WebThread(QObject *parent = 0);

signals:
    void toGuiStartingProcess(qint16);
    void toWebTimer(bool);
    void toWebSetPort(quint16);
    void toWebAddItem(QString);
    void toWebDelItem(qint16);
    void toWebDelLastItem();
public slots:
    void fromWebStartingProcess(qint16);
    void fromGuiTimer(bool);
    void fromGuiAddItem(QString);
    void fromGuiDelItem(qint16);
    void fromGuiSetPort(quint16);
    void fromGuiDelLastItem();
};

#endif // WEBTHREAD_H
