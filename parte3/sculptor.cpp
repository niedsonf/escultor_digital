#include "sculptor.h"
#include "voxel.h"
#include <fstream>
#include <iostream>

Sculptor::Sculptor(int nx, int ny, int nz)
{
    if (nx <= 0 || ny <= 0 || nz <= 0)
    {
        std::cout << "Tamanho de matriz invalido, insira dimensoes maiores que 0\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
    this->nx = nx;
    this->ny = ny;
    this->nz = nz;
    v = new Voxel **[nx];
    v[0] = new Voxel *[nx * ny];
    v[0][0] = new Voxel[nx * ny * nz];
    for (int i = 1; i < nx; i++)
    {
        v[i] = v[i - 1] + ny;
    }
    for (int i = 1; i < nx * ny; i++)
    {
        v[0][i] = v[0][i - 1] + nz;
    }
    for (int i = 0; i < nx * ny * nz; i++)
    {
        v[0][0][i].isOn = false;
    }
}

Sculptor::~Sculptor()
{
    delete[] v[0][0];
    delete[] v[0];
    delete[] v;
}

std::vector<std::vector<Voxel> > Sculptor::getPlan(int plan)
{
    std::vector<std::vector<Voxel>> holder;
    std::vector<Voxel> auxHolder;
    for(int y=0; y<ny; y++){
        for(int x=0; x<nx; x++){
            auxHolder.push_back(v[x][y][plan]);
        }
        holder.push_back(auxHolder);
        auxHolder.clear();
    }
    return holder;
}

std::vector<std::vector<Voxel> > Sculptor::getView(View view)
{
    std::vector<std::vector<Voxel>> holder;
    std::vector<Voxel> auxHolder;
    Voxel viewVoxel;

    switch(view){
    case FrontView:
        for(int y=0; y<ny; y++){
            for(int x=0; x<nx; x++){
                for(int z=nz-1; z>=0; z--){
                    if(v[x][y][z].isOn){
                        viewVoxel = v[x][y][z];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;

    case BackView:
        for(int y=0; y<ny; y++){
            for(int x=nx-1; x>=0; x--){
                for(int z=0; z<nz; z++){
                    if(v[x][y][z].isOn){
                        viewVoxel = v[x][y][z];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;

    case TopView:
        for(int y=ny-1; y>=0; y--){
            for(int x=0; x<nx; x++){
                for(int z=ny-1; z>=0; z--){
                    if(v[x][z][y].isOn){
                        viewVoxel = v[x][z][y];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;

    case BottomView:
        for(int y=0; y<ny; y++){
            for(int x=0; x<nx; x++){
                for(int z=0; z<nz; z++){
                    if(v[x][z][y].isOn){
                        viewVoxel = v[x][z][y];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;



    case LeftView:
        for(int y=0; y<ny; y++){
            for(int x=nx-1; x>=0; x--){
                for(int z=nz-1; z>=0; z--){
                    if(v[z][y][x].isOn){
                        viewVoxel = v[z][y][x];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;

    case RightView:
        for(int y=0; y<ny; y++){
            for(int x=0; x<nx; x++){
                for(int z=0; z<nz; z++){
                    if(v[z][y][x].isOn){
                        viewVoxel = v[z][y][x];
                    }
                }
                auxHolder.push_back(viewVoxel);
                viewVoxel.isOn = false;
            }
            holder.push_back(auxHolder);
            auxHolder.clear();
        }
        break;


}




return holder;
}

void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    if (x>=0 && y>=0 && z>=0 && x<nx && y<ny && z<nz)
    {
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
        v[x][y][z].isOn = true;
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'putVoxel'\n";
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    if (x>=0 && y>=0 && z>=0 && x<nx && y<ny && z<nz)
    {
        v[x][y][z].isOn = false;
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutVoxel'\n";
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if (x0 >= 0 && y0 >= 0 && z0 >= 0)
    {
        for (int i = x0; i < x1; i++)
        {
            for (int j = y0; j < y1; j++)
            {
                for (int k = z0; k < z1; k++)
                {
                    if(j < nx && k < ny && i < nz){
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                        v[i][j][k].isOn = true;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'putBox'\n";
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if (x0 >= 0 && y0 >= 0 && z0 >= 0)
    {
        for (int i = x0; i < x1; i++)
        {
            for (int j = y0; j < y1; j++)
            {
                for (int k = z0; k < z1; k++)
                {
                    if(j < nx && k < ny && i < nz){
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutBox'\n";
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (xcenter>=0 && ycenter>=0 && zcenter>=0 && xcenter<nx && ycenter<ny && zcenter<nz)
    {
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                for (int k = 0; k < nz; k++)
                {
                    int value = (i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) + (k - zcenter) * (k - zcenter);
                    if (value <= (radius) * (radius))
                    {
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'putSphere'\n";
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (xcenter>=0 && ycenter>=0 && zcenter>=0 && xcenter<nx && ycenter<ny && zcenter<nz)
    {
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                for (int k = 0; k < nz; k++)
                {

                    int value = (i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) + (k - zcenter) * (k - zcenter);
                    if (value <= (radius) * (radius))
                    {
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutSphere'\n";
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (xcenter>=0 && ycenter>=0 && zcenter>=0 && xcenter<nx && ycenter<ny && zcenter<nz)
    {
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                for (int k = 0; k < nz; k++)
                {
                    int value = ((i - xcenter) * (i - xcenter)) / (rx * rx) + ((j - ycenter) * (j - ycenter)) / (ry * ry) + ((k - zcenter) * (k - zcenter)) / (rz * rz);
                    if (value <= 1)
                    {
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'putEllipsoid'\n";
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (xcenter>=0 && ycenter>=0 && zcenter>=0 && xcenter<nx && ycenter<ny && zcenter<nz)
    {
        for (int i = 0; i < nx; i++)
        {
            for (int j = 0; j < ny; j++)
            {
                for (int k = 0; k < nz; k++)
                {

                    int value = ((i - xcenter) * (i - xcenter)) / (rx * rx) + ((j - ycenter) * (j - ycenter)) / (ry * ry) + ((k - zcenter) * (k - zcenter)) / (rz * rz);
                    if (value <= 1)
                    {
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutEllipsoid'\n";
    }
}

void Sculptor::writeOFF(QString filename)
{
    std::ofstream fout;
    int nVoxel = 0, ref = 0;
    fout.open(filename.toUtf8()+".off");

    if (fout.is_open())
    {
        std::cout << "Iniciando gravacao do arquivo...\n";
    }
    else
    {
        std::cout << "Erro na abertura do arquivo\n";
    }

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    nVoxel++;
                }
            }
        }
    }

    fout << "OFF" << std::endl;
    fout << nVoxel * 8 << " " << nVoxel * 6 << " " << 0 << std::endl;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            for (int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn)
                {
                    fout << 4 << " " << ref + 0 << " " << ref + 3 << " " << ref + 2 << " " << ref + 1 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 4 << " " << ref + 5 << " " << ref + 6 << " " << ref + 7 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 0 << " " << ref + 1 << " " << ref + 5 << " " << ref + 4 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 0 << " " << ref + 4 << " " << ref + 7 << " " << ref + 3 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 3 << " " << ref + 7 << " " << ref + 6 << " " << ref + 2 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fout << 4 << " " << ref + 1 << " " << ref + 2 << " " << ref + 6 << " " << ref + 5 << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    ref += 8;
                }
            }
        }
    }

    if (fout.is_open())
    {
        std::cout << "Arquivo gerado com sucesso!\n";
    }
}
