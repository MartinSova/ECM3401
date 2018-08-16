#include "singledevicesettings.h"
#include "ui_singledevicesettings.h"
#include <iostream>
#include <fstream>

SingleDeviceSettings::SingleDeviceSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleDeviceSettings)
{
    ui->setupUi(this);
    connect(ui->applyChanges, SIGNAL(clicked(bool)), this, SLOT(applyChanges()));
    connect(ui->chooseFile, SIGNAL(clicked(bool)), this, SLOT(toOmit()));
}

QComboBox *SingleDeviceSettings::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5) || defined(Q_WS_SIMULATOR)
    comboBox->setMinimumContentsLength(3);
#endif
    return comboBox;
}

SingleDeviceSettings::~SingleDeviceSettings()
{
    delete ui;
}

void SingleDeviceSettings::toOmit()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Destination Directory"), QDir::currentPath());
    QComboBox *directoryComboBox2 = createComboBox(QDir::currentPath());

    string targetDir(directory.toUtf8().constData());
    directoryToOmit = targetDir;
}


void SingleDeviceSettings::applyChanges()
{
    string newBackupFrequency = ui->backupFrequency->text().toUtf8().constData();
    cout << newBackupFrequency;
    string path = "/home/martin/build-ECM3401-Desktop_Qt_5_7_0_GCC_64bit-Debug/backupFrequency";
    ofstream newFile;
    newFile.open(path);
    newFile << newBackupFrequency;
    newFile.close();
    cout << directoryToOmit;
    if (!ifstream("/home/martin/build-ECM3401-Desktop_Qt_5_7_0_GCC_64bit-Debug/toOmit.json")) {
        // ERROR: no devices JSON file
    } else {
        ifstream i("/home/martin/build-ECM3401-Desktop_Qt_5_7_0_GCC_64bit-Debug/toOmit.json");
        json j;
        i >> j;
        j["omit"].push_back({{"path", directoryToOmit}});
        ofstream o("/home/martin/build-ECM3401-Desktop_Qt_5_7_0_GCC_64bit-Debug/toOmit.json");
        o << setw(4) << j << endl;
    }

}
