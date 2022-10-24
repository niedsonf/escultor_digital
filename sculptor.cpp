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
    v = new Voxel **[nz];
    v[0] = new Voxel *[nz * nx];
    v[0][0] = new Voxel[nz * ny * nx];
    for (int i = 1; i < nz; i++)
    {
        v[i] = v[i - 1] + nx;
    }
    for (int i = 1; i < nx * nz; i++)
    {
        v[0][i] = v[0][i - 1] + ny;
    }
    for (int i = 0; i < nz * nx * ny; i++)
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

void Sculptor::setColor(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z)
{
    if ((0 <= x < nx) && (0 <= y < ny) && (0 <= z < nz))
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    if ((0 <= x < nx) && (0 <= y < ny) && (0 <= z < nz))
    {
        v[x][y][z].isOn = false;
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutVoxel'\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if ((x0 >= 0 && y0 >= 0 && z0 >= 0) && (x1 < nx && y1 < ny && z1 < nz))
    {
        for (int i = z0; i < z1; i++)
        {
            for (int j = x0; j < x1; j++)
            {
                for (int k = y0; k < y1; k++)
                {
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
                    v[i][j][k].isOn = true;
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'putBox'\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if ((x0 >= 0 && y0 >= 0 && z0 >= 0) && (x1 < nx && y1 < ny && z1 < nz))
    {
        for (int i = z0; i < z1; i++)
        {
            for (int j = x0; j < x1; j++)
            {
                for (int k = y0; k < y1; k++)
                {
                    v[i][j][k].isOn = false;
                }
            }
        }
    }
    else
    {
        std::cout << "Referência invalida na chamada da funcao 'cutBox'\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (0 <= xcenter < nx && 0 <= ycenter < ny && 0 <= zcenter < nz)
    {
        for (int i = 0; i < nz; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                for (int k = 0; k < ny; k++)
                {
                    int value = (j - xcenter) * (j - xcenter) + (k - ycenter) * (k - ycenter) + (i - zcenter) * (i - zcenter);
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    if (0 <= xcenter < nx && 0 <= ycenter < ny && 0 <= zcenter < nz)
    {
        for (int i = 0; i < nz; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                for (int k = 0; k < ny; k++)
                {

                    int value = (j - xcenter) * (j - xcenter) + (k - ycenter) * (k - ycenter) + (i - zcenter) * (i - zcenter);
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (0 <= xcenter < nx && 0 <= ycenter < ny && 0 <= zcenter < nz)
    {
        for (int i = 0; i < nz; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                for (int k = 0; k < ny; k++)
                {

                    int value = ((j - xcenter) * (j - xcenter)) / (rx * rx) + ((k - ycenter) * (k - ycenter)) / (ry * ry) + ((i - zcenter) * (i - zcenter)) / (rz * rz);
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    if (0 <= xcenter < nx && 0 <= ycenter < ny && 0 <= zcenter < nz)
    {
        for (int i = 0; i < nz; i++)
        {
            for (int j = 0; j < nx; j++)
            {
                for (int k = 0; k < ny; k++)
                {

                    int value = ((j - xcenter) * (j - xcenter)) / (rx * rx) + ((k - ycenter) * (k - ycenter)) / (ry * ry) + ((i - zcenter) * (i - zcenter)) / (rz * rz);
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}

void Sculptor::writeOFF(const char *filename)
{
    std::ofstream fout;
    int nVoxel = 0, ref = 0;
    fout.open(filename);

    if (fout.is_open())
    {
        std::cout << "Iniciando gravacao do arquivo...\n";
    }
    else
    {
        std::cout << "Erro na abertura do arquivo\n";
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }

    for (int i = 0; i < nz; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            for (int k = 0; k < ny; k++)
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

    for (int i = 0; i < nz; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            for (int k = 0; k < ny; k++)
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

    for (int i = 0; i < nz; i++)
    {
        for (int j = 0; j < nx; j++)
        {
            for (int k = 0; k < ny; k++)
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
        std::cout << "Pressione Enter para fechar a janela...\n";
        std::cin.get();
        exit(1);
    }
}
