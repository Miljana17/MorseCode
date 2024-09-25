#include "mainwindow.h"
#include "ColorFillButton.h"

#include "circlewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;



    w.show();

    return a.exec();
}
