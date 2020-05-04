#include "albummodel.h"

#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>


AlbumModel::AlbumModel(QWidget *parent) : QFrame(parent) {


    createLayout();


}

void AlbumModel::createLayout() {

    //QWidget *albumWidget = new QWidget();
    QHBoxLayout *baseAlbumLayout = new QHBoxLayout();
    QLabel *albumCover = new QLabel();
    QPixmap *image = new QPixmap(":/res/empty_album.png");
    QPixmap newImage = image->scaled(QSize(150, 150), Qt::IgnoreAspectRatio);
    albumCover->setPixmap(newImage);


    QWidget *albumInfo = new QWidget();
    QVBoxLayout *albumInfoLayout = new QVBoxLayout();
    albumInfoLayout->setContentsMargins(0,0,0,0);
    albumInfoLayout->setSpacing(0);
    albumInfoLayout->setAlignment(Qt::AlignTop);

    QLabel *albumLabel = new QLabel("Album name");
    albumLabel->setStyleSheet("font-size: 25px;");
    QLabel *artistLabel = new QLabel("Artist Name");
    artistLabel->setStyleSheet("font-size: 20px;");
    QLabel *yearLabel = new QLabel("2009");
    yearLabel->setStyleSheet("font-size: 15px;");
    QLabel *genreLabel = new QLabel("Rock");
    genreLabel->setStyleSheet("font-size: 15px;");

    QSpacerItem *spacer = new QSpacerItem(0, 38, QSizePolicy::Minimum, QSizePolicy::Maximum);


    QPushButton *playButton = new QPushButton("Play");
    //playButton->setStyleSheet("qproperty-alignment: 'AlignBottom';");

    playButton->setMaximumWidth(100);
    playButton->setIcon(QPixmap(":/res/play.svg"));

    albumInfoLayout->addWidget(albumLabel);
    albumInfoLayout->addWidget(artistLabel);
    albumInfoLayout->addWidget(yearLabel);
    albumInfoLayout->addWidget(genreLabel);
    albumInfoLayout->addItem(spacer);
    albumInfoLayout->addWidget(playButton);
    albumInfo->setLayout(albumInfoLayout);


    baseAlbumLayout->addWidget(albumCover);
    baseAlbumLayout->addWidget(albumInfo);

    this->setLayout(baseAlbumLayout);
    this->setMaximumSize(350,200);
    this->setObjectName("albumWidget"); //css Id name for albumWidget
    this->setStyleSheet("#albumWidget { border: 1px solid black }"); //only affects albumWidget not children
    //this->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
}
