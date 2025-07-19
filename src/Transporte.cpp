#include "../include/Transporte.hpp"
#include <cstdio>

Transporte::Transporte() {
    tempo_transportar = 0;
    intervalo_transporte = 0;
    capacidade = 0;
    custo_remocao = 0;
}

void Transporte::inicializar(int cap, int tempo_trans, int intervalo_trans, int tempo_rem) {
    capacidade = cap;
    tempo_transportar = tempo_trans;
    intervalo_transporte = intervalo_trans;
    custo_remocao = tempo_rem;
}

void Transporte::processarTransporte(Armazem* origem, int destino, Escalonador& escalonador, int tempoAtual) {
    if (!origem || capacidade <= 0) return;
    
    int idOrigem = origem->getID();
    int tempoRemocao = tempoAtual; 
   
   //criar pilha invertida
   NoPilha* pilhaInvertida = nullptr;
    
    // Desempilhar todos os pacotes da seção 
    while (!origem->secaoVazia(destino)) {
        Pacote* p = origem->recuperarPacote(destino);
        if (!p) break;

        tempoRemocao += custo_remocao;
        
        // Registrar remoção
        printf("%07d pacote %03d removido de %03d na secao %03d\n", 
               tempoRemocao, p->getID(), idOrigem, destino);
        
        // empilhar na pilha invertida
        NoPilha* novo = new NoPilha;
        novo->pacote = p; // cópia do pacote criado na stack atual
        novo->proximo = pilhaInvertida;
        pilhaInvertida = novo;
    }

    // Desempilhar diretamente da pilha invertida e transportar até a capacidade 
    int transportados = 0;
   
    while (pilhaInvertida != nullptr && transportados < capacidade){
        NoPilha* topo = pilhaInvertida;
        Pacote* pacote = topo->pacote;
        pilhaInvertida = topo->proximo;
        
        delete topo;

        // Registrar transporte e avançar na rota
        printf("%07d pacote %03d em transito de %03d para %03d\n", 
                tempoRemocao, pacote->getID(), idOrigem, 
                pacote->getProximoArmazem());

        // Agendar chegada no próximo armazém
        Evento chegada;
        chegada.inicializar(1, tempoRemocao + tempo_transportar, pacote);
        escalonador.insereEvento(chegada);
        transportados++;  
    }
    
    // Rearmazenar pacotes restantes na pilha invertida
    while (pilhaInvertida != nullptr) {
        origem->armazenarPacote(pilhaInvertida->pacote);
        printf("%07d pacote %03d rearmazenado em %03d na secao %03d\n",
               tempoRemocao, pilhaInvertida->pacote->getID(), idOrigem, destino);

        NoPilha* temp = pilhaInvertida;
        pilhaInvertida = pilhaInvertida->proximo;
        delete temp;
    }
}
    



