#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED

#include <string>
#include <fstream>

class PGM
{
public:
    PGM(); // construtor
    ~PGM(); //desconstrutor

    void flip();

    void setCriar(int larg, int alt);

    void colorirLinha(unsigned char cor, int intervalo);

    void setLinha(int linha, unsigned char cor);

    void setRegiao(int x1, int y1, int x2, int y2, unsigned cor); 

    void setCoordenada(int x1, int y1, int x2, int y2, PGM *imgS);

    bool ler(std::string caminho); //lê a imagem no caminho 
	
    bool gravar(std::string caminho); //grava a imagem no caminho

     //retorna o vetor de pixels por referência! As alteraçõe realizadas fora da classe serão gravadas no vetor!
    unsigned char* & getPixels();
    
    unsigned char getPixel(int x, int y);

    void setPixel(int x, int y, unsigned char cor);

    int getLargura();
	
    int getAltura();


private:
    bool lerDado(std::ifstream &arq, std::string *dado);

    std::string tipo;
	int larg; //largura da imagem
	int alt; // altura
	int vmax; // valor máximo
	unsigned char* pixels; // unsigned char -> 0 a 255

};

#endif