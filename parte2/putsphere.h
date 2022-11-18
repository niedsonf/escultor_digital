#ifndef PUTSPHERE_H
#define PUTSPHERE_H
#include "figurageometrica.h"


class PutSphere : public FiguraGeometrica
{
protected:
    int radius;
public:
    PutSphere(int x, int y, int z, int radius, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTSPHERE_H
