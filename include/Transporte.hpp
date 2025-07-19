#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include "Pacote.hpp"
#include "Escalonador.hpp"
#include "Armazem.hpp"

class Transporte {
private:
    int capacidade;
    int tempo_transportar; 
    int intervalo_transporte; 
    int custo_remocao;  

public:
    Transporte();
    void inicializar(int cap, int tampo_trans, int intervalo_trans, int custo_rem);
    void processarTransporte(Armazem* origem, int destino, Escalonador& escalonador, int tempoAtual);
};

#endif