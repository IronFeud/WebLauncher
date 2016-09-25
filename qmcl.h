#ifndef QMCL_H
#define QMCL_H

#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QSystemTrayIcon>
//#include "qwebserver.h"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "qcomstring.h"
#include <QDebug>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColor>
#include <QLabel>
#include <QCheckBox>
#include <QFileDialog>
#include <QDir>
#include <QTimer>
#include <QProcess>
#include <QSettings>
#include "webthread.h"
#include <QList>


class QMCl : public QObject
{
    Q_OBJECT
public:
    explicit QMCl(QObject *parent = 0);
    QList<QComString*> commands;
    WebThread wt;
    QWidget mWidg;
    QIcon mIcon;
    QSystemTrayIcon stIcon;
    //QWebServer ws;
    QSpinBox portNum;//select port
    QSpinBox timerPeriod;//
    QCheckBox randomProg;//
    QLabel timerLabel;//timer label
    QPushButton setButton;//set port
    QTableWidget comList;//command table
    QPushButton addCom;//
    QPushButton delCom;//
    QHBoxLayout comLay;//comm lay
    QHBoxLayout edtLay1;//edit comm lay
    QHBoxLayout timeLay;//timer lay
    QPushButton timeStart;
    QLineEdit nameCom;//
    QLineEdit pathCom;//
    QPushButton pathFile;
    QLineEdit paramCom;
    QPushButton paramFile;
    QCheckBox timerPlay;
    QCheckBox batchCom;
    QHBoxLayout edtLay2;
    QHBoxLayout portLay;//server lay
    QVBoxLayout mainLay;//
    QTimer* circleTimer;
    qint16 commandIndex;
    qint32 timerTime;
    QSettings* sets;
    void rescanList();
    void loadList();
    void saveList();
signals:
    void setedTimer(bool);
    void addItem(QString);
    void delLastItem();
public slots:
    void iconDoubleCkick(QSystemTrayIcon::ActivationReason i);
    void buttonSet();
    void buttonAdd();
    void buttonDel();
    void batchSet(bool);
    void pathFileDialog();
    void paramFileDialod();
    void timerPeriodSet(int);
    void timerEvent();
    void startProcess(qint16);
    void randomSet(bool);
    void portSet(int);
    void timerSet(int);
    void timerStarting();
};

#endif // QMCL_H
