#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    //connection = new Connection();
    connect(ui->registerDevice, SIGNAL(clicked(bool)), this, SLOT(openRegister()));
    connect(ui->deregisterDevice, SIGNAL(clicked(bool)), this, SLOT(openDeregister()));
    connect(ui->settings, SIGNAL(clicked(bool)), this, SLOT(openSettings()));
    connect(ui->restore, SIGNAL(clicked(bool)), this, SLOT(openSearchFiles()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openRegister()
{
   registerDevice = new RegisterDevice();
    // Be sure to destroy your window somewhere
   registerDevice->show();
   // ...
}

void MainWindow::openSettings()
{
   deviceSettings = new DeviceSettings();
    // Be sure to destroy your window somewhere
   deviceSettings->show();
   // ...
}

void MainWindow::openDeregister()
{
    // Be sure to destroy your window somewhere
   deregisterDevice = new DeregisterDevice();
   deregisterDevice->show();
}

void MainWindow::openSearchFiles()
{
    searchWindow = new Window();
    searchWindow->show();
}
