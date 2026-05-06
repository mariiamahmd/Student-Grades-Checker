#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Apply a clean, modern style default
    a.setStyle("Fusion");

    MainWindow w;
    w.show();

    return a.exec();
}