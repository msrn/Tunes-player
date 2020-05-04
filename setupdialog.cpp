#include "setupdialog.h"

#include <QCoreApplication>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

SetupDialog::SetupDialog(QWidget* parent) : QDialog(parent) {

    this->setWindowTitle("Setup Wizard");
    this->setFixedSize(400,400);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    m_quit = false;

    createFirstPage();
    createSecondPage();

    m_stackWidget = new QStackedWidget();
    m_stackWidget->addWidget(m_firstPage);
    m_stackWidget->addWidget(m_secondPage);

    QVBoxLayout *contentLayout = new QVBoxLayout(this);
    QWidget *contentWidget = new QWidget(this);

    contentLayout->addWidget(m_stackWidget);
    contentWidget->setLayout(contentLayout);

    this->setLayout(contentLayout);

    connect(m_nextButton, SIGNAL(clicked()), this, SLOT(onNextClick()));
    connect(m_backButton, SIGNAL(clicked()), this, SLOT(onBackClick()));
    connect(m_addFolder, SIGNAL(clicked()), this, SLOT(onAddClick()));
    connect(m_finishButton, SIGNAL(clicked()), this, SLOT(onFinishClick()));
    connect(m_quitButton, SIGNAL(clicked()), this, SLOT(onQuitClick()));






}

void SetupDialog::createFirstPage()
{
    m_firstPage = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QLabel *label = new QLabel("Welcome!");
    label->setStyleSheet("font-size: 20px");

    QLabel *content = new QLabel(this);
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setText(
                "Welcome to Tunes music player\n"
                "Press Add button to select folders which you'd like to import music from. \n ");
    content->setMaximumHeight(100);
    QLabel *fileLabel = new QLabel("Monitored folders");
    m_addFolder = new QPushButton("Add");
    m_addFolder->setMaximumSize(50,50);

    QHBoxLayout *buttons = new QHBoxLayout();
    m_nextButton = new QPushButton("Next");
    m_quitButton = new QPushButton("Quit");
    buttons->addWidget(m_nextButton);
    buttons->addWidget(m_quitButton);

    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(label);
    mainLayout->addWidget(content);
    mainLayout->addSpacing(100);
    mainLayout->addWidget(fileLabel);
    mainLayout->addWidget(m_addFolder);
    mainLayout->addSpacing(200);
    mainLayout->addLayout(buttons);

    m_firstPage->setLayout(mainLayout);

}

void SetupDialog::createSecondPage() {

        m_secondPage = new QWidget();
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QLabel *label = new QLabel("Setup finished");
        label->setStyleSheet("font-size: 20px");

        QLabel *content = new QLabel(this);
        content->setStyleSheet("background-color: transparent; border: 0px;");
        content->setText(
                    "Setup finished!\n"
                    "Go on and enjoy your freshly imported music. \n You can also check some other "
                    " settings from Settings -menu.\n ");
        content->setMaximumHeight(100);

        QHBoxLayout *buttons = new QHBoxLayout();
        m_backButton = new QPushButton("Back");
        m_finishButton = new QPushButton("Finish");
        buttons->addWidget(m_backButton);
        buttons->addWidget(m_finishButton);

        mainLayout->setAlignment(Qt::AlignTop);
        mainLayout->addWidget(label);
        mainLayout->addWidget(content);
        mainLayout->addSpacing(100);
        mainLayout->addSpacing(200);
        mainLayout->addLayout(buttons);

        m_secondPage->setLayout(mainLayout);

}

bool SetupDialog::getQuit() const
{
    return m_quit;
}

void SetupDialog::onAddClick() {

    QString folder = QFileDialog::getExistingDirectory(this,tr("Choose a Folder"),QDir::homePath());

}

void SetupDialog::onNextClick() {

    m_stackWidget->setCurrentWidget(m_secondPage);

}

void SetupDialog::onBackClick() {

    m_stackWidget->setCurrentWidget(m_firstPage);
}

void SetupDialog::onFinishClick() {

    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Finished?", "Are you sure you are finished? \n"
                                                  "Clicking Yes takes you to the main window and clicking No goes back to Setup.",
                                   QMessageBox::Yes |QMessageBox::No);
    if (msgBox == QMessageBox::Yes) {
        accept();
    }

}

void SetupDialog::onQuitClick()
{
    QMessageBox::StandardButton msgBox;
    msgBox = QMessageBox::question(this, "Quit?", "Are you sure you want to quit? \n"
                                                  "You will have to complete this setup process on next startup.",
                                   QMessageBox::Yes |QMessageBox::No);
    if (msgBox == QMessageBox::Yes)
        QCoreApplication::quit();
        m_quit = true;
}


