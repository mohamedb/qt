#ifndef SOBEL_H
#define SOBEL_H
#include<QImage>
#include<QString>
#include<QWidget>
class Sobel : public QWidget
{
public :
    int srcHeight;int srcWidth;
    QImage srcImg;QImage grayImg;QImage *edgeImg;
    double *Gx,*Gy;
    Sobel();
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void toGray(QString nomficher );
    void toEdge();

};

#endif // SOBEL_H
