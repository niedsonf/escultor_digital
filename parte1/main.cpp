#include "sculptor.h"

int main()
{
    Sculptor model(100,100,100);
    model.setColor(0,0,0,1);
    model.putBox(0,99,0,50,0,10);
    model.cutBox(0,10,0,10,0,10);
    model.setColor(0,255,0,1);
    model.putVoxel(0,0,15);
    model.setColor(0,255,0,1);
    model.putSphere(30,30,30,10);
    model.setColor(0,0,255,1);
    model.putEllipsoid(70,70,70,5,10,15);
    model.cutEllipsoid(80,80,80,5,10,15);
    model.cutSphere(40,40,40,15);
    model.cutVoxel(99,99,9);
    model.writeOFF("model.off");
    return 0;
}
