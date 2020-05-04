#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playerdock.h"
#include "albummodel.h"
#include "settingsdialog.h"
#include "helpdialog.h"
#include <QMainWindow>
#include <QAction>
#include <QObject>
#include <QStackedWidget>


class MainWindow : public QMainWindow {

    Q_OBJECT

private:
    QAction *m_homeAction;
    QAction *m_artistsAction;
    QAction *m_albumsAction;
    QAction *m_genresAction;
    QAction *m_helpAction;
    QAction *m_settingsAction;
    PlayerDock *m_playerDock;
    QWidget *m_homeWidget;
    QWidget *m_artistsWidget;
    QWidget *m_albumsWidget;
    QWidget *m_genresWidget;
    QStackedWidget *m_viewStack;
    SettingsDialog *m_settingsDialog;
    HelpDialog *m_helpDialog;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createToolbar();
    void createActions();
    void createPlayerDock();
    void createHomeLayout();
    void createArtistsLayout();
    void createAlbumsLayout();
    void createGenresLayout();

    PlayerDock *getPlayerDock() const;
    void setPlayerDock(PlayerDock *value);

signals:

public slots:
    void onHomeActionClick();
    void onArtistsActionClick();
    void onAlbumsActionClick();
    void onGenresActionClick();


};
#endif // MAINWINDOW_H
