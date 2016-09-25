#ifndef QCOMSTRING_H
#define QCOMSTRING_H

#include <QtCore>

typedef struct fgh {
    QString Name;
    QString Comm;
    QString Param;
    bool timer = false;
    //bool batch = true;
} QComString;

#endif // QCOMSTRING_H
