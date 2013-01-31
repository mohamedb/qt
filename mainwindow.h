#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <QtGui>
#include<sobel.h>
#include<QPaintEvent>
#include "qpainter.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QString fileName;

    ~MainWindow();
public slots:
        QString open();
        void toGris();
private:
    Ui::MainWindow *ui;
    QPushButton * pushButton,*gris;
    Sobel S;
    QGridLayout * centralLayout;
    QMenu * fileMenu;
    QAction *openAct;
    QAction *quitAct;
    QGroupBox * buttonGroup;
    QGroupBox * colorGroupBox;
};

#endif // MAINWINDOW_H
