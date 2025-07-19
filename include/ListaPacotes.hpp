#ifndef LISTA_PACOTES_H
#define LISTA_PACOTES_H

#include "Pacote.hpp"
#include "Grafo.hpp"


struct NodoPacote {
    Pacote pacote;
    NodoPacote* proximo;
};

struct ListaPacotes {
    NodoPacote* inicio;
    int tamanho;
    
    ListaPacotes();
    ~ListaPacotes();
    void carregar(std::ifstream& entrada, Grafo& armazens);
    void inserirPacote(const Pacote& p);
    Pacote* buscarPacotePorID(int id);
    void imprimirTodos();
    void destruir();
};

#endif