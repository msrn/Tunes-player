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
    QDockWidget *m_player;
    QPixmap *m_albumImage;
    QPushButton *m_playButton;
    QPushButton *m_nextButton;
    QPushButton *m_previousButton;
    QPushButton *m_shuffleButton;
    QPushButton *m_repeatButton;
    QSlider *m_volumeSlider;
    QListWidget *m_trackListWidget;
    QLabel *m_volumePercent;
    QLabel *m_trackLabel;
    QLabel *m_artistLabel;
    QLabel *m_albumLabel;
    QLabel *m_albumArtistLabel;
    QLabel *m_yearLabel;
    QLabel *m_genreLabel;
public:
    explicit PlayerDock(QWidget *parent = nullptr);
    void createLayout();
    void createButtons();

public slots:
    void onPlayButtonClick();
signals:

};

#endif // PLAYERDOCK_H
