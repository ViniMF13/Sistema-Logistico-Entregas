#include "../include/Escalonador.hpp"
#include <iostream>

Escalonador::Escalonador() {
    tamanho = 0;
}

void Escalonador::troca(int i, int j) {
    Evento temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void Escalonador::subir(int i) {
    while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
        troca(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void Escalonador::descer(int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < tamanho && heap[esq] < heap[menor]) menor = esq;
    if (dir < tamanho && heap[dir] < heap[menor]) menor = dir;

    if (menor != i) {
        troca(i, menor);
        descer(menor);
    }
}

void Escalonador::insereEvento(Evento e) {
    if (tamanho >= MAX_EVENTOS) {
        std::cout << "Erro: fila de eventos cheia!" << std::endl;
        return;
    }
    
    heap[tamanho] = e;
    subir(tamanho);
    tamanho++;
}

Evento Escalonador::retiraProximo() {
    if (tamanho == 0) {
        std::cout << "Erro: fila de eventos vazia!" << std::endl;
        Evento vazio;
        return vazio;
    }
    Evento min = heap[0];
    heap[0] = heap[--tamanho];
    descer(0);
    return min;
}

bool Escalonador::vazio() {
    return tamanho == 0;
}

void Escalonador::finalizar() {
    std::cout << "\n[Estatísticas do Escalonamento]" << std::endl;
    std::cout << "Eventos restantes na fila: " << tamanho << std::endl;
    for (int i = 0; i < tamanho; i++) {
        std::cout << "Evento tipo " << heap[i].getTipo() << " agendado para " << heap[i].getExecucao() << "h\n";
    }
}