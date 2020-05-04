#ifndef ALBUMMODEL_H
#define ALBUMMODEL_H

#include <QFrame>
#include <QWidget>

class AlbumModel : public QFrame {
    Q_OBJECT
private:
    //QWidget *albumWidget;
public:
    explicit AlbumModel(QWidget *parent = nullptr);
    void createLayout();

signals:

};

#endif // ALBUMMODEL_H
