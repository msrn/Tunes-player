#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H
#include <QDialog>
#include <QObject>
#include <QStackedWidget>
#include <QWidget>

class SetupDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetupDialog(QWidget* parent = nullptr);
    void createFirstPage();
    void createSecondPage();

    bool getQuit() const;

private:
    QPushButton *m_nextButton;
    QPushButton *m_backButton;
    QPushButton *m_finishButton;
    QPushButton *m_quitButton;
    QPushButton *m_addFolder;
    QWidget *m_firstPage;
    QWidget *m_secondPage;
    QStackedWidget *m_stackWidget;
    bool m_quit;

signals:

private slots:
    void onAddClick();
    void onNextClick();
    void onBackClick();
    void onFinishClick();
    void onQuitClick();

};

#endif // SETUPDIALOG_H
