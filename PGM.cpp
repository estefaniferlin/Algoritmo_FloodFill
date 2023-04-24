#include "PGM.hpp"

#include <iostream>
using namespace std;

PGM::PGM(){
    pixels = nullptr;
	larg = 0;
	alt = 0;
	tipo = "";
}

void PGM::flip()
{
    for(int y=0; y <alt/2; y++) // trocar apenas a metade 
    {
        for(int x=0; x <larg; x++) // x troca até o final
        {
            unsigned char aux1 = getPixel(x,y);
            unsigned char aux2 = getPixel(x, alt - 1 - y); 
            setPixel(x,y, aux2);
            setPixel(x, alt - 1 - y, aux1);
        }
    }
}

void PGM::setCriar(int largura, int altura)
{
    this->larg = largura;
    this->alt = altura;

    this->tipo = "P2";
    this->pixels = new unsigned char [larg * alt];
    for(int i=0; i<larg *alt; i++)
        this->pixels[i] = 0;
}

void PGM::colorirLinha(unsigned char cor, int intervalo)
{
    for(int y = intervalo; y < alt; y += intervalo)
        for(int x = 0; x < larg; x++)
        this->setPixel(x, y, cor); //passar os pontos de referência
}

void PGM::setRegiao(int x1, int y1, int x2, int y2, unsigned cor)
{
    
    if(!pixels)
    {
        cout << "Leia a imagem primeiro!!\n";
        return;
    }

    for(int y=y1; y<=y2; y++)
    {
        for(int x=x1; x<=x2; x++)
        {
            if(x>=0 && x<larg && y>=0 && y<alt)
                this->setPixel(x, y, cor);
        }
    }
        
}

void PGM::setCoordenada(int x1, int y1, int x2, int y2, PGM *imgS)
{
    
    if(!pixels)
    {
        cout << "Leia a imagem primeiro!!\n";
        return;
    }
    unsigned char aux;

    cout<<"oi"<<endl;

    for(int y=y1; y<=y2; y++)
    {
        for(int x=x1; x<=x2; x++)
        {
            cout<<"oi muanoite"<<endl;
            if(x>=0 && x<larg && y>=0 && y<alt)
            {
                aux = this->getPixel(x,y);
                imgS->setPixel(x,y,aux);
            }
        }
    }
        
}


void PGM::setLinha(int linha, unsigned char cor)
{
    if(!pixels)
    {
        cout << "Leia a imagem primeiro!!\n";
        return;
    }

    if(linha < 0 || linha >= larg)
    {
        cout << "Informe uma cooredenada válida para a linha!!\n";
        return;
    }

    for(int x=0; x<larg; x++)
        this->setPixel(x, linha, cor);  //percorre todos os elementos x de uma linha
}

PGM::~PGM() {
    if (pixels)
        delete pixels;
    pixels = nullptr;
}


int PGM::getLargura()
{
    return larg;
}

int PGM::getAltura()
{
    return alt;
}


unsigned char* & PGM::getPixels()
{
    return pixels;
}

unsigned char PGM::getPixel(int x, int y){
    return pixels[y*larg + x];
}

void PGM::setPixel(int x, int y, unsigned char cor){

    if(pixels)
        pixels[y*larg + x] = cor;
}

bool PGM::ler(string caminho) {
    ifstream arq;
    string aux;

    

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }
    tipo = aux;


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a largura da imagem\n";
        return false;
    }
    larg = atoi(aux.c_str());

    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler a altura da imagem\n";
        return false;
    }
    alt = atoi(aux.c_str());


    if (!lerDado(arq, &aux)) {
        cout << "PGM: erro ao ler o valor máximo de cor\n";
        return false;
    }
    vmax = atoi(aux.c_str()); // valor máximo de cor

    if (pixels)
        delete pixels;
    pixels = new unsigned char[larg * alt]; //valor de era nulo passa a ter o tamanho da imagem

    int i = 0; // lê os valores e aloca
    while (!arq.eof()) {
        if (!lerDado(arq, &aux)) {
            break;
        }

        pixels[i] = (unsigned char) atoi(aux.c_str());
        i++;

    }

    //cout << "i: " << i << endl;
    if (i != larg * alt) {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }

    //cout << this->tipo << endl;
    //cout << this->larg << endl;
    //cout << this->alt << endl;
    //cout << this->vmax << endl;


    return true;
}

bool PGM::gravar(string caminho) { // grava a saída 

    if (!pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open()) {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << tipo << endl;

    arq << larg << " " << alt << endl; //pode ser adicionado um comentário 

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = larg * alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int) pixels[i] << endl;
        arq.flush();
    }
        

    arq.close();
    return true;
}

bool PGM::lerDado(ifstream &arq, string *dado) {
    string aux;
    while (!arq.eof()) {
        arq >> aux;
        if (aux.size() > 0 && aux[0] == '#') {
            std::getline(arq, aux);
        }else if(aux.size() > 0){
            *dado = aux;
            return true;
        }

        aux = "";
    }
    return false;
}
