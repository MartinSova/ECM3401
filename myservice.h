#ifndef MYSERVICE_H
#define MYSERVICE_H

#include <QCoreApplication>
#include <QObject>
#include <QDebug>
#include <qtservice.h>

class MyService : public QtService<QCoreApplication>
{
public:
    /**
     * @brief The constructor
     * @param argc
     * @param argv
     */
    MyService(int argc, char **argv);

    /**
     * @brief The decosntructor
     */
    ~MyService();

    /**
     * @brief Start the service
     */
    void start();

    /**
     * @brief Pause the service
     */
    void pause();

    /**
     * @brief Resume the service
     */
    void resume();

    /**
     * @brief Stop the service
     */
    void stop();

private:
       // Add in any pointers

};

#endif // MYSERVICE_H
