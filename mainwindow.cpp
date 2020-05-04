#include "mainwindow.h"
#include <QToolBar>
#include <QDockWidget>
#include <QApplication>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QMenu>
#include <QScrollArea>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("Tunes");
    this->resize(1280, 768); //initial window size
    this->setMinimumSize(1280, 768);
    settingsDialog = new SettingsDialog(this);
    helpDialog = new HelpDialog(this);

    createActions();
    createToolbar();
    createPlayerDock();
    createHomeLayout();
    createArtistsLayout();
    createAlbumsLayout();
    createGenresLayout();


    /*
     * ViewStack handles view changing
     */
    viewStack = new QStackedWidget();

    viewStack->addWidget(homeWidget);
    viewStack->addWidget(artistsWidget);
    viewStack->addWidget(albumsWidget);
    viewStack->addWidget(genresWidget);


    this->setCentralWidget(viewStack);


    //Handles Toolbar Buttons and view change
    connect(homeAction, SIGNAL(triggered()), this, SLOT(onHomeActionClick()));
    connect(artistsAction, SIGNAL(triggered()), this, SLOT(onArtistsActionClick()));
    connect(albumsAction, SIGNAL(triggered()), this, SLOT(onAlbumsActionClick()));
    connect(genresAction, SIGNAL(triggered()), this, SLOT(onGenresActionClick()));


    connect(settingsAction, SIGNAL(triggered()), settingsDialog, SLOT(exec()));
    connect(helpAction, SIGNAL(triggered()), helpDialog, SLOT(exec()));



}

MainWindow::~MainWindow() {

}

void MainWindow::createToolbar() {

    QToolBar *toolbar = new QToolBar(this);
    this->addToolBar(Qt::TopToolBarArea,toolbar); //Adds toolbar to MainWindow
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolbar->setIconSize(QSize(32,32));
    toolbar->setFloatable(false);
    toolbar->setStyleSheet("padding: 0px;");


    QWidget *spacerLeft = new QWidget(this);
    spacerLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *spacerRight = new QWidget(this);
    spacerRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    toolbar->setMovable(true);

    toolbar->addWidget(spacerLeft);
    toolbar->addAction(homeAction);
    toolbar->addAction(artistsAction);
    toolbar->addAction(albumsAction);
    toolbar->addAction(genresAction);
    toolbar->addWidget(spacerRight);
    toolbar->addAction(helpAction);
    toolbar->addAction(settingsAction);



}

void MainWindow::createActions() {

    homeAction = new QAction("Home", this);
    homeAction->setIcon(QPixmap(":/res/home.svg"));

    artistsAction = new QAction("Artists", this);
    artistsAction->setIcon(QPixmap(":/res/artist.svg"));

    albumsAction = new QAction("Albums", this);
    albumsAction->setIcon(QPixmap(":/res/album.svg"));

    genresAction = new QAction("Genres", this);
    genresAction->setIcon(QPixmap(":/res/genre.svg"));

    helpAction = new QAction("Help", this);
    helpAction->setIcon(QPixmap(":/res/help.svg"));

    settingsAction = new QAction("Settings", this);
    settingsAction->setIcon(QPixmap(":/res/settings.svg"));
}

void MainWindow::createPlayerDock() {
    playerDock = new PlayerDock(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, playerDock, Qt::Vertical); //Add dock to MainWindow
}

