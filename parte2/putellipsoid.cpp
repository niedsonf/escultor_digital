#include "putellipsoid.h"

PutEllipsoid::PutEllipsoid(int x, int y, int z, int rx, int ry, int rz, float r, float g, float b, float a)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutEllipsoid::draw(Sculptor &s)
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
                    s.setColor(r,g,b,a);
                    s.putVoxel(i,j,k);
                }
            }
        }
    }
}
