#include "../include/Evento.hpp"
#include <cstring>
#include <cstdio>
 
 
 Evento::Evento(){
    tipo = -1;            
    execucao = -1;          
    origem = -1;
    destino = -1;
    pacote = nullptr;
    contador = 0;
 }

 void Evento::inicializar(int T, int tempo, Pacote* P){
    tipo = T;
    execucao = tempo;
    pacote = P;
    if(T == 2 && P != nullptr) {
        origem = P->getArmazemAtual(); 
        destino = P->getProximoArmazem();
    }
}

// operador de comparação para chaves
bool Evento::operator<(const Evento& outro) const {
    if (execucao != outro.execucao)
        return execucao < outro.execucao; // > porque vamos usar min-heap

    // Empate no tempo, decidir por ID do pacote ou chave auxiliar
    if (tipo == 1 && outro.tipo == 1)
        return pacote->getID() < outro.pacote->getID();

    if (tipo == 2 && outro.tipo == 2) {
        if (origem != outro.origem)
            return origem < outro.origem;
        return destino < outro.destino;
    }

    // Desempate final por tipo (priorizar chegada de pacote)
    return tipo > outro.tipo;
}

// Setters
void Evento::setOrigem(int orig) { origem = orig; }
void Evento::setDestino(int dest) { destino = dest; }
void Evento::setContador(int c) { contador = c; }

// Getters
int Evento::getTipo() { return tipo; }
int Evento::getExecucao() { return execucao; }
int Evento::getOrigem() { return origem; }
int Evento::getDestino() { return destino; }
int Evento::getContador() { return contador; } 
Pacote* Evento::getPacote() { return pacote; }

