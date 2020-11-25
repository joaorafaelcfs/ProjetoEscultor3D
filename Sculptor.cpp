#include "Sculptor.h" // Header onde está declarada a classe Sculptor
#include <iostream>   // Biblioteca Padrao
#include <cstdlib>    // Biblioteca usado para o exit
#include <fstream>    // Biblioteca usado para as streams
#include <cmath>      // Biblioteca usado para operações matematicas

using namespace std;

// Construtor da classe Esculptor
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx; ny = _ny; nz = _nz;
    if (_nx <= 0 || _ny <= 0 || _nz <= 0){
        _nx = _ny = _nz = 0;
    }
// Alocaçao da matriz 3d
    v = new Voxel **[_nz];
    if ( v == NULL){
        cout << "Erro de alocação" << endl;
        exit(1) ;
    }
    v[0] = new Voxel*[_nz*_ny];
    if (v[0] == NULL){
        cout << "Erro de alocação" << endl;
        exit(1) ;
    }
    v[0][0] = new Voxel[_nx*_ny*_nz];
    if (v[0][0] == NULL){
        cout << "Erro de alocação" << endl;
        exit(1) ;
    }

    for (int i = 1; i < _nz; i++){
        v[i] = v[i-1] + _nz;
    }

    for (int j = 1; j < (_nz*_ny); j++){
        v[0][j] = v[0][j-1] + _nx;

    }
}

