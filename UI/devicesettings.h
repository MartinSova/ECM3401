#ifndef DEVICESETTINGS_H
#define DEVICESETTINGS_H

#include <QWidget>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <jsonmanager.h>
#include <singledevicesettings.h>

using namespace std;

typedef vector<string> stringvec;

namespace Ui {
class DeviceSettings;
}

class DeviceSettings : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceSettings(QWidget *parent = 0);
    ~DeviceSettings();
    void readDirectory(const string &name);
    bool notRegistered(string path);
public slots:
    void openSingleDeviceSettings();
private:
    Ui::DeviceSettings *ui;
    SingleDeviceSettings *singleDeviceSettings;
};

#endif // DeviceSettings_H

