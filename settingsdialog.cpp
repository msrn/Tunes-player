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
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_addFolder, SIGNAL(clicked()), this, SLOT(onAddClick()));


}

void SettingsDialog::createLayout() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Settings");
    titleLabel->setStyleSheet("font-size: 30px;");

    m_fileSettingsGroup = new QGroupBox("Libary");
    m_fileSettingsGroup->setStyleSheet("QGroupBox { font-size: 20px;}");
    QVBoxLayout *fileGroupLayout = new QVBoxLayout(this);
    QLabel *fileLabel = new QLabel("Monitored folders");
    m_addFolder = new QPushButton("Add");
    m_addFolder->setMaximumSize(50,50);
    fileGroupLayout->addWidget(fileLabel);
    fileGroupLayout->addWidget(m_addFolder);
    m_fileSettingsGroup->setLayout(fileGroupLayout);


    m_audioSettingsGroup = new QGroupBox("Audio");
    m_audioSettingsGroup->setStyleSheet("QGroupBox {font-size: 20px; }");
    QVBoxLayout *audioGroupLayout = new QVBoxLayout();
    QLabel *deviceLabel = new QLabel("Playback device");
    deviceLabel->setWhatsThis("Set applications default output device for music playing");
    QComboBox *deviceDropDown = new QComboBox();
    deviceDropDown->setMaximumWidth(200);
    deviceDropDown->addItem("Default system output device");
    audioGroupLayout->addWidget(deviceLabel);
    audioGroupLayout->addWidget(deviceDropDown);
    m_audioSettingsGroup->setLayout(audioGroupLayout);

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);



    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_fileSettingsGroup);
    mainLayout->addWidget(m_audioSettingsGroup);
    mainLayout->addSpacing(200);
    mainLayout->addWidget(m_buttonBox);
    mainLayout->setAlignment(Qt::AlignTop);

    this->setLayout(mainLayout);

}

void SettingsDialog::onAddClick() {

  QString folder = QFileDialog::getExistingDirectory(this,tr("Choose a Folder"),QDir::homePath());

}
