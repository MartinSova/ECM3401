#include "registerdevice.h"
#include "ui_registerdevice.h"

RegisterDevice::RegisterDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterDevice)
{
    ui->setupUi(this);
    readDirectory("/media/martin/");
    connect(ui->applyChanges, SIGNAL(clicked(bool)), this, SLOT(applyRegister()));
}


void RegisterDevice::readDirectory(const string& name)
{
    stringvec v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
        if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0 && JsonManager::notRegistered(dp->d_name)) {
            QListWidgetItem* item = new QListWidgetItem(dp->d_name, ui->connectedNotRegisteredList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
            item->setCheckState(Qt::Unchecked);
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

RegisterDevice::~RegisterDevice()
{
    delete ui;
}

void RegisterDevice::applyRegister()
{

    QListWidget *listWidget = ui->connectedNotRegisteredList;
    vector<string> devicesToRegister;
    for(int i = 0; i < listWidget->count(); ++i)
    {
        QListWidgetItem* item = listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            devicesToRegister.push_back(item->text().toUtf8().constData());
            cout << item->text().toUtf8().constData();
        }
    }
    JsonManager::Register(devicesToRegister);
}
