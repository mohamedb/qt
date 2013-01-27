#include "sobel.h"
#include<math.h>

Sobel::Sobel()
{
   // this->contrast();
    this->run();
    //this->myfilter();
    //this->play();
}


void Sobel::run()
{
    QImage m_Image("C:\\Users\\Mohamed\\Desktop\\man\\gray.png",  0 );
    //qDebug() << "thread id " << (int) QThread::currentThreadId();

    quint32 kernelSize = 3;
    qint32 kern = (kernelSize-1)/2.0;
    quint32 r1=0, r2=0, g1=0, g2=0, b1=0, b2=0;

    int kernelx[] = {-1,0,1,-2,0,2,-1,0,1};
    int kernely[] = {-1,-2,-1,0,0,0,1,2,1};

    quint8 z=0, r=0, g=0, b=0;

    m_Image.convertToFormat(QImage::Format_ARGB32);

    QRgb *peekScanLine;
    QImage result(m_Image.width(), m_Image.height(), m_Image.format());
    QPoint point;

    for (quint32 y = kern; y < m_Image.height() - kern; ++y) {
        for (quint32 x = kern; x < m_Image.width() - kern; ++x) {
            for(qint32 ky = -kern; ky <= kern; ++ky) {
                // Could be optimized by keeping scanlines in memory and
                // not calling scanLine ky times for each pixel
                peekScanLine = (QRgb *)m_Image.scanLine(y+ky);

                for(qint32 kx = -kern; kx <= kern; ++kx) {
                    r1 += kernelx[z] * qRed(peekScanLine[x+kx]);
                    g1 += kernelx[z] * qGreen(peekScanLine[x+kx]);
                    b1 += kernelx[z] * qBlue(peekScanLine[x+kx]);

                    r2 += kernely[z] * qRed(peekScanLine[x+kx]);
                    g2 += kernely[z] * qGreen(peekScanLine[x+kx]);
                    b2 += kernely[z] * qBlue(peekScanLine[x+kx]);

                    z++;
                }
            }

            r = sqrt(r1*r1+r2*r2);//sqrt(r1*r1 + r2*r1 );
            g = sqrt(g1*g1+g2*g2);//sqrt(g1*g1 + g2*g2);
            b = sqrt(b1*b1+b2*b2);//sqrt(b1*b1 + b1*b2);
            r=(0.3*r+0.6*g+0.1*b);

            r1=0, r2=0, g1=0, g2=0, b1=0, b2=0, z=0;

            point.setX(x);
            point.setY(y);
            m_Image.setPixel(point, qRgba(r,r,r,255));r=0;

        }
    }

    m_Image.save("C:\\Users\\Mohamed\\Desktop\\man\\res.png",  0,-1);
    //emit manipulationDone();
}
void Sobel::contrast(){
     QImage I("C:\\Users\\Mohamed\\Desktop\\man\\goo.png",  0 );
     for(int i=2;i <=I.height()-1;i++){
         for(int j=2;j<I.width()-1;j++){
             int r,g,b,sum;

             QRgb q=I.pixel(j,i);
             r=qRed(q);g=qGreen(q);b=qBlue(q);
             sum=0.29*r+0.58*g+0.12*b;
             I.setPixel(j,i,qGray(sum));
              r=0;b=0;g=0;
         }
     }

     I.save("C:\\Users\\Mohamed\\Desktop\\man\\goo3.png",  0,  -1);
}
int Sobel::pixmax(){
    int max=0;
    QImage Img("C:\\Users\\Mohamed\\Desktop\\man\\res.png",  0);
    for(int i=2;i <=Img.height()-1;i++){
        for(int j=2;j<Img.width()-1;j++){
    int T[10];T[0]=Img.pixel(j-1,i-1);T[1]=Img.pixel(j,i-1);T[2]=Img.pixel(j+1,i-1);
                   T[3]=Img.pixel(j-1,i);T[4]=Img.pixel(j,i);T[5]=Img.pixel(j+1,i);
                   T[6]=Img.pixel(j-1,i+1);T[7]=Img.pixel(j,i+1);T[8]=Img.pixel(j+1,i+1);

                   for(int kj;kj<9;kj++){
                       for(int ki=kj;ki<9-kj;ki++){
                           if(max<T[ki]){
                               max=T[kj];
                           }

                       }
                   }
                    //I.setPixel(j,i, qRgb(max,max,max));
        }}
                   return 0;
}
void Sobel::myfilter(){
    QImage Img("C:\\Users\\Mohamed\\Desktop\\man\\goo.png",  0 );
    int min=1000;int max=0;int S[10];
    for(int i=2;i <=Img.height()-1;i++){
        for(int j=2;j<Img.width()-1;j++){
            QRgb T[10];T[0]=Img.pixel(j-1,i-1);T[1]=Img.pixel(j,i-1);T[2]=Img.pixel(j+1,i-1);
                           T[3]=Img.pixel(j-1,i);T[4]=Img.pixel(j,i);T[5]=Img.pixel(j+1,i);
                           T[6]=Img.pixel(j-1,i+1);T[7]=Img.pixel(j,i+1);T[8]=Img.pixel(j+1,i+1);
                           int R[10];int G[10];int B[10];
                           for(int c=0;c<9;c++){
                               R[c]=qRed(T[c]);
                               G[c]=qGreen(T[c]);
                               B[c]=qBlue(T[c]);
                               S[c]=0.29*R[c]+0.59*G[c]+0.12*B[c];

                             for(int r=0; r<9; r++){
                                 if(min>S[r]) {min=S[r];}
                                 if(max<S[r]) max=S[r];
                             }
                           }
                           if(abs(S[4]-min)< abs(S[4]-max))
                               Img.setPixel(j,i,qRgb(min/2,min/2,min/2));
                          else Img.setPixel(j,i,qRgb(1.5*max,1.5*max,1.5*max));
                           min=300;max=0;
        }
    }
  Img.save("C:\\Users\\Mohamed\\Desktop\\man\\cc.png",  0,  -1);
}