void MainWindow::createHomeLayout() {

    homeWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(homeWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(homeWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QVBoxLayout *viewBarLayout = new QVBoxLayout(homeWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);
    //viewBarLayout->setMargin(0);
    //viewBarLayout->setSpacing(0);



    QPushButton *customizeButton = new QPushButton("Customize", homeWidget);
    QMenu *customizeMenu = new QMenu(homeWidget);
    QAction *newAdditions = new QAction("Newest Additions", homeWidget);
    QAction *nowPlaying = new QAction("Now Playing", homeWidget);

    customizeButton->setMaximumWidth(100);
    customizeButton->setMinimumSize(100, 20);

    newAdditions->setCheckable(true);
    newAdditions->setChecked(true);
    newAdditions->setDisabled(true);

    nowPlaying->setCheckable(true);
    nowPlaying->setChecked(false);
    nowPlaying->setDisabled(true);

    customizeMenu->addAction(nowPlaying);
    customizeMenu->addAction(newAdditions);
    customizeButton->setMenu(customizeMenu);


    viewBarLayout->addWidget(customizeButton);
    viewBar->setLayout(viewBarLayout);

    /*
     * Content setup
     */

    QLabel *newAddHeader = new QLabel("New Additions", homeWidget);
    QFont *font = new QFont("Arial", 15, QFont::Bold);
    newAddHeader->setStyleSheet("font-size: 40px;");
    newAddHeader->setContentsMargins(20,10,20,10);

    /*
     * Grid setup
     */

    QWidget *gridWidget = new QWidget(homeWidget);
    QGridLayout *homeGrid = new QGridLayout();

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(homeWidget);
    AlbumModel *albumWidget2 = new AlbumModel(homeWidget);
    AlbumModel *albumWidget3 = new AlbumModel(homeWidget);
    AlbumModel *albumWidget4 = new AlbumModel(homeWidget);
    AlbumModel *albumWidget5 = new AlbumModel(homeWidget);
    AlbumModel *albumWidget6 = new AlbumModel(homeWidget);

    homeGrid->addWidget(albumWidget,0,0);
    homeGrid->addWidget(albumWidget2,0,1);
    homeGrid->addWidget(albumWidget3,1,0);
    homeGrid->addWidget(albumWidget4);
    homeGrid->addWidget(albumWidget5);
    homeGrid->addWidget(albumWidget6);
    //homeGrid->setAlignment(Qt::AlignHCenter);


    QScrollArea  *scrollArea = new QScrollArea();

    gridWidget->setLayout(homeGrid);
    gridWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(gridWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);


    mainLayout->addWidget(viewBar);
    mainLayout->addWidget(newAddHeader);
    mainLayout->addWidget(scrollArea);


    homeWidget->setLayout(mainLayout);


}

void MainWindow::createArtistsLayout() {

    artistsWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(artistsWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(artistsWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(artistsWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);



    QPushButton *customizeButton = new QPushButton("View", artistsWidget);
    QPushButton *sortButton = new QPushButton("Sort by", artistsWidget);
    QMenu *customizeMenu = new QMenu(artistsWidget);
    QMenu *sortMenu = new QMenu(artistsWidget);
    QAction *newAdditions = new QAction("Album covers", artistsWidget);
    QAction *sortByArtist = new QAction("Artist", artistsWidget);
    QAction *sortByAlbum = new QAction("Album", artistsWidget);
    QAction *sortByYear = new QAction("Year", artistsWidget);

    customizeButton->setMaximumWidth(100);
    customizeButton->setMinimumSize(100, 20);

    sortButton->setMaximumWidth(100);
    sortButton->setMinimumSize(100, 20);
    //customizeButton->setStyleSheet("background: white;");

    newAdditions->setCheckable(true);
    newAdditions->setChecked(true);
    newAdditions->setDisabled(true);

    customizeMenu->addAction(newAdditions);
    sortMenu->addAction(sortByArtist);
    sortMenu->addAction(sortByAlbum);
    sortMenu->addAction(sortByYear);

    customizeButton->setMenu(customizeMenu);
    sortButton->setMenu(sortMenu);


    viewBarLayout->addWidget(customizeButton);
    viewBarLayout->addWidget(sortButton);

    viewBar->setLayout(viewBarLayout);

    /*
     * Content setup
     */

    QWidget *horWidget = new QWidget(artistsWidget);
    QHBoxLayout *horLayout = new QHBoxLayout(artistsWidget);

    /*
     * Artist Scroll list setup
     */

    QListWidget *listWidget = new QListWidget();
    QListWidgetItem *artist = new QListWidgetItem("Artist name");
    artist->setTextAlignment(Qt::AlignCenter);
    listWidget->addItem(artist);
    listWidget->setCurrentItem(artist);
    listWidget->setMinimumWidth(150);
    listWidget->setMaximumWidth(150);
    listWidget->setStyleSheet("QListWidget { "
                              "background: transparent;"
                              "font-size: 20px; "
                              "Text-Align: center;"
                              "border: 0px;"
                              "border-right: 2px solid black;"
                              "}");


    /*
     * Grid content setup
     */

    QWidget *gridWidget = new QWidget(artistsWidget);
    QGridLayout *homeGrid = new QGridLayout(artistsWidget);

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(artistsWidget);
    AlbumModel *albumWidget2 = new AlbumModel(artistsWidget);
    AlbumModel *albumWidget3 = new AlbumModel(artistsWidget);
    AlbumModel *albumWidget4 = new AlbumModel(artistsWidget);
    AlbumModel *albumWidget5 = new AlbumModel(artistsWidget);
    AlbumModel *albumWidget6 = new AlbumModel(artistsWidget);

    homeGrid->addWidget(albumWidget,0,0);
    homeGrid->addWidget(albumWidget2,0,1);
    homeGrid->addWidget(albumWidget3,1,0);
    homeGrid->addWidget(albumWidget4);
    homeGrid->addWidget(albumWidget5);
    homeGrid->addWidget(albumWidget6);
    //homeGrid->setAlignment(Qt::AlignHCenter);

    QScrollArea  *scrollArea = new QScrollArea();

    gridWidget->setLayout(homeGrid);
    //gridWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(gridWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);

    horLayout->addWidget(listWidget);
    horLayout->addWidget(scrollArea);
    horWidget->setLayout(horLayout);



    mainLayout->addWidget(viewBar);
    mainLayout->addWidget(horWidget);

    artistsWidget->setLayout(mainLayout);

}

void MainWindow::createAlbumsLayout() {

    albumsWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(albumsWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);


    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(albumsWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(albumsWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);
    //viewBarLayout->setMargin(0);
    //viewBarLayout->setSpacing(0);



    QPushButton *customizeButton = new QPushButton("View", albumsWidget);
    QPushButton *sortButton = new QPushButton("Sort by", albumsWidget);
    QMenu *customizeMenu = new QMenu(albumsWidget);
    QMenu *sortMenu = new QMenu(albumsWidget);
    QAction *newAdditions = new QAction("Album covers", albumsWidget);
    QAction *sortByArtist = new QAction("Artist", albumsWidget);
    QAction *sortByAlbum = new QAction("Album", albumsWidget);
    QAction *sortByYear = new QAction("Year", albumsWidget);

    customizeButton->setMaximumWidth(100);
    customizeButton->setMinimumSize(100, 20);

    sortButton->setMaximumWidth(100);
    sortButton->setMinimumSize(100, 20);
    //customizeButton->setStyleSheet("background: white;");

    newAdditions->setCheckable(true);
    newAdditions->setChecked(true);
    newAdditions->setDisabled(true);

    customizeMenu->addAction(newAdditions);
    sortMenu->addAction(sortByArtist);
    sortMenu->addAction(sortByAlbum);
    sortMenu->addAction(sortByYear);

    customizeButton->setMenu(customizeMenu);
    sortButton->setMenu(sortMenu);


    viewBarLayout->addWidget(customizeButton);
    viewBarLayout->addWidget(sortButton);

    viewBar->setLayout(viewBarLayout);

    /*
     * Content setup
     */

    /*
     * Grid setup
     */

    QWidget *gridWidget = new QWidget(albumsWidget);
    QGridLayout *homeGrid = new QGridLayout();

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(albumsWidget);
    AlbumModel *albumWidget2 = new AlbumModel(albumsWidget);
    AlbumModel *albumWidget3 = new AlbumModel(albumsWidget);
    AlbumModel *albumWidget4 = new AlbumModel(albumsWidget);
    AlbumModel *albumWidget5 = new AlbumModel(albumsWidget);
    AlbumModel *albumWidget6 = new AlbumModel(albumsWidget);

    homeGrid->addWidget(albumWidget,0,0);
    homeGrid->addWidget(albumWidget2,0,1);
    homeGrid->addWidget(albumWidget3,1,0);
    homeGrid->addWidget(albumWidget4);
    homeGrid->addWidget(albumWidget5);
    homeGrid->addWidget(albumWidget6);
    //homeGrid->setAlignment(Qt::AlignHCenter);

    QScrollArea  *scrollArea = new QScrollArea();

    gridWidget->setLayout(homeGrid);
    gridWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(gridWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);


    mainLayout->addWidget(viewBar);
    mainLayout->addWidget(scrollArea);

    albumsWidget->setLayout(mainLayout);

}

void MainWindow::createGenresLayout() {


    genresWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(genresWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(genresWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(genresWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);



    QPushButton *customizeButton = new QPushButton("View", genresWidget);
    QPushButton *sortButton = new QPushButton("Sort by", genresWidget);
    QMenu *customizeMenu = new QMenu(genresWidget);
    QMenu *sortMenu = new QMenu(genresWidget);
    QAction *newAdditions = new QAction("Album covers", genresWidget);
    QAction *sortByArtist = new QAction("Artist", genresWidget);
    QAction *sortByAlbum = new QAction("Album", genresWidget);
    QAction *sortByYear = new QAction("Year", genresWidget);

    customizeButton->setMaximumWidth(100);
    customizeButton->setMinimumSize(100, 20);

    sortButton->setMaximumWidth(100);
    sortButton->setMinimumSize(100, 20);
    //customizeButton->setStyleSheet("background: white;");

    newAdditions->setCheckable(true);
    newAdditions->setChecked(true);
    newAdditions->setDisabled(true);

    customizeMenu->addAction(newAdditions);
    sortMenu->addAction(sortByArtist);
    sortMenu->addAction(sortByAlbum);
    sortMenu->addAction(sortByYear);

    customizeButton->setMenu(customizeMenu);
    sortButton->setMenu(sortMenu);


    viewBarLayout->addWidget(customizeButton);
    viewBarLayout->addWidget(sortButton);

    viewBar->setLayout(viewBarLayout);

    /*
     * Content setup
     */

    QWidget *horWidget = new QWidget(genresWidget);
    QHBoxLayout *horLayout = new QHBoxLayout(genresWidget);

    /*
     * Artist Scroll list setup
     */

    QListWidget *listWidget = new QListWidget();
    QListWidgetItem *artist = new QListWidgetItem("Rock");
    artist->setTextAlignment(Qt::AlignCenter);
    listWidget->addItem(artist);
    listWidget->setCurrentItem(artist);
    listWidget->setMinimumWidth(150);
    listWidget->setMaximumWidth(150);
    listWidget->setStyleSheet("QListWidget { "
                              "background: transparent;"
                              "font-size: 20px; "
                              "Text-Align: center;"
                              "border: 0px;"
                              "border-right: 2px solid black;"
                              "}");


    /*
     * Grid content setup
     */

    QWidget *gridWidget = new QWidget(genresWidget);
    QGridLayout *homeGrid = new QGridLayout(genresWidget);

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(genresWidget);
    AlbumModel *albumWidget2 = new AlbumModel(genresWidget);
    AlbumModel *albumWidget3 = new AlbumModel(genresWidget);
    AlbumModel *albumWidget4 = new AlbumModel(genresWidget);
    AlbumModel *albumWidget5 = new AlbumModel(genresWidget);
    AlbumModel *albumWidget6 = new AlbumModel(genresWidget);

    homeGrid->addWidget(albumWidget,0,0);
    homeGrid->addWidget(albumWidget2,0,1);
    homeGrid->addWidget(albumWidget3,1,0);
    homeGrid->addWidget(albumWidget4);
    homeGrid->addWidget(albumWidget5);
    homeGrid->addWidget(albumWidget6);
    //homeGrid->setAlignment(Qt::AlignHCenter);

    QScrollArea  *scrollArea = new QScrollArea();

    gridWidget->setLayout(homeGrid);
    //gridWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(gridWidget);
    scrollArea->setFrameShape(QFrame::NoFrame);

    horLayout->addWidget(listWidget);
    horLayout->addWidget(scrollArea);
    horWidget->setLayout(horLayout);



    mainLayout->addWidget(viewBar);
    mainLayout->addWidget(horWidget);

    genresWidget->setLayout(mainLayout);

}



/*
 * SLOTS
*/

void MainWindow::onHomeActionClick() {

    viewStack->setCurrentWidget(homeWidget);

}

void MainWindow::onArtistsActionClick() {

    viewStack->setCurrentWidget(artistsWidget);

}

void MainWindow::onAlbumsActionClick() {

    viewStack->setCurrentWidget(albumsWidget);

}

void MainWindow::onGenresActionClick() {

    viewStack->setCurrentWidget(genresWidget);

}



