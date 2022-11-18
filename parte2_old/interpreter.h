#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <vector>
#include "figurageometrica.h"
#include <string>

class Interpreter
{
private:
    int dimX, dimY, dimZ;
    std::vector<FiguraGeometrica*> figs;
    std::vector<FiguraGeometrica*>::iterator itf;
public:
    Interpreter(std::string filename);
    void draw(Sculptor &s);
    int getdimX();
    int getdimY();
    int getdimZ();
};

#endif // INTERPRETER_H
