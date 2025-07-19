#include "../include/Armazem.hpp"
#include <cstdio>

Armazem::Armazem() : id(-1), numSecoes(0), secoes(nullptr) {}

Armazem::~Armazem() {
    if (secoes != nullptr) {
        for (int i = 0; i < numSecoes; ++i) {
            NoPilha* atual = secoes[i];
            while (atual != nullptr) {
                NoPilha* temp = atual;
                atual = atual->proximo;
                
                delete temp;
            }
        }
        delete[] secoes;
    }
}

void Armazem::inicializar(int id_, int n) {
    id = id_;
    numSecoes = n ;
    secoes = new NoPilha*[numSecoes]; // vetor de ponteiros
    for (int i = 0; i < numSecoes; ++i) {
        secoes[i] = nullptr; 
    }
}

void Armazem::armazenarPacote(Pacote* pacote) {
    int destino = pacote->getProximoArmazem();
    if (destino < 0 || destino >= numSecoes) return;

    // empilha o pacote na seção correspondente
    NoPilha* novo = new NoPilha; 
    novo->pacote = pacote; 
    novo->proximo = secoes[destino];
    secoes[destino] = novo;
 
}

Pacote* Armazem::recuperarPacote(int destino) {
    if (destino < 0 || destino >= numSecoes || !secoes[destino]) 
        return nullptr;

    // Desempilhar diretamente da seção correspondente
    NoPilha* topo = secoes[destino];
    Pacote* pacote = topo->pacote;
    secoes[destino] = topo->proximo;
    
    delete topo;
    return pacote;
}

bool Armazem::secaoVazia(int destino) const {
    if (destino < 0 || destino >= numSecoes) return true;
    return secoes[destino] == nullptr;
}

bool Armazem::secoesVazias(){
    for (int i = 0; i < numSecoes; i++) {
        if (secoes[i] != nullptr) return false;
    }
    return true;
}
    
int Armazem::getID() { return id; }

NoPilha** Armazem::getSecoes() { return secoes; }