#include "cutvoxel.h"

CutVoxel::CutVoxel(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void CutVoxel::draw(Sculptor &s)
{
    s.cutVoxel(x,y,z);
}
