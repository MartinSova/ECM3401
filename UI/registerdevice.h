#ifndef REGISTERDEVICE_H
#define REGISTERDEVICE_H

#include <QWidget>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <jsonmanager.h>

using namespace std;

typedef vector<string> stringvec;

namespace Ui {
class RegisterDevice;
}

class RegisterDevice : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterDevice(QWidget *parent = 0);
    ~RegisterDevice();
    void readDirectory(const string &name);
    bool notRegistered(string path);
public slots:
    void applyRegister();
private:
    Ui::RegisterDevice *ui;
};

#endif // REGISTERDEVICE_H
