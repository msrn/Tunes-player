#include "mainwindow.h"
#include "setupdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SetupDialog s;
    s.exec();
    if (s.getQuit() == true)
        return 1;


    w.show();
    return a.exec();

}
