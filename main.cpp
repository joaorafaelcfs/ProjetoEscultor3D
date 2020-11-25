#include <iostream>
#include "Sculptor.h" 


using namespace std;
/** 
 *  \brief Projeto de Programação Avançada
*/
/** 
 *  Autores: João Rafael e Myllena Sila
*/

/** \n \n Criação de um boneco de neve \n */
int main(){
    Sculptor fig(70,70,70); //
    
    //Corpo  
    fig.setColor(0.9,0.9,0.9,1.0);
    fig.putSphere(30,30,40,5); 
    fig.setColor(0.9,0.9,0.9,1.0);
    fig.putSphere(30,30,30,10); 
    //Chapeu 
    fig.setColor(0,0,0,1.0); 
    fig.putBox(27,33,28,32,45,46);
    fig.setColor(0.9,0,0.7,1.0);
    fig.putBox(28,32,29,31,47,48);
    fig.setColor(0,0,0,1.0);
    fig.putBox(28,32,29,31,48,52); 
    //Olhos
    fig.setColor(0.9,0.7,0.6,1.0);
    fig.putVoxel(28,26,43);
    fig.putVoxel(32,26,43);
    //Nariz
    fig.setColor(0.9,0.5,0.3,1.0); 
    fig.putBox(30,30,23,25,42,42);
    //Boca
    fig.setColor(0.9,0,0,1.0);
    fig.putBox(29,31,25,25,40,40);
    fig.putVoxel(28,25,41);
    fig.putVoxel(32,25,41);
    //Botao
    fig.setColor(0.9,0,0.7,1.0);
    fig.putBox(30,30,21,21,34,35);
    fig.putBox(30,30,21,21,31,32);
    fig.putBox(30,30,21,21,28,29);
    fig.putBox(30,30,21,21,25,26);
    //Braço
    fig.setColor(0.5,0.3,0.3,1.0);
    fig.putBox(18,20,29,30,31,32);
    fig.putBox(16,18,29,30,32,33);
    fig.putBox(14,16,29,30,33,34);
    fig.putBox(40,42,29,30,31,32);
    fig.putBox(42,44,29,30,32,33);
    fig.putBox(44,46,29,30,33,34);

    
    fig.writeOFF("Escultura.off");
    return 0;
}