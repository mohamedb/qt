#include <QtGui/QApplication>
#include "mainwindow.h"
#include<QImage>
#include<sobel.h>



int main(int argc, char *argv[])
{
    Sobel S;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
