#ifndef SINGLEDEVICESETTINGS_H
#define SINGLEDEVICESETTINGS_H

#include <QWidget>
#include <string>
#include <QWidget>
#include <QDir>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <QComboBox>
#include <QFileDialog>
#include <QWidget>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <jsonmanager.h>
#include "json.hpp"
#include <fstream>
#include <iostream>

using namespace std;

namespace Ui {
class SingleDeviceSettings;
}

class SingleDeviceSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SingleDeviceSettings(QWidget *parent = 0);
    ~SingleDeviceSettings();

    QComboBox *createComboBox(const QString &text);
public slots:
    void applyChanges();
    void toOmit();
private:
    Ui::SingleDeviceSettings *ui;
    string directoryToOmit;
};

#endif // SINGLEDEVICESETTINGS_H
