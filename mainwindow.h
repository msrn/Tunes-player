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
    QAction *homeAction;
    QAction *artistsAction;
    QAction *albumsAction;
    QAction *genresAction;
    QAction *helpAction;
    QAction *settingsAction;
    PlayerDock *playerDock;
    QWidget *homeWidget;
    QWidget *artistsWidget;
    QWidget *albumsWidget;
    QWidget *genresWidget;
    QStackedWidget *viewStack;
    SettingsDialog *settingsDialog;
    HelpDialog *helpDialog;

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
