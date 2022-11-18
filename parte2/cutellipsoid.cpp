#include "cutellipsoid.h"

CutEllipsoid::CutEllipsoid(int x, int y, int z, int rx, int ry, int rz)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}

void CutEllipsoid::draw(Sculptor &s)
{
    for (int i = 0; i < s.nx; i++)
    {
        for (int j = 0; j < s.ny; j++)
        {
            for (int k = 0; k < s.nz; k++)
            {

                int value = ((i - x) * (i - x)) / (rx * rx) + ((j - y) * (j - y)) / (ry * ry) + ((k - z) * (k - z)) / (rz * rz);
                if (value <= 1)
                {
                    s.cutVoxel(i,j,k);
                }
            }
        }
    }
}
