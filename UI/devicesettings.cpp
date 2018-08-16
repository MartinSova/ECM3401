#include "devicesettings.h"
#include "ui_devicesettings.h"

DeviceSettings::DeviceSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceSettings)
{
    ui->setupUi(this);
    readDirectory("/media/martin/");
}


void DeviceSettings::readDirectory(const string& name)
{
    stringvec v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
        if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0 && JsonManager::registered(dp->d_name)) {
            QListWidgetItem *item = new QListWidgetItem(dp->d_name);
            connect(ui->registeredList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openSingleDeviceSettings()));
            ui->registeredList->addItem(item);
        }
    }
    /*
    for(vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
        // process i
        cout << *i << " "; // this will print all the contents of *features*
    }
    */
    closedir(dirp);
}

DeviceSettings::~DeviceSettings()
{
    delete ui;
}

void DeviceSettings::openSingleDeviceSettings()
{

    singleDeviceSettings = new SingleDeviceSettings();
     // Be sure to destroy your window somewhere
    singleDeviceSettings->show();
}

