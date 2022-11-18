#include "cutsphere.h"

CutSphere::CutSphere(int x, int y, int z, int radius)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
}

void CutSphere::draw(Sculptor &s)
{
    for (int i = 0; i < s.nx; i++)
    {
        for (int j = 0; j < s.ny; j++)
        {
            for (int k = 0; k < s.nz; k++)
            {
                int value = (i - x) * (i - x) + (j - y) * (j - y) + (z - z) * (z - z);
                if (value <= (radius) * (radius))
                {
                    s.cutVoxel(i,j,k);
                }
            }
        }
    }
}
