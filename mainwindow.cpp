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
    m_settingsDialog = new SettingsDialog(this);
    m_helpDialog = new HelpDialog(this);

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
    m_viewStack = new QStackedWidget();

    m_viewStack->addWidget(m_homeWidget);
    m_viewStack->addWidget(m_artistsWidget);
    m_viewStack->addWidget(m_albumsWidget);
    m_viewStack->addWidget(m_genresWidget);


    this->setCentralWidget(m_viewStack);


    //Handles Toolbar Buttons and view change
    connect(m_homeAction, SIGNAL(triggered()), this, SLOT(onHomeActionClick()));
    connect(m_artistsAction, SIGNAL(triggered()), this, SLOT(onArtistsActionClick()));
    connect(m_albumsAction, SIGNAL(triggered()), this, SLOT(onAlbumsActionClick()));
    connect(m_genresAction, SIGNAL(triggered()), this, SLOT(onGenresActionClick()));


    connect(m_settingsAction, SIGNAL(triggered()), m_settingsDialog, SLOT(exec()));
    connect(m_helpAction, SIGNAL(triggered()), m_helpDialog, SLOT(exec()));



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
    toolbar->addAction(m_homeAction);
    toolbar->addAction(m_artistsAction);
    toolbar->addAction(m_albumsAction);
    toolbar->addAction(m_genresAction);
    toolbar->addWidget(spacerRight);
    toolbar->addAction(m_helpAction);
    toolbar->addAction(m_settingsAction);



}

void MainWindow::createActions() {

    m_homeAction = new QAction("Home", this);
    m_homeAction->setIcon(QPixmap(":/res/home.svg"));

    m_artistsAction = new QAction("Artists", this);
    m_artistsAction->setIcon(QPixmap(":/res/artist.svg"));

    m_albumsAction = new QAction("Albums", this);
    m_albumsAction->setIcon(QPixmap(":/res/album.svg"));

    m_genresAction = new QAction("Genres", this);
    m_genresAction->setIcon(QPixmap(":/res/genre.svg"));

    m_helpAction = new QAction("Help", this);
    m_helpAction->setIcon(QPixmap(":/res/help.svg"));

    m_settingsAction = new QAction("Settings", this);
    m_settingsAction->setIcon(QPixmap(":/res/settings.svg"));
}

void MainWindow::createPlayerDock() {
    m_playerDock = new PlayerDock(this);
    this->addDockWidget(Qt::LeftDockWidgetArea, m_playerDock, Qt::Vertical); //Add dock to MainWindow
}

