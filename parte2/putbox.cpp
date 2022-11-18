#include "putbox.h"

PutBox::PutBox(int x0, int x1, int y0, int y1, int z0, int z1, float r, float g, float b, float a)
{
    x = x0 < x1 ? x0 : x1;
    xf = x0 < x1 ? x1 : x0;
    y = y0 < y1 ? y0 : y1;
    yf = y0 < y1 ? y1 : y0;
    z = z0 < z1 ? z0 : z1;
    zf = z0 < z1 ? z1 : z0;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void PutBox::draw(Sculptor &s)
{

    for (int i = x; i <= xf; i++)
    {
        for (int j = y; j <= yf; j++)
        {
            for (int k = z; k <= zf; k++)
            {
                s.setColor(r,g,b,a);
                s.putVoxel(i,j,k);
            }
        }
    }

}
