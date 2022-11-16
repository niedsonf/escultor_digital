#include "interpreter.h"
#include "putvoxel.h"
#include "cutvoxel.h"
#include <fstream>
#include <iostream>
#include <vector>

Interpreter::Interpreter(std::string filename)
{
    std::ifstream fin;
    fin.open("arquivo.txt");
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
      }

}

void Interpreter::draw(Sculptor &s)
{
    for(auto it: figs){
        it->draw(s);
      }

    for(itf = figs.begin(); itf!=figs.end(); itf++){
        delete *itf;
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
