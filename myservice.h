#ifndef MYSERVICE_H
#define MYSERVICE_H

#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <qtservice.h>

class MyService : public QtService<QCoreApplication>
{
public:
    MyService();
};

#endif // MYSERVICE_H
