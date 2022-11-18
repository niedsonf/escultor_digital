#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H
#include "figurageometrica.h"

class PutEllipsoid : public FiguraGeometrica
{
protected:
    int rx, ry, rz;
public:
    PutEllipsoid(int x, int y, int z, int rx, int ry, int rz, float r, float g, float b, float a);
    void draw(Sculptor &s);
};

#endif // PUTELLIPSOID_H
