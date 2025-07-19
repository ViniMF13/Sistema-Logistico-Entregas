#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "Evento.hpp"

#define MAX_EVENTOS 100000

class Escalonador {
private:
    Evento heap[MAX_EVENTOS];
    int tamanho;

    void subir(int i);
    void descer(int i);
    void troca(int i, int j);

public:
    Escalonador();                
    void insereEvento(Evento e);  
    Evento retiraProximo();      

    bool vazio();
    void finalizar();               
};

#endif