void MainWindow::createHomeLayout() {

    m_homeWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(m_homeWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(m_homeWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QVBoxLayout *viewBarLayout = new QVBoxLayout(m_homeWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);
    //viewBarLayout->setMargin(0);
    //viewBarLayout->setSpacing(0);



    QPushButton *customizeButton = new QPushButton("Customize", m_homeWidget);
    QMenu *customizeMenu = new QMenu(m_homeWidget);
    QAction *newAdditions = new QAction("Newest Additions", m_homeWidget);
    QAction *nowPlaying = new QAction("Now Playing", m_homeWidget);

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

    QLabel *newAddHeader = new QLabel("New Additions", m_homeWidget);
    QFont *font = new QFont("Arial", 15, QFont::Bold);
    newAddHeader->setStyleSheet("font-size: 40px;");
    newAddHeader->setContentsMargins(20,10,20,10);

    /*
     * Grid setup
     */

    QWidget *gridWidget = new QWidget(m_homeWidget);
    QGridLayout *homeGrid = new QGridLayout();

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(m_homeWidget);
    AlbumModel *albumWidget2 = new AlbumModel(m_homeWidget);
    AlbumModel *albumWidget3 = new AlbumModel(m_homeWidget);
    AlbumModel *albumWidget4 = new AlbumModel(m_homeWidget);
    AlbumModel *albumWidget5 = new AlbumModel(m_homeWidget);
    AlbumModel *albumWidget6 = new AlbumModel(m_homeWidget);

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


    m_homeWidget->setLayout(mainLayout);


}

void MainWindow::createArtistsLayout() {

    m_artistsWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(m_artistsWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(m_artistsWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(m_artistsWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);



    QPushButton *customizeButton = new QPushButton("View", m_artistsWidget);
    QPushButton *sortButton = new QPushButton("Sort by", m_artistsWidget);
    QMenu *customizeMenu = new QMenu(m_artistsWidget);
    QMenu *sortMenu = new QMenu(m_artistsWidget);
    QAction *newAdditions = new QAction("Album covers", m_artistsWidget);
    QAction *sortByArtist = new QAction("Artist", m_artistsWidget);
    QAction *sortByAlbum = new QAction("Album", m_artistsWidget);
    QAction *sortByYear = new QAction("Year", m_artistsWidget);

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

    QWidget *horWidget = new QWidget(m_artistsWidget);
    QHBoxLayout *horLayout = new QHBoxLayout(m_artistsWidget);

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

    QWidget *gridWidget = new QWidget(m_artistsWidget);
    QGridLayout *homeGrid = new QGridLayout(m_artistsWidget);

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(m_artistsWidget);
    AlbumModel *albumWidget2 = new AlbumModel(m_artistsWidget);
    AlbumModel *albumWidget3 = new AlbumModel(m_artistsWidget);
    AlbumModel *albumWidget4 = new AlbumModel(m_artistsWidget);
    AlbumModel *albumWidget5 = new AlbumModel(m_artistsWidget);
    AlbumModel *albumWidget6 = new AlbumModel(m_artistsWidget);

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

    m_artistsWidget->setLayout(mainLayout);

}

void MainWindow::createAlbumsLayout() {

    m_albumsWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(m_albumsWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);


    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(m_albumsWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(m_albumsWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);
    //viewBarLayout->setMargin(0);
    //viewBarLayout->setSpacing(0);



    QPushButton *customizeButton = new QPushButton("View", m_albumsWidget);
    QPushButton *sortButton = new QPushButton("Sort by", m_albumsWidget);
    QMenu *customizeMenu = new QMenu(m_albumsWidget);
    QMenu *sortMenu = new QMenu(m_albumsWidget);
    QAction *newAdditions = new QAction("Album covers", m_albumsWidget);
    QAction *sortByArtist = new QAction("Artist", m_albumsWidget);
    QAction *sortByAlbum = new QAction("Album", m_albumsWidget);
    QAction *sortByYear = new QAction("Year", m_albumsWidget);

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

    QWidget *gridWidget = new QWidget(m_albumsWidget);
    QGridLayout *homeGrid = new QGridLayout();

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(m_albumsWidget);
    AlbumModel *albumWidget2 = new AlbumModel(m_albumsWidget);
    AlbumModel *albumWidget3 = new AlbumModel(m_albumsWidget);
    AlbumModel *albumWidget4 = new AlbumModel(m_albumsWidget);
    AlbumModel *albumWidget5 = new AlbumModel(m_albumsWidget);
    AlbumModel *albumWidget6 = new AlbumModel(m_albumsWidget);

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

    m_albumsWidget->setLayout(mainLayout);

}

void MainWindow::createGenresLayout() {


    m_genresWidget = new QWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(m_genresWidget);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    /*
     * ViewBar setup
     */

    QWidget *viewBar = new QWidget(m_genresWidget);
    viewBar->setStyleSheet(".QWidget { background-color: #B4B4B4 }");
    viewBar->setContentsMargins(0,0,0,0);

    QHBoxLayout *viewBarLayout = new QHBoxLayout(m_genresWidget);
    viewBarLayout->setAlignment(Qt::AlignTop);
    viewBar->setMaximumHeight(100);



    QPushButton *customizeButton = new QPushButton("View", m_genresWidget);
    QPushButton *sortButton = new QPushButton("Sort by", m_genresWidget);
    QMenu *customizeMenu = new QMenu(m_genresWidget);
    QMenu *sortMenu = new QMenu(m_genresWidget);
    QAction *newAdditions = new QAction("Album covers", m_genresWidget);
    QAction *sortByArtist = new QAction("Artist", m_genresWidget);
    QAction *sortByAlbum = new QAction("Album", m_genresWidget);
    QAction *sortByYear = new QAction("Year", m_genresWidget);

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

    QWidget *horWidget = new QWidget(m_genresWidget);
    QHBoxLayout *horLayout = new QHBoxLayout(m_genresWidget);

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

    QWidget *gridWidget = new QWidget(m_genresWidget);
    QGridLayout *homeGrid = new QGridLayout(m_genresWidget);

    /*
     * Album
     */

    AlbumModel *albumWidget = new AlbumModel(m_genresWidget);
    AlbumModel *albumWidget2 = new AlbumModel(m_genresWidget);
    AlbumModel *albumWidget3 = new AlbumModel(m_genresWidget);
    AlbumModel *albumWidget4 = new AlbumModel(m_genresWidget);
    AlbumModel *albumWidget5 = new AlbumModel(m_genresWidget);
    AlbumModel *albumWidget6 = new AlbumModel(m_genresWidget);

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

    m_genresWidget->setLayout(mainLayout);

}



/*
 * SLOTS
*/

void MainWindow::onHomeActionClick() {

    m_viewStack->setCurrentWidget(m_homeWidget);

}

void MainWindow::onArtistsActionClick() {

    m_viewStack->setCurrentWidget(m_artistsWidget);

}

void MainWindow::onAlbumsActionClick() {

    m_viewStack->setCurrentWidget(m_albumsWidget);

}

void MainWindow::onGenresActionClick() {

    m_viewStack->setCurrentWidget(m_genresWidget);

}



