#ifndef CUTBOX_H
#define CUTBOX_H
#include "figurageometrica.h"


class CutBox : public FiguraGeometrica
{
protected:
    int xf; int yf; int zf;
public:
    CutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void draw(Sculptor &s);
};

#endif // CUTBOX_H
