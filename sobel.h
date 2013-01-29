#ifndef SOBEL_H
#define SOBEL_H
#include<QImage>
#include<QString>
class Sobel
{
public :
    int srcHeight;int srcWidth;
    QImage srcImg;QImage grayImg;QImage *edgeImg;
    double *Gx,*Gy;
public:
    void toGray(QString nomficher );
    void toEdge();
    Sobel();
};

#endif // SOBEL_H
