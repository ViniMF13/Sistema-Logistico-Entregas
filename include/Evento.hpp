#ifndef EVENTO_H
#define EVENTO_H
#include "Pacote.hpp"

class Evento {
    private:
    int tipo;            
    int execucao;          
    int origem;
    int destino;
    Pacote* pacote;     
    int contador;

    public:
    Evento();
    void inicializar(int T, int tempo, Pacote* P);
    bool operator<(const Evento& outro) const;
    // Setters
    void setOrigem(int orig);
    void setDestino(int dest);
    void setContador(int c);
    //getters
    int getTipo();
    int getExecucao();
    int getOrigem();
    int getDestino();
    int getContador(); // Novo getter
    Pacote* getPacote();
};

#endif