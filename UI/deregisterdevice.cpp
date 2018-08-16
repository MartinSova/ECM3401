#include "deregisterdevice.h"
#include "ui_deregisterdevice.h"

DeregisterDevice::DeregisterDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeregisterDevice)
{
    ui->setupUi(this);
    readDirectory("/media/martin/");
    connect(ui->applyDeregister, SIGNAL(clicked(bool)), this, SLOT(applyDeregister()));
}

void DeregisterDevice::readDirectory(const string& name)
{
    stringvec v;
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
        if (strcmp(".", dp->d_name) != 0 && strcmp("..", dp->d_name) != 0 && JsonManager::registered(dp->d_name)) {

            QListWidgetItem* item = new QListWidgetItem(dp->d_name, ui->connectedRegisteredList);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // set checkable flag
            item->setCheckState(Qt::Unchecked);
            //new QListWidgetItem(tr(dp->d_name), ui->connectedRegisteredList);

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

void DeregisterDevice::highlightChecked(QListWidgetItem *item){
    if(item->checkState() == Qt::Checked)
        item->setBackgroundColor(QColor("#ffffb2"));
    else
        item->setBackgroundColor(QColor("#ffffff"));
}

DeregisterDevice::~DeregisterDevice()
{
    delete ui;
}

void DeregisterDevice::applyDeregister()
{

    QListWidget *listWidget = ui->connectedRegisteredList;
    vector<string> devicesToDeregister;
    for(int i = 0; i < listWidget->count(); ++i)
    {
        QListWidgetItem* item = listWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            devicesToDeregister.push_back(item->text().toUtf8().constData());
            cout << item->text().toUtf8().constData();
        }
    }
    JsonManager::deRegister(devicesToDeregister);
}
