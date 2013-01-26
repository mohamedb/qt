#ifndef SOBEL_H
#define SOBEL_H
#include<QImage>
class Sobel
{
public:
    Sobel();
    void run();
    void contrast();
    int pixmax();
    void myfilter();
};

#endif // SOBEL_H
