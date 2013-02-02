#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QGroupBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



     QWidget *widget = new QWidget;
     setCentralWidget(widget);
     Sobel* my_widget = new Sobel(); // You need to create the widget on heap so that it is persistent when you exit the function / constructor
     //setCentralWidget(my_widget); // Added this

     //*******************************************************
     /* GroupBox for the controls */
     buttonGroup = new QGroupBox(this);
     buttonGroup->setFixedWidth(130);
     buttonGroup->setTitle(tr("Actions"));

     QVBoxLayout *buttonGroupLayout = new QVBoxLayout(buttonGroup);

     //
     ui->pushButton = new QPushButton(tr("Parcourir"),buttonGroup);
     buttonGroupLayout->addWidget(ui->pushButton);
     ui->gris = new QPushButton(tr("Gris"),buttonGroup);
     buttonGroupLayout->addWidget(ui->gris);
     // Put all the elements in a GridLayout
     centralLayout = new QGridLayout;
     // The widget for the Sobel display spans 3 rows
     centralLayout->addWidget(my_widget, 0, 0, 3, 1);
     centralLayout->addWidget(buttonGroup,0,1);
     widget->setLayout(centralLayout);
     //*******************************************************
     connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(open(void)));
     connect(ui->gris,SIGNAL(pressed()),this,SLOT(toGris()));
     connect(ui->gris,SIGNAL(pressed()),this,SLOT(update()));

}
QString MainWindow::open(){
   this->fileName = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "/home/*", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
   return fileName;

}
void MainWindow::toGris(){
    this->S.toGray(fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}



