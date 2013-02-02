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

    Gy[0] = -1.0; Gy[1] = -2.0; Gy[2] = - 1.0;
    Gy[3] = 0.0; Gy[4] = 0.0; Gy[5] = 0.0;
    Gy[6] = 1.0; Gy[7] = 2.0; Gy[8] = 1.0;
}


void Sobel::toGray(QString nomfichier){
    try{
    //nomfichier="C:\\Users\\Mohamed\\Desktop\\man\\gray.tif";


    }
    catch(...){}

    source_image=QImage(nomfichier);
    source_image=source_image.convertToFormat(QImage::Format_ARGB32);
    source_width=source_image.width();source_height=source_image.height();
    //****GrayWith...
    //****
    //---------------Conversion en niveaux de gris-----------------------
    gray_image=QImage(source_width,source_height,QImage::Format_ARGB32);
    double gray;int i,j;
    QRgb pixel;
    for(i=0;i<source_width;i++){
        for(j=0;j<source_height;j++){
            pixel=source_image.pixel(i,j);
            gray=(0.29*qRed(pixel)+0.58*qGreen(pixel)+0.12*qBlue(pixel));
            gray_image.setPixel(i,j,qRgb(int(gray),int(gray),int(gray)));
        }//finFor j->source_height
    }//finFor i->source_width
    //-----------------fin Conversion en niveaux de Gris------------------
    edge_image=new QImage(source_width,source_height,QImage::Format_ARGB32);
    toEdge();


}//finFunction toGray()



void Sobel::toEdge(){
    QRgb pixel;
    double value_gx,value_gy;
    double sum_coeff_gx,sum_coeff_gy;
    float sobel_norm[source_width*source_height];
    float max=0.0;
    QColor my_color;
    for(int i=0;i<source_width;i++){
        for(int j=0;j<source_height;j++){
            value_gx=0.0;value_gy=0.0;sum_coeff_gx=0.0;sum_coeff_gy=0.0;
            for(int k=0;k<3;k++){
                for(int p=0;p<3;p++){
                    pixel=gray_image.pixel((i+1+1-k),(j+1+1-p));
                    value_gx+=Gx[p*3+k]*qRed(pixel);
                    value_gy+=Gy[p*3+k]*qRed(pixel);
                }//fin For P->3
            }//fin For k->3
            sobel_norm[i+j*source_width]=sqrt(value_gx*value_gx + value_gy*value_gy)/1.0;
            max=sobel_norm[i+j*source_width]>max ? sobel_norm[i+j*source_width]:max;
        }//fin For j->source_height
    }//fin For i->source_width
   int c = rand() % 255; // v1 in the range 0 to 99
    //Enregistrement
    for(int i=0;i<source_width;i++){
        for(int j=0;j<source_height;j++){
            my_color.setHsv( 0 ,0, 255-int(255.0*sobel_norm[i + j * source_width]/max));
            edge_image->setPixel(i,j,my_color.rgb());
        }//fin For j
    }//fin For i
    edge_image->save("C:\\Users\\Mohamed\\Desktop\\man\\new.png",0,-1);
}
void Sobel::paintEvent(QPaintEvent * )
{

  QRectF target(0.0, 0.0, 990.0, 990.0);
  QRectF source(00.0, 00.0, 990.0, 990.0);
  QImage image_to_print("C:\\Users\\Mohamed\\Desktop\\man\\new.png");
  QPainter painter(this);
  painter.drawImage(target, image_to_print, source);

}

