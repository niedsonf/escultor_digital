#include "putsphere.h"

PutSphere::PutSphere(int x, int y, int z, int radius, float r, float g, float b, float a)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutSphere::draw(Sculptor &s)
{
    for (int i = 0; i < s.nx; i++)
    {
        for (int j = 0; j < s.ny; j++)
        {
            for (int k = 0; k < s.nz; k++)
            {
                int value = (i - x) * (i - x) + (j - y) * (j - y) + (k - z) * (k - z);
                if (value <= (radius) * (radius))
                {
                    s.setColor(r,g,b,a);
                    s.putVoxel(i,j,k);
                }
            }
        }
    }
}
