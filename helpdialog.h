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
    QWidget *m_welcomeWidget;
    QWidget *m_howToWidget;
    QWidget *m_mainViewWidget;
    QWidget *m_albumViewWidget;
    QWidget *m_artistViewWidget;
    QWidget *m_genreViewWidget;
    QListWidgetItem *m_welcomeItem;
    QListWidgetItem *m_howToItem;
    QListWidgetItem *m_mainViewItem;
    QListWidgetItem *m_albumViewItem;
    QListWidgetItem *m_artistViewItem;
    QListWidgetItem *m_genreViewItem;
    QListWidget *m_helpList;
    QStackedWidget *m_viewStack;
signals:

private slots:
    //void onWelcomeClick();
    void onItemClick(QListWidgetItem *);

};

#endif // HELPDIALOG_H
