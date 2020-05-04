#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QWidget>

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = nullptr);
    void createLayout();
    void createWelcome();
    void createHowTo();
    void createMain();
    void createArtist();
    void createAlbum();
    void createGenre();

private:
    QWidget *welcomeWidget;
    QWidget *howToWidget;
    QWidget *mainViewWidget;
    QWidget *albumViewWidget;
    QWidget *artistViewWidget;
    QWidget *genreViewWidget;
    QListWidgetItem *welcomeItem;
    QListWidgetItem *howToItem;
    QListWidgetItem *mainViewItem;
    QListWidgetItem *albumViewItem;
    QListWidgetItem *artistViewItem;
    QListWidgetItem *genreViewItem;
    QListWidget *helpList;
    QStackedWidget *viewStack;
signals:

private slots:
    //void onWelcomeClick();
    void onItemClick(QListWidgetItem *);

};

#endif // HELPDIALOG_H
