#include "mapeo.h"

/*mapeo::mapeo()
{

}
*/

void mapeo::ventana(float wX1, float wY1, float wX2, float wY2)
{
    xWmin = wX1;
    yWmin = wY1;
    xWmax = wX2;
    yWmax = wY2;
}

void mapeo::puerto(int pvX1, int pvY1, int pvX2, int pvY2)
{
    xpVmin = pvX1;
    ypVmin = pvY1;
    xpVmax = pvX2;
    ypVmax = pvY2;

}

void mapeo::mapear(float *xw, float *yw, int *xpV, int &ypV, int L, int M)
{
    float sX, sY;
    sX =  (xpVmax - xpVmin) / (xWmax - xWmin);
    sY = (ypVmax - ypVmin) / (yWmax - yWmin);
    *xpV = int(round(sX * (*xw-xWmin) + xpVmin)+L);
    ypV = int(round(sY * (yWmin - *yw) - ypVmin)+ M);
}
