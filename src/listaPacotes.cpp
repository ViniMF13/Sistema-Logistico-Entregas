#include "../include/ListaPacotes.hpp"
#include <fstream>

using namespace std;

ListaPacotes::ListaPacotes(){
    inicio = nullptr;
    tamanho = 0;
}

ListaPacotes::~ListaPacotes() {
        destruir();
}

void ListaPacotes::carregar(std::ifstream& entrada, Grafo& armazens) {
    int m; 
    entrada >> m;
   
    for (int i = 0; i < m; ++i) {
        int data, origem, destino;
        std::string dummy;
        
        entrada >> data >> dummy; // "pac"
        entrada >> dummy >> dummy;   // "org"
        entrada >> origem >> dummy; // "dst"
        entrada >> destino;

        //calcula a rota 
        int tamanho_rota = 0;
        int* rota = armazens.calcularRota(origem, destino, tamanho_rota);

        //criação e inicialização de um objeto do tipo Pacote
        Pacote p;
        p.inicializar(i, "org", "dst", "pac", origem, destino, data, tamanho_rota);
        p.definirRota(rota);  
         
        //inserção do pacote na lista 
        inserirPacote(p);
        
        delete[] rota;
    }
}

void ListaPacotes::inserirPacote(const Pacote& p) {
    NodoPacote* novo = new NodoPacote;
    novo->pacote = p; // aqui o pacote é copiado para o nó
    novo->proximo = inicio;
    inicio = novo;
    tamanho++;
}

Pacote* ListaPacotes::buscarPacotePorID(int id) {
    NodoPacote* atual = inicio;
    while (atual != nullptr) {
        if (atual->pacote.getID() == id)
            return &(atual->pacote);
        atual = atual->proximo;
    }
    return nullptr;
}

void ListaPacotes::destruir() {
    NodoPacote* atual = inicio;
    while (atual != nullptr) {
        NodoPacote* temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    inicio = nullptr;
}