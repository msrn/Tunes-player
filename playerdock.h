#ifndef PLAYERDOCK_H
#define PLAYERDOCK_H

#include <QWidget>
#include <QDockWidget>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QListWidget>
#include <QLabel>

class PlayerDock : public QDockWidget
{
    Q_OBJECT
private:
    QDockWidget *player;
    QPixmap *albumImage;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *shuffleButton;
    QPushButton *repeatButton;
    QSlider *volumeSlider;
    QListWidget *trackListWidget;
    QLabel *volumePercent;
    QLabel *trackLabel;
    QLabel *artistLabel;
    QLabel *albumLabel;
    QLabel *albumArtistLabel;
    QLabel *yearLabel;
    QLabel *genreLabel;
public:
    explicit PlayerDock(QWidget *parent = nullptr);
    void createLayout();
    void createButtons();

public slots:
    void onPlayButtonClick();
signals:

};

#endif // PLAYERDOCK_H
