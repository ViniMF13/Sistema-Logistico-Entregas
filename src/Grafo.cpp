#include "../include/Grafo.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

Grafo::Grafo() {
    matrizAdjacencia = nullptr;
    numVertices = 0;
    armazens = nullptr;
}

Grafo::~Grafo() {
    if (matrizAdjacencia != nullptr) {
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrizAdjacencia[i];
        }
        delete[] matrizAdjacencia;
        matrizAdjacencia = nullptr;
    }

    if (armazens != nullptr) {
        delete[] armazens;  // chama o destrutor de cada Armazem 
        armazens = nullptr;
    }
}

void Grafo::inicializar(int n) {
    numVertices = n;
    matrizAdjacencia = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrizAdjacencia[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrizAdjacencia[i][j] = 0;
        }
    }
    
    // Inicializa os objetos armazém
    armazens = new Armazem[n]; 
    for (int i = 0; i < n; ++i) {
        armazens[i].inicializar(i, n); 
    }
}

void Grafo::carregar(std::ifstream& entrada) {
    entrada >> numVertices;
    inicializar(numVertices);

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            entrada >> matrizAdjacencia[i][j];
        }
    }
}

bool Grafo::armazensVazios(){
    for(int i = 0; i < numVertices; i++){
        if( !(armazens[i].secoesVazias()) ){
            return false;
        }
    }
    return true;
}

int Grafo::getNumVertices() {
    return numVertices;
}

int** Grafo::getMatriz() {
    return matrizAdjacencia;
}

Armazem* Grafo::getArmazem(int id){
    if (id < 0 || id >= numVertices) {
        return nullptr;
    }
    return &armazens[id];
}

// BFS para encontrar a menor rota entre origem e destino (busca em largura)
int* Grafo::calcularRota(int origem, int destino, int& tamanhoRota) {
    // Verificar se origem e destino são válidos
    if (origem < 0 || origem >= numVertices || 
        destino < 0 || destino >= numVertices) {
        tamanhoRota = 0;
        return nullptr;
    }
    // Se origem e destino são iguais
    if (origem == destino) {
        tamanhoRota = 1;
        int* rota = new int[1];
        rota[0] = origem;
        return rota;
    }

    // Estruturas para BFS
    bool* visitado = new bool[numVertices];
    int* fila = new int[numVertices];
    int frente = 0, tras = 0;
    int* predecessores = new int[numVertices];

    for (int i = 0; i < numVertices; ++i) {
        visitado[i] = false;
        predecessores[i] = -1;
    }

    // Início da BFS
    visitado[origem] = true;
    fila[tras++] = origem;

    bool encontrou = false;
    while (frente < tras && !encontrou) {
        int atual = fila[frente++];
        
        // Explora todos os vizinhos
        for (int vizinho = 0; vizinho < numVertices; vizinho++) {
            if (matrizAdjacencia[atual][vizinho] == 1 && !visitado[vizinho]) {
                visitado[vizinho] = true;
                predecessores[vizinho] = atual;
                fila[tras++] = vizinho;
                
                if (vizinho == destino) {
                    encontrou = true;
                    break;
                }
            }
        }
    }

    // Reconstruir caminho se encontrado
    int* rota = nullptr;
    tamanhoRota = 0;
    
    if (encontrou) {
        // Calcular tamanho do caminho
        int contador = 0;
        for (int no = destino; no != -1; no = predecessores[no]) {
            contador++;
        }
        
        tamanhoRota = contador;
        rota = new int[tamanhoRota];

        // Preencher caminho (invertido)
        int indice = tamanhoRota - 1;
        for (int no = destino; no != -1; no = predecessores[no]) {
            rota[indice--] = no;
        }
    }
    
    // Liberar memória
    delete[] visitado;
    delete[] predecessores;
    delete[] fila;

    return rota;
}