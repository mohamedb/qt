#include <QtGui/QApplication.h>
#include "mainwindow.h"
#include<QImage>
#include<sobel.h>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
