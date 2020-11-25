#ifndef SCULPTOR_H_INCLUDED
#define SCULPTOR_H_INCLUDED


/** 
 *  \brief Declaração do Struct Voxel \n
 *  No struct Voxel é armazenado variaveis que irão determinar as cores (r,g,b) e transparência (a) do objeto,
 *  como também  teremos a propriedade isOn que define se o voxel correspondete deve ser incluído no arquivo digital.
 *  \param r - Cor vermelha
 *  \param g - Cor verde
 *  \param b - Cor azul
 *  \param a - Transparência
 *  \param isOn - Incluir ou não no arquivo digital
*/
struct Voxel {
  float r,g,b; // Cores
  float a; // Transparencia
  bool isOn; // Included or not
};

/**
 *  \brief Classe Sculptor
 */
class Sculptor {
protected:
  Voxel ***v; // 3D matrix
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:

/** \brief Construtor da Classe \n Aqui fazemos a alocação dinâmica de memória para o nosso vetor ***v
 *  \param _nx -- Dimensão em x
 *  \param _ny -- Dimensão em y
 *  \param _nz -- Dimensão em z*/
  Sculptor(int _nx, int _ny, int _nz);

/** \brief Destrutor da Classe \n Aqui fazemos a liberação da memória do nosso vetor ***v */
  ~Sculptor();

/** \brief Atribuição de cor ao objeto desenhado
 *  \n As variáveis r,g,b e alpha recebem valores compreendidos em um intervalo de [0,1]. A variável r está relacionada a cor vermelha (red),
 * g está relacionada a cor verde (green) e b é a cor azul (blue). E por sua vez a variável alpha corresponde a transparência que o objeto terá. \n
 * A cada vez que o usuário quiser mudar a cor de um objeto, ele deverá chamar essa função. 
 *  \param r -- Cor vermelha 
 *  \param g -- Cor verde
 *  \param b -- Cor azul
 *  \param alpha -- Transparência */

  void setColor(float r, float g, float b, float alpha);

/** \brief Essa função é responsável por formar um voxel na posição x,y,z e fazendo isOn = true. \n Atribui a ele a cor atual definida na função setColor
*   \param x -- Ativação do voxel na posição x
*   \param y -- Ativação do voxel na posição y
*   \param z -- Ativação do voxel na posição z */
  void putVoxel(int x, int y, int z);

/** \brief Essa função é responsável por excluir um voxel na posição x,y,z e fazendo isOn = false.
*   \param x -- Desativa o voxel na posição x
*   \param y -- Desativa o voxel na posição y
*   \param z -- Desativa o voxel na posição z */  
  void cutVoxel(int x, int y, int z);

/** \brief Essa função é responsável por ativar todos os voxels compreendidos no intervalo [x0,x1], [y0,y1], [z0,z1] e fazendo isOn = true.
*   \n Ela forma todos os voxels que estão compreendidos nesse intervalo. \n Atribui a ele a cor atual definida na função setColor
*   \param x0  x1 -- Ativa uma sequência de voxels no intervalo de x0 a x1
*   \param y0 y1 -- Ativa uma sequência de voxels no intervalo de y0 a y1
*   \param z0 z1 -- Ativa uma sequência de voxels no intervalo de z0 a z1 */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

/** \brief Essa função é responsável por desativar todos os voxels compreendidos no intervalo [x0,x1], [y0,y1], [z0,z1] e fazendo isOn = false.
*   \brief Ela exclui todos os voxels que estão compreendidos nesse intervalo.
*   \param x0  x1 -- Desativa uma sequência de voxels no intervalo de x0 a x1
*   \param y0 y1 -- Desativa uma sequência de voxels no intervalo de y0 a y1
*   \param z0 z1 -- Desativa uma sequência de voxels no intervalo de z0 a z1 */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

/** \brief Ativa todos os voxels que satisfazem à equação da esfera. \n Atribui a ele a cor atual definida na função setColor
*   \param xcenter -- Posição central da esfera no eixo x 
*   \param ycenter -- Posição central da esfera no eixo y 
*   \param zcenter -- Posição central da esfera no eixo z
*   \param radius -- Raio da esfera */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);

/** \brief Desativa todos os voxels que satisfazem à equação da esfera.
*   \param xcenter -- Posição central da esfera no eixo x 
*   \param ycenter -- Posição central da esfera no eixo y 
*   \param zcenter -- Posição central da esfera no eixo z
*   \param radius -- Raio da esfera */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

/** \brief Ativa todos os voxels que satisfazem à equação da elipsóide. \n Atribui a ele a cor atual definida na função setColor
*   \param xcenter -- Posição central da elipse no eixo x 
*   \param ycenter -- Posição central da elipse no eixo y 
*   \param zcenter -- Posição central da elipse no eixo z
*   \param rx -- Raio da elipse no eixo x
*   \param ry -- Raio da elipse no eixo y
*   \param rz -- Raio da elipse no eixo z */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

/** \brief Desativa todos os voxels que satisfazem à equação da elipsóide.
*   \param xcenter -- Posição central da elipse no eixo x 
*   \param ycenter -- Posição central da elipse no eixo y 
*   \param zcenter -- Posição central da elipse no eixo z
*   \param rx -- Raio da elipse no eixo x
*   \param ry -- Raio da elipse no eixo y
*   \param rz -- Raio da elipse no eixo z */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

/** \brief Aqui a função grava a escultura no formato OFF no arquivo "filename".
*   \param *filename -- Nome que o seu arquivo OFF receberá */
  void writeOFF(char* filename);
};


#ifdef __GNUC__
#include "Sculptor.cpp"
#endif // SCULPTOR_H_INCLUDED

#endif