#include "mainwindow.h"
#include "daemon.h"
#include <QApplication>
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
    Daemon();
    while (1)
        {
            //TODO: Insert daemon code here.
            syslog (LOG_NOTICE, "First daemon started.");
            cout << "daemon started";
            sleep (20);
            break;
        }
        cout << "daemon started";
        syslog (LOG_NOTICE, "First daemon terminated.");
        closelog();

       return EXIT_SUCCESS;

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
}
