#include "playerdock.h"
#include <QLabel>
#include <QVBoxLayout>


PlayerDock::PlayerDock(QWidget *parent) : QDockWidget(parent) {

    this->setWindowTitle("Now playing");
    this->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->setMaximumWidth(350);
    //this->setContentsMargins(0,0,0,0);
    //this->setStyleSheet("padding: 0px;");

    this->createButtons();
    this->createLayout();

    connect(playButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClick()));

}

void PlayerDock::createLayout() {

    QWidget *dockLayout = new QWidget(this);
    QVBoxLayout *parentLayout = new QVBoxLayout(this);

    /*
     * Album cover
     */
    QLabel *albumImageLabel = new QLabel();
    albumImage = new QPixmap(":/res/empty_album.png");
    albumImageLabel->setPixmap(*albumImage);


    /*
     *Track labels
     */
    QVBoxLayout *trackLabelLayout = new QVBoxLayout(this);

    trackLabel = new QLabel("Track Name");
    artistLabel = new QLabel("Artist Name");
    albumLabel = new QLabel("Album Name");
    albumArtistLabel = new QLabel("Album Artist Name");
    genreLabel = new QLabel("Rock");
    yearLabel = new QLabel("2009");


    QLabel *trackAndArtistLabel = new QLabel();
    trackAndArtistLabel->setText(trackLabel->text() + " - " + artistLabel->text());
    trackAndArtistLabel->setStyleSheet("font-size: 20px;");
    QLabel *albumAndAlbumArtistLabel = new QLabel();
    albumAndAlbumArtistLabel->setText(albumLabel->text() + " by " + albumArtistLabel->text());
    QLabel *genreAndYearLabel = new QLabel();
    genreAndYearLabel->setText(yearLabel->text() + " " + genreLabel->text());
    genreAndYearLabel->setStyleSheet("font-size: 10px;");



    trackLabelLayout->addWidget(trackAndArtistLabel);
    trackLabelLayout->addWidget(albumAndAlbumArtistLabel);
    trackLabelLayout->addWidget(genreAndYearLabel);

    /*
     *Track list
     */

    trackListWidget = new QListWidget();
    trackListWidget->addItem("Play queue currently empty");

    /*
     * PLay,pause,volume controls
     */

    QHBoxLayout *mediaControlsLayout = new QHBoxLayout(this);

    QLabel *volumeLabel = new QLabel("Vol:");
    volumePercent = new QLabel("100%");
    volumePercent->setStyleSheet("font-size: 10px;");
    volumeLabel->setStyleSheet("font-size: 10px;");

    mediaControlsLayout->setAlignment(Qt::AlignCenter);
    mediaControlsLayout->setMargin(5);
    mediaControlsLayout->setSpacing(5);

    mediaControlsLayout->addWidget(shuffleButton);
    mediaControlsLayout->addWidget(repeatButton);
    mediaControlsLayout->addSpacing(30);
    mediaControlsLayout->addWidget(previousButton);
    mediaControlsLayout->addWidget(playButton);
    mediaControlsLayout->addWidget(nextButton);
    mediaControlsLayout->addSpacing(20);
    mediaControlsLayout->addWidget(volumeLabel);
    mediaControlsLayout->addWidget(volumeSlider);
    mediaControlsLayout->addWidget(volumePercent);


    /*
     * track lenght slider and label
     */
    QHBoxLayout *trackInfoLayout = new QHBoxLayout(this);
    QSlider *trackLengthSlider = new QSlider(Qt::Orientation::Horizontal);
    QLabel *trackLengthLabel = new QLabel("0:00/0:00");
    trackLengthLabel->setStyleSheet("font-size: 10px;");
    trackInfoLayout->addWidget(trackLengthSlider);
    trackInfoLayout->addWidget(trackLengthLabel);


    parentLayout->addWidget(albumImageLabel);
    parentLayout->addLayout(trackLabelLayout);
    parentLayout->addWidget(trackListWidget);    
    parentLayout->addLayout(mediaControlsLayout);
    parentLayout->addLayout(trackInfoLayout);

    dockLayout->setLayout(parentLayout);

    this->setWidget(dockLayout);


}

void PlayerDock::createButtons() {

    playButton = new QPushButton(this);
    nextButton = new QPushButton(this);
    previousButton = new QPushButton(this);
    shuffleButton = new QPushButton(this);
    repeatButton = new QPushButton(this);

    playButton->setIcon(QPixmap(":/res/play.svg"));
    nextButton->setIcon(QPixmap(":/res/next.svg"));
    previousButton->setIcon(QPixmap(":/res/previous.svg"));
    shuffleButton->setIcon(QPixmap(":/res/shuffle.svg"));
    repeatButton->setIcon(QPixmap(":/res/repeat.svg"));


    playButton->setMaximumWidth(30);
    nextButton->setMaximumWidth(30);
    playButton->setMaximumWidth(30);
    previousButton->setMaximumWidth(30);
    shuffleButton->setMaximumWidth(30);
    repeatButton->setMaximumWidth(30);

    shuffleButton->setFlat(true);
    nextButton->setFlat(true);
    playButton->setFlat(true);
    previousButton->setFlat(true);
    repeatButton->setFlat(true);
    nextButton->setFlat(true);


    shuffleButton->setToolTip("Shuffle playlist");
    repeatButton->setToolTip("Repeat one song");
    playButton->setToolTip("Play or pause song");
    nextButton->setToolTip("Next song");
    previousButton->setToolTip("Previous song");

    volumeSlider = new QSlider(Qt::Orientation::Horizontal);
    volumeSlider->setToolTip("Volume");
    volumeSlider->setMaximumWidth(90);
    volumeSlider->setValue(100);
    volumeSlider->setStyleSheet("height: 10px;");


}

/*
 * SLOTS
 *
*/

void PlayerDock::onPlayButtonClick() {
    playButton->setIcon(QPixmap(":/res/pause.svg"));
}
