#include "sobel.h"
#include<math.h>
#include <QWidget>
#include <QBrush>
#include <QPen>
#include <QPainter>


Sobel::Sobel()
{
    Gx = new double[9];
    Gy = new double[9];

    /* Sobel */
    Gx[0] = 1.0; Gx[1] = 0.0; Gx[2] = -1.0;
    Gx[3] = 2.0; Gx[4] = 0.0; Gx[5] = -2.0;
    Gx[6] = 1.0; Gx[7] = 0.0; Gx[8] = -1.0;

    Gy[0] =  -1.0; Gy[1] =  -2.0; Gy[2] = - 1.0;
    Gy[3] =   0.0; Gy[4] =   0.0; Gy[5] =   0.0;
    Gy[6] =   1.0; Gy[7] =   2.0; Gy[8] =   1.0;
}


void Sobel::toGray(QString nomfichier){
    try{
    //nomfichier="C:\\Users\\Mohamed\\Desktop\\man\\gray.tif";


    }
    catch(...){}

    srcImg=QImage(nomfichier);
    srcImg=srcImg.convertToFormat(QImage::Format_ARGB32);
    srcWidth=srcImg.width();srcHeight=srcImg.height();
    //****GrayWith...
    //****
    //---------------Conversion en niveaux de gris-----------------------
    grayImg=QImage(srcWidth,srcHeight,QImage::Format_ARGB32);
    double gray;int i,j;
    QRgb pixel;
    for(i=0;i<srcWidth;i++){
        for(j=0;j<srcHeight;j++){
            pixel=srcImg.pixel(i,j);
            gray=(0.29*qRed(pixel)+0.58*qGreen(pixel)+0.12*qBlue(pixel));
            grayImg.setPixel(i,j,qRgb(int(gray),int(gray),int(gray)));
        }//finFor j->srcHeight
    }//finFor i->srcWidth
    //-----------------fin Conversion en niveaux de Gris------------------
    edgeImg=new QImage(srcWidth,srcHeight,QImage::Format_ARGB32);
    toEdge();


}//finFunction toGray()



void Sobel::toEdge(){
    QRgb pixel;
    double value_gx,value_gy;
    double sum_coeff_gx,sum_coeff_gy;
    float sobel_norm[srcWidth*srcHeight];
    float max=0.0;
    QColor my_color;
    for(int i=0;i<srcWidth;i++){
        for(int j=0;j<srcHeight;j++){
            value_gx=0.0;value_gy=0.0;sum_coeff_gx=0.0;sum_coeff_gy=0.0;
            for(int k=0;k<3;k++){
                for(int p=0;p<3;p++){
                    pixel=grayImg.pixel((i+1+1-k),(j+1+1-p));
                    value_gx+=Gx[p*3+k]*qRed(pixel);
                    value_gy+=Gy[p*3+k]*qRed(pixel);
                }//fin For P->3
            }//fin For k->3
            sobel_norm[i+j*srcWidth]=sqrt(value_gx*value_gx + value_gy*value_gy)/1.0;
            max=sobel_norm[i+j*srcWidth]>max ? sobel_norm[i+j*srcWidth]:max;
        }//fin For j->srcHeight
    }//fin For i->srcWidth
   int c = rand() % 255;         // v1 in the range 0 to 99
    //Enregistrement
    for(int i=0;i<srcWidth;i++){
        for(int j=0;j<srcHeight;j++){
            my_color.setHsv( 0  ,0, 255-int(255.0*sobel_norm[i + j * srcWidth]/max));
            edgeImg->setPixel(i,j,my_color.rgb());
        }//fin For j
    }//fin For i
    edgeImg->save("C:\\Users\\Mohamed\\Desktop\\man\\new.png",0,-1);
}
void Sobel::paintEvent(QPaintEvent * )
{

  QRectF target(0.0, 0.0, 990.0, 990.0);
  QRectF source(00.0, 00.0, 990.0, 990.0);
  QImage image("C:\\Users\\Mohamed\\Desktop\\man\\new.png");
  QPainter painter(this);
  painter.drawImage(target, image, source);

}


