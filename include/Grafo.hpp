#ifndef GRAFO_H
#define GRAFO_H

#include "Armazem.hpp"
#include <fstream>
#include <iostream>



// o TAD Grafo representa a topologia de conexões entre as unidades do Armazmes Hanoi
class Grafo {
private:
    int numVertices;
    int** matrizAdjacencia;

    Armazem* armazens;

public:
    Grafo();
    ~Grafo();

    void inicializar(int n);
    void carregar(std::ifstream& entrada);
    int* calcularRota(int origem, int destino, int &tamanho);

    Armazem* getArmazem(int id);
    int getNumVertices();
    bool armazensVazios();

    int** getMatriz();  
    void imprimir();

};


#endif