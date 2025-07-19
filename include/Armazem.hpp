#ifndef ARMAZEM_H
#define ARMAZEM_H

#include "Pacote.hpp"

// Estrutura de nó da pilha
struct NoPilha {
    Pacote* pacote;
    NoPilha* proximo;
};

class Armazem {
private:
    int id;
    int numSecoes;
    NoPilha** secoes; // Array de pilhas (uma para cada possível destino)

public:
    Armazem();
    ~Armazem();

    void inicializar(int id_, int n);
    void armazenarPacote(Pacote* pacote);
    Pacote* recuperarPacote(int destino);
 
    bool secaoVazia(int destino) const;
    bool secoesVazias();
    void imprimirSecao(int destino);
    
    int getID();
    NoPilha** getSecoes();
};

#endif