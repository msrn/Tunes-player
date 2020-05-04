#include "helpdialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>


HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent) {

    this->setWindowTitle("Help");
    this->setModal(true);
    this->setFixedSize(400,400);

    //Viewstack controls the content view
    m_viewStack = new QStackedWidget();
    createLayout();
    createWelcome();
    createHowTo();
    createMain();
    createArtist();
    createAlbum();
    createGenre();


    m_viewStack->addWidget(m_welcomeWidget);
    m_viewStack->addWidget(m_howToWidget);
    m_viewStack->addWidget(m_mainViewWidget);
    m_viewStack->addWidget(m_artistViewWidget);
    m_viewStack->addWidget(m_albumViewWidget);
    m_viewStack->addWidget(m_genreViewWidget);

    connect(m_helpList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClick(QListWidgetItem*)));

}

void HelpDialog::createLayout() {

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QVBoxLayout *helpIndexLayout = new QVBoxLayout(this);
    QWidget *helpIndex = new QWidget();
    QLabel *helpIndexLabel = new QLabel("Help Index");
    helpIndexLabel->setStyleSheet("font-size: 30px;");

    m_helpList = new QListWidget(this);
    m_welcomeItem = new QListWidgetItem("Welcome", m_helpList);
    m_howToItem = new QListWidgetItem("How to use", m_helpList);
    m_mainViewItem = new QListWidgetItem("Home view", m_helpList);
    m_artistViewItem = new QListWidgetItem("Artist view", m_helpList);
    m_albumViewItem = new QListWidgetItem("Album view", m_helpList);
    m_genreViewItem = new QListWidgetItem("Genre view", m_helpList);

    m_helpList->addItem(m_welcomeItem);
    m_helpList->addItem(m_howToItem);
    m_helpList->addItem(m_mainViewItem);
    m_helpList->addItem(m_artistViewItem);
    m_helpList->addItem(m_albumViewItem);
    m_helpList->addItem(m_genreViewItem);

    helpIndexLayout->addWidget(helpIndexLabel);
    helpIndexLayout->addWidget(m_helpList);
    helpIndex->setLayout(helpIndexLayout);

    QVBoxLayout *contentLayout = new QVBoxLayout(this);
    QWidget *contentWidget = new QWidget(this);

    contentLayout->addWidget(m_viewStack);
    contentWidget->setLayout(contentLayout);



    mainLayout->addWidget(helpIndex);
    mainLayout->addWidget(contentWidget);
    this->setLayout(mainLayout);

}

void HelpDialog::createWelcome() {

    m_welcomeWidget = new QWidget(this);

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("Welcome");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit(this);
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText(
                "Welcome to Tunes music player\n"
                "From left sidebar select your desired category. \n "
                "Close this help view by closing this with the windows close button.");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_welcomeWidget->setLayout(vBox);

}

void HelpDialog::createHowTo()
{
    m_howToWidget = new QWidget();

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("How to use");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit();
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText("Tunes is very simple to use.\n\n"
                     "On album you want to play press the 'Play' -button "
                     "to add that album to your playlist. \n"
                     "You can see your playlist on the Now Playing dock which shows "
                     "your currently playing track with other information to it. \n"
                     "And then the play queue with upcoming tracks. "
                     "And lastly you can control playback with media buttons at the bottom. \n\n "
                     "Now PLaying dock position can also be changed. Just left click and drag "
                     "Now Playing from its titlebar to left side or right side. Transparent rectangle will be shown. "
                     "Then release left mouse button to set dock position. \n\n"
                     "Main menu bar can also dragged in the same way, just click and hold on four vertical dots on the left side of the menubar.");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_howToWidget->setLayout(vBox);
}

void HelpDialog::createMain()
{
    m_mainViewWidget = new QWidget();

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("Main View");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit();
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText("Home view shows all of your new additions to your library. \n"
                     "In the future you can add more sub views to your Home view.");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_mainViewWidget->setLayout(vBox);
}

void HelpDialog::createArtist()
{
    m_artistViewWidget = new QWidget();

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("Artist View");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit();
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText("Artist view lists all of your librarys artist in list on the left side.\n"
                     "Just click on the artists whos albums you want to view and then on the right press Play on the desired album");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_artistViewWidget->setLayout(vBox);
}

void HelpDialog::createAlbum()
{
    m_albumViewWidget = new QWidget();

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("Album View");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit();
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText("Album view lists all of your librarys albums on cover mode.\n"
                     "Just press Play on the desired album to play that particular album. \n"
                     "You can also sort albums in different ways, press Sort to see how.");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_albumViewWidget->setLayout(vBox);
}

void HelpDialog::createGenre()
{
    m_genreViewWidget = new QWidget();

    QVBoxLayout *vBox = new QVBoxLayout(this);

    QLabel *title = new QLabel("Genre View");
    title->setStyleSheet("font-size: 20px;");

    QTextEdit *content = new QTextEdit();
    content->setStyleSheet("background-color: transparent; border: 0px;");
    content->setReadOnly(true);
    content->setText("Genre view lists all of your librarys genres in list on the left side.\n"
                     "Just click on the genre which albums you want to view and then on the right press Play on the desired album \n "
                     "You can also sort albums in different ways, press Sort to see how.");

    vBox->addWidget(title);
    vBox->addWidget(content);
    m_genreViewWidget->setLayout(vBox);
}



void HelpDialog::onItemClick(QListWidgetItem * item)
{
    if (item == m_welcomeItem)
        m_viewStack->setCurrentWidget(m_welcomeWidget);

    if (item == m_howToItem)
        m_viewStack->setCurrentWidget(m_howToWidget);

    if (item == m_mainViewItem)
        m_viewStack->setCurrentWidget(m_mainViewWidget);

    if (item == m_artistViewItem)
        m_viewStack->setCurrentWidget(m_artistViewWidget);

    if (item == m_albumViewItem)
        m_viewStack->setCurrentWidget(m_albumViewWidget);

    if (item == m_genreViewItem)
        m_viewStack->setCurrentWidget(m_genreViewWidget);
}
