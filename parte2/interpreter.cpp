#include "interpreter.h"
#include "putvoxel.h"
#include "cutvoxel.h"
#include "putbox.h"
#include "cutbox.h"
#include "putsphere.h"
#include "cutsphere.h"
#include "putellipsoid.h"
#include "cutellipsoid.h"
#include <fstream>
#include <iostream>
#include <vector>

Interpreter::Interpreter(const char* filename)
{
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        std::cout << "Falha na abertura do arquivo\n";
        exit(1);
    }

    std::string s;
    while(fin.good()){
        fin >> s;
        if(!fin.good())
          break;
        if(s.compare("dim")==0){
          int x, y, z;
          fin >> x >> y >> z;
          dimX = x;
          dimY = y;
          dimZ = z;
        }
        if(s.compare("putvoxel")==0){
           int x, y, z;
           float r, g, b, a;
           fin >> x >> y >> z;
           fin >> r >> g >> b >> a;
           figs.push_back(new PutVoxel(x,y,z,r,g,b,a));
        }
        if(s.compare("cutvoxel")==0){
           int x, y, z;
           fin >> x >> y >> z;
           figs.push_back(new CutVoxel(x,y,z));
        }
        if(s.compare("putbox")==0){
            int x0, x1, y0, y1, z0, z1;
            float r, g, b, a;
            fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
            figs.push_back(new PutBox(x0,x1,y0,y1,z0,z1,r,g,b,a));
        }
        if(s.compare("cutbox")==0){
            int x0, x1, y0, y1, z0, z1;
            fin >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
            figs.push_back(new CutBox(x0,x1,y0,y1,z0,z1));
        }

        if(s.compare("putsphere")==0){
            int x, y, z, radius;
            float r, g, b, a;
            fin >> x >> y >> z >> radius >> r >> g >> b >> a;
            figs.push_back(new PutSphere(x,y,z,radius,r,g,b,a));
        }

        if(s.compare("cutsphere")==0){
            int x, y, z, radius;
            fin >> x >> y >> z >> radius;
            figs.push_back(new CutSphere(x,y,z,radius));
        }

        if(s.compare("putellipsoid")==0){
            int x, y, z, rx, ry, rz;
            float r, g, b, a;
            fin >> x >> y >> z >> rx >> ry >> rz >> r >> g >> b >> a;
            figs.push_back(new PutEllipsoid(x,y,z,rx,ry,rz,r,g,b,a));
        }

        if(s.compare("cutellipsoid")==0){
            int x, y, z, rx, ry, rz;
            fin >> x >> y >> z >> rx >> ry >> rz;
            figs.push_back(new CutEllipsoid(x,y,z,rx,ry,rz));
        }

      }

}

Interpreter::~Interpreter()
{

    for(itf = figs.begin(); itf!=figs.end(); itf++){
        delete *itf;
      }
}

void Interpreter::draw(Sculptor &s)
{
    for(auto it: figs){
        it->draw(s);
      }
}

int Interpreter::getdimX()
{
    return dimX;
}

int Interpreter::getdimY()
{
    return dimY;
}

int Interpreter::getdimZ()
{
    return dimZ;
}
