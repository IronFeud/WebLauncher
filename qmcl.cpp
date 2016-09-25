#include "qmcl.h"

QMCl::QMCl(QObject *parent) : QObject(parent)
{
    sets = new QSettings("weblauncher.ini", QSettings::IniFormat);
    circleTimer = new QTimer(this);

    mIcon.addFile("whhjAsa.png");
    stIcon.setIcon(mIcon);
    stIcon.setToolTip("WebLauncher");
    stIcon.show();

    setButton.setText("Hide");
    portNum.setRange(80, 65530);
    portNum.setValue(sets->value("local/port").toInt());
    portNum.setSingleStep(1);
    //portLay.addWidget(&portNum);
    portLay.addWidget(&setButton);

    timerLabel.setText("Timer Min.");
    randomProg.setText("Random");
    timeStart.setText("Start");
    randomProg.setChecked(sets->value("local/rnd").toBool());
    timerPeriod.setRange(0, 1000);
    timerPeriod.setValue(sets->value("local/timer").toInt());
    timerPeriodSet(sets->value("local/timer").toInt());
    timeLay.addWidget(&timerPeriod);
    timeLay.addWidget(&timerLabel);
    timeLay.addWidget(&randomProg);
    timeLay.addWidget(&timeStart);

    nameCom.setText("Name");
    pathCom.setText("Path or Name Programm");
    pathFile.setText("Open");
    edtLay1.addWidget(&pathCom);
    edtLay1.addWidget(&pathFile);
    paramCom.setText("Param");
    paramFile.setText("Open");
    edtLay2.addWidget(&paramCom);
    edtLay2.addWidget(&paramFile);

    batchCom.setText("Batch Script");
    timerPlay.setText("Start On Timer");

    addCom.setText("Add Command");
    delCom.setText("Del Last Command");
    comLay.addWidget(&addCom);
    comLay.addWidget(&delCom);

    comList.setColumnCount(4);
    QTableWidgetItem *header1 = new QTableWidgetItem();
    header1->setText("Name");
    comList.setHorizontalHeaderItem(0,header1);
    QTableWidgetItem *header2 = new QTableWidgetItem();
    header2->setText("Path");
    comList.setHorizontalHeaderItem(1,header2);
    QTableWidgetItem *header3 = new QTableWidgetItem();
    header3->setText("Param");
    comList.setHorizontalHeaderItem(2,header3);
    QTableWidgetItem *header4 = new QTableWidgetItem();
    header4->setText("List");
    comList.setHorizontalHeaderItem(3,header4);
    comList.setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLay.addLayout(&portLay);
    //mainLay.addLayout(&timeLay);
    mainLay.addWidget(&comList);
    mainLay.addWidget(&nameCom);
    mainLay.addWidget(&batchCom);
    mainLay.addLayout(&edtLay1);
    mainLay.addLayout(&edtLay2);
    mainLay.addWidget(&timerPlay);
    mainLay.addLayout(&comLay);

    mWidg.setMinimumWidth(500);
    mWidg.setLayout(&mainLay);
    mWidg.setWindowIcon(mIcon);
    mWidg.setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    mWidg.hide();

    connect(&stIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconDoubleCkick(QSystemTrayIcon::ActivationReason)));
    connect(&setButton, SIGNAL(released()), this, SLOT(buttonSet()));
    connect(&addCom, SIGNAL(released()), this, SLOT(buttonAdd()));
    connect(&delCom, SIGNAL(released()), this, SLOT(buttonDel()));
    connect(&batchCom, SIGNAL(toggled(bool)), this, SLOT(batchSet(bool)));
    connect(&pathFile, SIGNAL(released()), this, SLOT(pathFileDialog()));
    connect(&paramFile, SIGNAL(released()), this, SLOT(paramFileDialod()));
    connect(&timerPeriod, SIGNAL(valueChanged(int)), this, SLOT(timerPeriodSet(int)), Qt::DirectConnection);
    connect(circleTimer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    connect(this, SIGNAL(setedTimer(bool)), &wt, SLOT(fromGuiTimer(bool)));
    connect(this, SIGNAL(addItem(QString)), &wt, SLOT(fromGuiAddItem(QString)));
    connect(this, SIGNAL(delLastItem()), &wt, SLOT(fromGuiDelLastItem()));
    connect(&timeStart, SIGNAL(released()), this, SLOT(timerStarting()));
    connect(&wt, SIGNAL(toGuiStartingProcess(qint16)), this, SLOT(startProcess(qint16)));
    connect(&randomProg, SIGNAL(toggled(bool)), this, SLOT(randomSet(bool)));
    connect(&portNum, SIGNAL(valueChanged(int)), this, SLOT(portSet(int)));
    connect(&timerPeriod, SIGNAL(valueChanged(int)), this, SLOT(timerSet(int)));
    loadList();
    rescanList();
}

