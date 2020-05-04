#include "settingsdialog.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {

    this->setWindowTitle("Settings");
    this->setModal(true);
    this->createLayout();
    this->setFixedSize(400,400);

    //handle buttonbox clicks
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(addFolder, SIGNAL(clicked()), this, SLOT(onAddClick()));


}

void SettingsDialog::createLayout() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Settings");
    titleLabel->setStyleSheet("font-size: 30px;");

    fileSettingsGroup = new QGroupBox("Libary");
    fileSettingsGroup->setStyleSheet("QGroupBox { font-size: 20px;}");
    QVBoxLayout *fileGroupLayout = new QVBoxLayout(this);
    QLabel *fileLabel = new QLabel("Monitored folders");
    addFolder = new QPushButton("Add");
    addFolder->setMaximumSize(50,50);
    fileGroupLayout->addWidget(fileLabel);
    fileGroupLayout->addWidget(addFolder);
    fileSettingsGroup->setLayout(fileGroupLayout);


    audioSettingsGroup = new QGroupBox("Audio");
    audioSettingsGroup->setStyleSheet("QGroupBox {font-size: 20px; }");
    QVBoxLayout *audioGroupLayout = new QVBoxLayout();
    QLabel *deviceLabel = new QLabel("Playback device");
    deviceLabel->setWhatsThis("Set applications default output device for music playing");
    QComboBox *deviceDropDown = new QComboBox();
    deviceDropDown->setMaximumWidth(200);
    deviceDropDown->addItem("Default system output device");
    audioGroupLayout->addWidget(deviceLabel);
    audioGroupLayout->addWidget(deviceDropDown);
    audioSettingsGroup->setLayout(audioGroupLayout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);



    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(fileSettingsGroup);
    mainLayout->addWidget(audioSettingsGroup);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(buttonBox);
    mainLayout->setAlignment(Qt::AlignTop);

    this->setLayout(mainLayout);

}

void SettingsDialog::onAddClick() {

  QString folder = QFileDialog::getExistingDirectory(this,tr("Choose a Folder"),QDir::homePath());

}
