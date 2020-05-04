#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>


class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    void createLayout();
private:
    QGroupBox *fileSettingsGroup;
    QGroupBox *audioSettingsGroup;
    QDialogButtonBox *buttonBox;
    QPushButton *addFolder;
signals:

private slots:
    void onAddClick();

};

#endif // SETTINGSDIALOG_H
