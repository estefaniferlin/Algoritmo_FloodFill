#include <iostream>
#include <fstream>
#include "PGM.hpp"

using namespace std;

void floodfill(PGM *img, int x, int y, unsigned char corNova, unsigned char corVelha)
{
    // Verifica se o pixel atual está dentro da imagem 
    if (x < 0 || x >= img->getLargura() || y < 0 || y >= img->getAltura() || img->getPixel(x, y) != corVelha) // Compara cor do pixel atual com a cor velha
    {
        return;
    }

    // Se a cor do Pixel atual for igual a cor antiga

    // Preenche o pixel atual com a nova cor
    img->setPixel(x, y, corNova);

    // Preenche os pixels vizinhos recursivamente
    floodfill(img, x + 1, y, corNova, corVelha);
    floodfill(img, x - 1, y, corNova, corVelha);
    floodfill(img, x, y + 1, corNova, corVelha);
    floodfill(img, x, y - 1, corNova, corVelha);
}

int main(void)
{
    // declaração de variáveis
    const int x = 7;
    const int y = 1;
    const unsigned char newColor = 255; // 255 = branco

    PGM *img = new PGM(); 

    // realiza a leitura da imagem 
    img->ler("feep.pgm");

    cout << "Inciando Algoritmo" << endl;

    // variável oldColor recebe a cor antiga do pixel (x,y) na imagem
    unsigned char oldColor = img->getPixel(x, y);

    // Chama a função de preenchimento
    floodfill(img, x, y, newColor, oldColor);

    //grava a imagem resultante 
    img->gravar("saida.pgm");

    // Desaloca memória
    delete img;

    return EXIT_SUCCESS;
}
