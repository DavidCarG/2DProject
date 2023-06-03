#ifndef MAPEO_H
#define MAPEO_H

#include <iostream>
using namespace std;

class mapeo
{
    float xWmin, yWmin, xWmax,yWmax;
    int xpVmin, ypVmin, xpVmax, ypVmax;

public:
    //mapeo();

    int round(float n){ return n + .5; }
    void ventana(float wX1, float wY1, float wX2, float wY2);
    void puerto(int pvX1, int pvY1, int pvX2, int pvY2);
    //   * = Notación de Puntero,      & = Notación de Referencia
    void mapear(float *xw, float* yw, int *xpV, int &ypV, int L,int M);

};

#endif // MAPEO_H
