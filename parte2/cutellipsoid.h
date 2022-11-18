#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H
#include "figurageometrica.h"

class CutEllipsoid : public FiguraGeometrica
{
private:
    int rx, ry, rz;
public:
    CutEllipsoid(int x, int y, int z, int rx, int ry, int rz);
    void draw(Sculptor &s);
};

#endif // CUTELLIPSOID_H
