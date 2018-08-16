#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registerdevice.h"
#include "deregisterdevice.h"
#include "devicesettings.h"
#include "connection.h"
#include "window2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
   void openRegister();
   void openDeregister();
   void openSettings();
   void openSearchFiles();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RegisterDevice *registerDevice;
    DeregisterDevice *deregisterDevice;
    DeviceSettings *deviceSettings;
    Connection *connection;
    Window *searchWindow;
};

#endif // MAINWINDOW_H
