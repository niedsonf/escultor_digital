#ifndef CUTVOXEL_H
#define CUTVOXEL_H
#include "figurageometrica.h"
#include "sculptor.h"

class CutVoxel : public FiguraGeometrica
{
public:
    CutVoxel(int x, int y, int z);
    ~CutVoxel();
    void draw(Sculptor &s);
};

#endif // CUTVOXEL_H
