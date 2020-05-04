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

    connect(m_playButton, SIGNAL(clicked()), this, SLOT(onPlayButtonClick()));

}

void PlayerDock::createLayout() {

    QWidget *dockLayout = new QWidget(this);
    QVBoxLayout *parentLayout = new QVBoxLayout(this);

    /*
     * Album cover
     */
    QLabel *albumImageLabel = new QLabel();
    m_albumImage = new QPixmap(":/res/empty_album.png");
    albumImageLabel->setPixmap(*m_albumImage);


    /*
     *Track labels
     */
    QVBoxLayout *trackLabelLayout = new QVBoxLayout(this);

    m_trackLabel = new QLabel("Track Name");
    m_artistLabel = new QLabel("Artist Name");
    m_albumLabel = new QLabel("Album Name");
    m_albumArtistLabel = new QLabel("Album Artist Name");
    m_genreLabel = new QLabel("Rock");
    m_yearLabel = new QLabel("2009");


    QLabel *trackAndArtistLabel = new QLabel();
    trackAndArtistLabel->setText(m_trackLabel->text() + " - " + m_artistLabel->text());
    trackAndArtistLabel->setStyleSheet("font-size: 20px;");
    QLabel *albumAndAlbumArtistLabel = new QLabel();
    albumAndAlbumArtistLabel->setText(m_albumLabel->text() + " by " + m_albumArtistLabel->text());
    QLabel *genreAndYearLabel = new QLabel();
    genreAndYearLabel->setText(m_yearLabel->text() + " " + m_genreLabel->text());
    genreAndYearLabel->setStyleSheet("font-size: 10px;");



    trackLabelLayout->addWidget(trackAndArtistLabel);
    trackLabelLayout->addWidget(albumAndAlbumArtistLabel);
    trackLabelLayout->addWidget(genreAndYearLabel);

    /*
     *Track list
     */

    m_trackListWidget = new QListWidget();
    m_trackListWidget->addItem("Play queue currently empty");

    /*
     * PLay,pause,volume controls
     */

    QHBoxLayout *mediaControlsLayout = new QHBoxLayout(this);

    QLabel *volumeLabel = new QLabel("Vol:");
    m_volumePercent = new QLabel("100%");
    m_volumePercent->setStyleSheet("font-size: 10px;");
    volumeLabel->setStyleSheet("font-size: 10px;");

    mediaControlsLayout->setAlignment(Qt::AlignCenter);
    mediaControlsLayout->setMargin(5);
    mediaControlsLayout->setSpacing(5);

    mediaControlsLayout->addWidget(m_shuffleButton);
    mediaControlsLayout->addWidget(m_repeatButton);
    mediaControlsLayout->addSpacing(30);
    mediaControlsLayout->addWidget(m_previousButton);
    mediaControlsLayout->addWidget(m_playButton);
    mediaControlsLayout->addWidget(m_nextButton);
    mediaControlsLayout->addSpacing(20);
    mediaControlsLayout->addWidget(volumeLabel);
    mediaControlsLayout->addWidget(m_volumeSlider);
    mediaControlsLayout->addWidget(m_volumePercent);


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
    parentLayout->addWidget(m_trackListWidget);
    parentLayout->addLayout(mediaControlsLayout);
    parentLayout->addLayout(trackInfoLayout);

    dockLayout->setLayout(parentLayout);

    this->setWidget(dockLayout);


}

void PlayerDock::createButtons() {

    m_playButton = new QPushButton(this);
    m_nextButton = new QPushButton(this);
    m_previousButton = new QPushButton(this);
    m_shuffleButton = new QPushButton(this);
    m_repeatButton = new QPushButton(this);

    m_playButton->setIcon(QPixmap(":/res/play.svg"));
    m_nextButton->setIcon(QPixmap(":/res/next.svg"));
    m_previousButton->setIcon(QPixmap(":/res/previous.svg"));
    m_shuffleButton->setIcon(QPixmap(":/res/shuffle.svg"));
    m_repeatButton->setIcon(QPixmap(":/res/repeat.svg"));


    m_playButton->setMaximumWidth(30);
    m_nextButton->setMaximumWidth(30);
    m_playButton->setMaximumWidth(30);
    m_previousButton->setMaximumWidth(30);
    m_shuffleButton->setMaximumWidth(30);
    m_repeatButton->setMaximumWidth(30);

    m_shuffleButton->setFlat(true);
    m_nextButton->setFlat(true);
    m_playButton->setFlat(true);
    m_previousButton->setFlat(true);
    m_repeatButton->setFlat(true);
    m_nextButton->setFlat(true);


    m_shuffleButton->setToolTip("Shuffle playlist");
    m_repeatButton->setToolTip("Repeat one song");
    m_playButton->setToolTip("Play or pause song");
    m_nextButton->setToolTip("Next song");
    m_previousButton->setToolTip("Previous song");

    m_volumeSlider = new QSlider(Qt::Orientation::Horizontal);
    m_volumeSlider->setToolTip("Volume");
    m_volumeSlider->setMaximumWidth(90);
    m_volumeSlider->setValue(100);
    m_volumeSlider->setStyleSheet("height: 10px;");


}

/*
 * SLOTS
 *
*/

void PlayerDock::onPlayButtonClick() {
    m_playButton->setIcon(QPixmap(":/res/pause.svg"));
}
