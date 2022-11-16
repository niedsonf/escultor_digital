#include <iostream>
#include "interpreter.h"

using namespace std;

int main()
{
    Interpreter interpreter("arquivo.txt");
    Sculptor sculptor(interpreter.getdimX(), interpreter.getdimY(), interpreter.getdimZ());
    interpreter.draw(sculptor);
    sculptor.writeOFF("arquivo.off");
    return 0;
}
