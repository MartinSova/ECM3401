#ifndef DeregisterDevice_H
#define DeregisterDevice_H
#include <QWidget>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <jsonmanager.h>
#include <QListWidgetItem>

using namespace std;

typedef vector<string> stringvec;

namespace Ui {
class DeregisterDevice;
}

class DeregisterDevice : public QWidget
{
    Q_OBJECT

public:
    explicit DeregisterDevice(QWidget *parent = 0);
    ~DeregisterDevice();
    void readDirectory(const string &name);
    bool notRegistered(string path);
    void highlightChecked(QListWidgetItem *item);
public slots:
    void applyDeregister();
private:
    Ui::DeregisterDevice *ui;
};

#endif // DeregisterDevice_H