void QMCl::rescanList()
{
    QString tmlst;
        comList.clear();
        QTableWidgetItem *header1 = new QTableWidgetItem();
        header1->setText("Name");
        comList.setHorizontalHeaderItem(0,header1);
        QTableWidgetItem *header2 = new QTableWidgetItem();
        header2->setText("Path");
        comList.setHorizontalHeaderItem(1,header2);
        QTableWidgetItem *header3 = new QTableWidgetItem();
        header3->setText("Param");
        comList.setHorizontalHeaderItem(2,header3);
        QTableWidgetItem *header4 = new QTableWidgetItem();
        header4->setText("List");
        comList.setHorizontalHeaderItem(3,header4);
        comList.setRowCount(commands.count());
        for(qint16 row = 0; row <= commands.count() - 1; row++) {
            QTableWidgetItem *newItem1 = new QTableWidgetItem(commands.at(row)->Name);
            QTableWidgetItem *newItem2 = new QTableWidgetItem(commands.at(row)->Comm);
            QTableWidgetItem *newItem3 = new QTableWidgetItem(commands.at(row)->Param);
            if(commands.at(row)->timer == true) {
                tmlst = "On Timer";
            } else {
                tmlst = "Off Timer";
            }
            QTableWidgetItem *newItem4 = new QTableWidgetItem(tmlst);
            comList.setItem(row, 0, newItem1);
            comList.setItem(row, 1, newItem2);
            comList.setItem(row, 2, newItem3);
            comList.setItem(row, 3, newItem4);
        }
}

void QMCl::loadList()
{
    int ev;
    ev = sets->value("events/events").toInt();
    if(ev != 0) {
        for(qint16 row = 0; row <= ev - 1; row++) {
            commands.append(new QComString);
            commands.last()->Name = sets->value("events/evName-" + QString::number(row)).toString();
            commands.last()->Comm = sets->value("events/evComm-" + QString::number(row)).toString();
            commands.last()->Param = sets->value("events/evParm-" + QString::number(row)).toString();
            commands.last()->timer = sets->value("events/evTime-" + QString::number(row)).toBool();
            emit addItem(sets->value("events/evName-" + QString::number(row)).toString());
        }
    }
}

void QMCl::saveList()
{
    sets->setValue("events/events", commands.count());
    for(qint16 row = 0; row <= commands.count() - 1; row++) {
        sets->setValue("events/evName-" + QString::number(row), commands.at(row)->Name);
        sets->setValue("events/evComm-" + QString::number(row), commands.at(row)->Comm);
        sets->setValue("events/evParm-" + QString::number(row), commands.at(row)->Param);
        sets->setValue("events/evTime-" + QString::number(row), commands.at(row)->timer);
    }
}

void QMCl::iconDoubleCkick(QSystemTrayIcon::ActivationReason i)
{
    if(i == QSystemTrayIcon::DoubleClick) {
        mWidg.show();
    } else if(i == QSystemTrayIcon::Context) {
        //
    }
}

void QMCl::buttonSet()
{
    mWidg.hide();
}

void QMCl::buttonAdd()
{
    commands.append(new QComString);
    commands.last()->Name = nameCom.text();
    commands.last()->Comm = pathCom.text();
    commands.last()->Param = paramCom.text();
    commands.last()->timer = timerPlay.isChecked();
    rescanList();
    saveList();
    emit addItem(nameCom.text());
}

void QMCl::buttonDel()
{
    if(commands.count() != 0) {
        sets->remove("events/evName-" + QString::number(commands.count() - 1));
        sets->remove("events/evComm-" + QString::number(commands.count() - 1));
        sets->remove("events/evParm-" + QString::number(commands.count() - 1));
        sets->remove("events/evTime-" + QString::number(commands.count() - 1));
        commands.removeLast();
        rescanList();
    }
    saveList();
    emit delLastItem();
}

void QMCl::batchSet(bool i)
{
    if(i == true) {
        pathCom.setText("cmd.exe");
        pathCom.setDisabled(i);
        pathFile.setDisabled(i);
    } else {
        pathCom.setText("Path or Name Programm");
        pathCom.setDisabled(i);
        pathFile.setDisabled(i);
    }
}

void QMCl::pathFileDialog()
{
    QString filename = QFileDialog::getOpenFileName(&mWidg, tr("Open Document"), "C:/", "Programm (*.exe)");
    if( !filename.isNull() )
    {
        //qDebug() << filename;
        pathCom.setText(filename);
    }
}

void QMCl::paramFileDialod()
{
    QString filename = QFileDialog::getOpenFileName(&mWidg, tr("Open Document"), "C:/", "All files (*.*)");
    if( !filename.isNull() )
    {
        //qDebug() << filename;
        paramCom.setText(filename);
    }
}

void QMCl::timerPeriodSet(int i)
{
    timerTime = i * 6000;
    //qDebug() << i;
    //circleTimer.setInterval(i * 6000);//60000
    if(i != 0) {
        emit setedTimer(true);
        //qDebug() << "true";
    } else {
        emit setedTimer(false);
    }
}

void QMCl::timerStarting()
{
    //qDebug() << "Ts";
    timerEvent();
    circleTimer->start(timerTime);
}

void QMCl::timerEvent()
{
    //qDebug() << "Timer";
    //if(randomProg.isChecked() == true) {
        //qint16 h = qrand();
    //} else {
        //commandIndex
        while (commands.at(commandIndex)->timer == false) {
            commandIndex++;
        };
        startProcess(commandIndex);
        if(commands.count() == commandIndex + 1) {
            commandIndex = 0;
        } else {
            commandIndex++;
        }
    //}
}

void QMCl::startProcess(qint16 i)
{
    if(i != -1) {
        QProcess *proced = new QProcess();
        proced->startDetached(commands.at(i)->Comm, QStringList() << commands.at(i)->Param);
    } else {
        timerStarting();
    }
}

void QMCl::randomSet(bool i)
{
    sets->setValue("local/rnd", i);
}

void QMCl::portSet(int i)
{
    sets->setValue("local/port", i);
}

void QMCl::timerSet(int i)
{
    sets->setValue("local/timer", i);
}