// Destrutor da classe Esculptor
Sculptor::~Sculptor(){  
//liberação da memoria que foi alocada para a matriz 3D
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

// Definição da cor do desenho
void Sculptor::setColor (float _r, float _g, float _b, float alpha){ 
    if (_r < 0 || _r > 1 || _g < 0 || _g > 1 || _b < 0 || _b > 1 || alpha < 0 || alpha > 1){
        cout << "Valor errado para cor " << endl;
        exit(1);
    }
    r = _r;
    g = _g;
    b = _b;
    a = alpha;
}
// Ativa o Voxel na posição (x,y,z), 
void Sculptor::putVoxel (int x, int y ,int z){ 
// isOn = true
    if ( x < 0 || x > nx || y < 0 || y > ny || z < 0 || z > nz){
        cout << "Valor errado para ativar o Voxel" << endl;
    } else {
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

// Desativa o Voxel na posição (x,y,z)
void Sculptor::cutVoxel (int x, int y, int z){ 
//isOn = false
    if ( x < 0 || x > nx || y < 0 || y > ny || z < 0 || z > nz){
        cout << "Valor errado para desativar o Voxel" << endl;
    } else {
        v[x][y][z].isOn = false;
    }
}

//Ativa todos os voxels no intervalo {x0,x1}, {y0,y1}, {z0,z1}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
// isOn = true
    int i, j, k;
    if (x0 > nx || x0 < 0 || x1 > nx || x1 < 0 || y0 > ny || y0 < 0 || y1 > ny || y1 < 0 || z0 > nz || z0 < 0 ||  z1 > nz || z1 < 0) {
        cout << "coordenadas incorretas" << endl;
        exit (1);
    } else {
        for ( i = x0; i <= x1; i++){
            for (j = y0; j <= y1; j++){
                for (k = z0; k <= z1; k++){
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

//Desativa todos os voxels no intervalo {x0,x1}, {y0,y1}, {z0,z1}
void Sculptor::cutBox (int x0, int x1, int y0, int y1, int z0, int z1){
//isOn = false
    int i, j, k;
    if (x0 > nx || x0 < 0 || x1 > nx || x1 < 0 || y0 > ny || y0 < 0 || y1 > ny || y1 < 0 || z0 > nz || z0 < 0 ||  z1 > nz || z1 < 0) {
        cout << "coordenadas incorretas" << endl;
        exit (1);
    } else {
        for ( i = x0; i <= x1; i++){
            for (j = y0; j <= y1; j++){
                for (k = z0; k <= z1; k++){
                    v[i][j][k].isOn = false;
                }
            }
        } 
    }
}

//Ativa todos os voxels que satisfazem à equação da esfera, atribuindo as cores
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter , int radius){
// isOn = true
    int i, j, k;
    if ( xcenter < 0 || xcenter > nx || ycenter < 0 || ycenter > ny || zcenter < 0 || zcenter > nz
    || radius < 0 || (xcenter + radius ) > nx || (ycenter + radius) > ny || (zcenter + radius) > nz){
        cout << "dimensões erradas" << endl;
        exit(1);
    } else {
        float d;
        for (i = 0; i <= nx; i++){
            for (j = 0; j <= ny; j++){
                for (k = 0; k <= nz; k++){
                    //distancia entre tres pontos
                    d = sqrt(pow(i-xcenter,2) + pow(j-ycenter, 2) + pow(k-zcenter, 2));
                    if (d <= radius){
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
}

//Desativa todos os voxels que satisfazem à equação da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter , int radius){
// isOn = false    
    int i, j, k;
    if ( xcenter < 0 || xcenter > nx || ycenter < 0 || ycenter > ny || zcenter < 0 || zcenter > nz
    || radius < 0 || (xcenter + radius ) > nx || (ycenter + radius) > ny || (zcenter + radius) > nz){
        cout << "dimensões erradas" << endl;
        exit(1);
    } else {
        float d;
        for (i = 0; i <= nx; i++){
            for (j = 0; j <= ny; j++){
                for (k = 0; k <= nz; k++){
                    //distancia entre tres pontos -- equação da esfera
                    d = sqrt(pow(i-xcenter,2) + pow(j-ycenter, 2) + pow(k-zcenter, 2));
                    if (d <= radius){
                        v[i][j][k].isOn = false;
                    }
                }
            }
        } 
    }
}
// Ativa todos os voxels que satisfazem à equação do elipsóide
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
// isOn = true    
    int i, j, k;
    if (xcenter < 0 || xcenter > nx || ycenter < 0 || ycenter > ny || zcenter < 0 || zcenter > nz
    || (xcenter + rx) > nx || (ycenter + ry) > ny || (zcenter + rz) > nz || rx < 0 || ry < 0 || rz < 0){
        cout << "dimensões erradas" << endl;
        exit (1);
    } else {
        float d;
        for ( i =  xcenter - rx; i < xcenter + rx; i++){
            for (j = ycenter - ry; j < ycenter + ry; j++){
                for (k = zcenter - rz; k < zcenter + rz; k++){
                    // equação da elipsoide
                    d = (float) pow ((i - xcenter),2)/pow(rx,2) + (float)pow((j-ycenter),2)/pow(ry,2) +(float)pow((k-zcenter),2)/pow(rz,2);
                    if (d <= 1.0){
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
}

// Desativa todos os voxels que satisfazem à equação do elipsóide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){   
// isOn = true
    int i, j, k;
    if (xcenter < 0 || xcenter > nx || ycenter < 0 || ycenter > ny || zcenter < 0 || zcenter > nz
    || (xcenter + rx) > nx || (ycenter + ry) > ny || (zcenter + rz) > nz || rx < 0 || ry < 0 || rz < 0){
        cout << "dimensões erradas" << endl;
        exit (1);
    } else {
        float d;
        for ( i =  xcenter - rx; i < xcenter + rx; i++){
            for (j = ycenter - ry; j < ycenter + ry; j++){
                for (k = zcenter - rz; k < zcenter + rz; k++){
                    if (i>=0 && i<nx && j>=0 && j<ny && k>=0 && k<nz){
                    // equação da elipsoide
                    d = (float) pow ((i - xcenter),2)/pow(rx,2) + (float)pow((j-ycenter),2)/pow(ry,2) + (float)pow((k-zcenter),2)/pow(rz,2);     
                    }                
                    if (d <= 1.0){
                        v[i][j][k].isOn = false;
                    }
                }
                
            }
        }
    }
}

void Sculptor::writeOFF(char *filename){
// variáveis relacionado ao n° de vertices, faces e arestas
    int nv = 0, nf = 0, i, j, k;

// variavel para faces
    int face = 0;

    ofstream escultura;

    escultura.open(filename); // abertura do arquivo off que receberá as informações necessárias para a escultura

    if (escultura.is_open()){
        cout << "Arquivo aberto" << endl;
    } else {
        cout << "Arquivo não abriu" <<endl;
        exit(1);
    }
// Escrever primeira linha no arquivo.
    escultura << "OFF" << endl;
// Contar a quantidade de vertices e faces que deverão ser incluidos no arquivo
    for (i=0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (v[i][j][k].isOn == true){
                    nv = nv + 8;
                    nf = nf + 6;
                }
            }
        }
    }

// Escrever a quantidade de vertices, faces e arestas
    escultura << nv << " " << nf << " 0" << endl;

    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (v[i][j][k].isOn == true){
                    escultura << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    escultura << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    escultura << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    escultura << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    escultura << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    escultura << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    escultura << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    escultura << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }

    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (v[i][j][k].isOn == true){
                    escultura << 4 << " " << face + 0 << " " << face + 3 << " " << face + 2 << " " << face + 1 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    escultura << 4 << " " << face + 4 << " " << face + 5 << " " << face + 6 << " " << face + 7 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    escultura << 4 << " " << face + 0 << " " << face + 1 << " " << face + 5 << " " << face + 4 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    escultura << 4 << " " << face + 0 << " " << face + 4 << " " << face + 7 << " " << face + 3 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    escultura << 4 << " " << face + 3 << " " << face + 7 << " " << face + 6 << " " << face + 2 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    escultura << 4 << " " << face + 1 << " " << face + 2 << " " << face + 6 << " " << face + 5 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    face = face + 8;
                }
            }
        }
    }

    if (escultura.is_open()){
        cout << "Arquivo Salvo" << endl;
    }

    escultura.close();
}