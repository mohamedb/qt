#ifndef SOBEL_H
#define SOBEL_H
#include<QImage>
#include<QString>
#include<QWidget>
class Sobel : public QWidget
{
public :
    int source_height;int source_width;
    QImage source_image;QImage gray_image;QImage *edge_image;
    double *Gx,*Gy;
    Sobel();
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void toGray(QString file_name );
    void toEdge();

};

#endif // SOBEL_H
