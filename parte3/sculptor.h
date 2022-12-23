#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"
#include <vector>
#include <QString>

enum View{FrontView, BackView, TopView, BottomView, LeftView, RightView};

class Sculptor
{
private:
    Voxel ***v;
    int nx,ny,nz;
    float r=0,g=255,b=255,a=255;
public:
    Sculptor(int _nx, int _ny, int _nz);
    ~Sculptor();
    std::vector<std::vector<Voxel>> getPlan(int plan);
    std::vector<std::vector<Voxel>> getView(View);
    void setColor(float r, float g, float b, float a);
    void putVoxel(int x, int y, int z);
    void cutVoxel(int x, int y, int z);
    void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void putSphere(int xcenter, int ycenter, int zcenter, int radius);
    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void writeOFF(QString);
};

#endif // SCULPTOR_H
