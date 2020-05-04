#include "helpdialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>


HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent) {

    this->setWindowTitle("Help");
    this->setModal(true);
    this->setFixedSize(400,400);

    //Viewstack controls the content view
    viewStack = new QStackedWidget();
    createLayout();
    createWelcome();
    createHowTo();
    createMain();
    createArtist();
    createAlbum();
    createGenre();


    viewStack->addWidget(welcomeWidget);
    viewStack->addWidget(howToWidget);
    viewStack->addWidget(mainViewWidget);
    viewStack->addWidget(artistViewWidget);
    viewStack->addWidget(albumViewWidget);
    viewStack->addWidget(genreViewWidget);

    connect(helpList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClick(QListWidgetItem*)));

}

void HelpDialog::createLayout() {

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QVBoxLayout *helpIndexLayout = new QVBoxLayout(this);
    QWidget *helpIndex = new QWidget();
    QLabel *helpIndexLabel = new QLabel("Help Index");
    helpIndexLabel->setStyleSheet("font-size: 30px;");

    helpList = new QListWidget(this);
    welcomeItem = new QListWidgetItem("Welcome", helpList);
    howToItem = new QListWidgetItem("How to use", helpList);
    mainViewItem = new QListWidgetItem("Home view", helpList);
    artistViewItem = new QListWidgetItem("Artist view", helpList);
    albumViewItem = new QListWidgetItem("Album view", helpList);
    genreViewItem = new QListWidgetItem("Genre view", helpList);

    helpList->addItem(welcomeItem);
    helpList->addItem(howToItem);
    helpList->addItem(mainViewItem);
    helpList->addItem(artistViewItem);
    helpList->addItem(albumViewItem);
    helpList->addItem(genreViewItem);

    helpIndexLayout->addWidget(helpIndexLabel);
    helpIndexLayout->addWidget(helpList);
    helpIndex->setLayout(helpIndexLayout);

    QVBoxLayout *contentLayout = new QVBoxLayout(this);
    QWidget *contentWidget = new QWidget(this);

    contentLayout->addWidget(viewStack);
    contentWidget->setLayout(contentLayout);



    mainLayout->addWidget(helpIndex);
    mainLayout->addWidget(contentWidget);
    this->setLayout(mainLayout);

}

void HelpDialog::createWelcome() {

    welcomeWidget = new QWidget(this);

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
    welcomeWidget->setLayout(vBox);

}

void HelpDialog::createHowTo()
{
    howToWidget = new QWidget();

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
    howToWidget->setLayout(vBox);
}

void HelpDialog::createMain()
{
    mainViewWidget = new QWidget();

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
    mainViewWidget->setLayout(vBox);
}

void HelpDialog::createArtist()
{
    artistViewWidget = new QWidget();

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
    artistViewWidget->setLayout(vBox);
}

void HelpDialog::createAlbum()
{
    albumViewWidget = new QWidget();

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
    albumViewWidget->setLayout(vBox);
}

void HelpDialog::createGenre()
{
    genreViewWidget = new QWidget();

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
    genreViewWidget->setLayout(vBox);
}



void HelpDialog::onItemClick(QListWidgetItem * item)
{
    if (item == welcomeItem)
        viewStack->setCurrentWidget(welcomeWidget);

    if (item == howToItem)
        viewStack->setCurrentWidget(howToWidget);

    if (item == mainViewItem)
        viewStack->setCurrentWidget(mainViewWidget);

    if (item == artistViewItem)
        viewStack->setCurrentWidget(artistViewWidget);

    if (item == albumViewItem)
        viewStack->setCurrentWidget(albumViewWidget);

    if (item == genreViewItem)
        viewStack->setCurrentWidget(genreViewWidget);
}
