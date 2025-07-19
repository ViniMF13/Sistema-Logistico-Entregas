#include "../include/Pacote.hpp"
#include <cstring>
#include <cstdio>

/*
1. Não foi postado
2. Chegada escalonada a um armazém (postagem ou transporte)
3. Armazenado na seção associada ao próximo destino de um armazém
4. Removido da seção para transporte
5. Entregue
*/

Pacote::Pacote() 
    : id(-1), tempo_postagem(0), origem(-1), destino(-1), estado_atual(1),
      tamanho_rota(0), posicao_atual(0), tempo_armazenado_total(0),
      tempo_transporte_total(0), rota(nullptr) 
{
    strcpy(remetente, "");
    strcpy(destinatario, "");
    strcpy(tipo, "");
}

Pacote::~Pacote() {
   if (rota) {
        delete[] rota;
        rota = nullptr;
    }
}

// Construtor de cópia
Pacote::Pacote(const Pacote& outro) {
    id = outro.id;
    tempo_postagem = outro.tempo_postagem;
    strcpy(remetente, outro.remetente);
    strcpy(destinatario, outro.destinatario);
    strcpy(tipo, outro.tipo);
    origem = outro.origem;
    destino = outro.destino;
    estado_atual = outro.estado_atual;
    tamanho_rota = outro.tamanho_rota;
    posicao_atual = outro.posicao_atual;
    tempo_armazenado_total = outro.tempo_armazenado_total;
    tempo_transporte_total = outro.tempo_transporte_total;

    // Deep Copy da rota
    if (outro.rota && tamanho_rota > 0) {
        rota = new int[tamanho_rota];
        for (int i = 0; i < tamanho_rota; ++i) {
            rota[i] = outro.rota[i];
        }
    } else {
        rota = nullptr;
    }
}

// Operador de atribuição
Pacote& Pacote::operator=(const Pacote& outro) {
    if (this == &outro) {
        return *this;
    }

    // Libera recursos existentes
    if (rota) {
        delete[] rota;
        rota = nullptr;
    }

    id = outro.id;
    tempo_postagem = outro.tempo_postagem;
    strcpy(remetente, outro.remetente);
    strcpy(destinatario, outro.destinatario);
    strcpy(tipo, outro.tipo);
    origem = outro.origem;
    destino = outro.destino;
    estado_atual = outro.estado_atual;
    tamanho_rota = outro.tamanho_rota;
    posicao_atual = outro.posicao_atual;
    tempo_armazenado_total = outro.tempo_armazenado_total;
    tempo_transporte_total = outro.tempo_transporte_total;

    // Cópia profunda da rota
    if (outro.rota && tamanho_rota > 0) {
        rota = new int[tamanho_rota];
        for (int i = 0; i < tamanho_rota; ++i) {
            rota[i] = outro.rota[i];
        }
    } else {
        rota = nullptr;
    }

    return *this;
}

void Pacote::inicializar(int id_, const char* rem, const char* dest, const char* tipo_, int org, int dst, int data, int tam_rota) {
    id = id_;
    strcpy(remetente, rem);
    strcpy(destinatario, dest);
    strcpy(tipo, tipo_);
    origem = org;
    destino = dst;
    tempo_postagem = data;
    tamanho_rota = tam_rota;
    
}

void Pacote::definirRota(int* nova_rota) {
    // Libera a rota antiga se existir
    if (rota) {
        delete[] rota;
        rota = nullptr;
    }
    
    // Aloca espaço para a nova rota
    rota = new int[tamanho_rota];
    for (int i = 0; i < tamanho_rota; ++i) {
        rota[i] = nova_rota[i];
    }
    posicao_atual = 0;
}

bool Pacote::avancarNaRota() {
    if (posicao_atual + 1 < tamanho_rota) {
        posicao_atual++;
        return true;
    }
    return false;
}

void Pacote::avancarEstado() {
    if (estado_atual < 6)
        estado_atual++;
}

int Pacote::getTamanhoRota() { return tamanho_rota; }

int* Pacote::getRota() { return rota; }

int Pacote::getEstado() {
    return estado_atual;
}

void Pacote::registrarTempoArmazenado(int inicio, int fim) {
    tempo_armazenado_total += (fim - inicio);
}

void Pacote::registrarTempoTransporte(int inicio, int fim) {
    tempo_transporte_total += (fim - inicio);
}

void Pacote::imprimirEstatisticas() {
    printf("Pacote ID: %d\n", id);
    printf("Remetente: %s\n", remetente);
    printf("Destinatário: %s\n", destinatario);
    printf("Tipo: %s\n", tipo);
    printf("Origem: %d → Destino: %d\n", origem, destino);
    printf("Estado atual: %d\n", estado_atual);
    printf("Tempo armazenado total: %d\n", tempo_armazenado_total);
    printf("Tempo transporte total: %d\n", tempo_transporte_total);
}

int Pacote::getID() {
    return id;
}

int Pacote::getTempoPostagem() {
    return tempo_postagem;
}

int Pacote::getOrigem(){
    return origem;
}

int Pacote::getDestino(){
    return destino;
}

int Pacote::getArmazemAtual() {
    if (posicao_atual < tamanho_rota)
        return rota[posicao_atual];
    return -1;
}

int Pacote::getProximoArmazem() {
    if (posicao_atual < tamanho_rota)
        return rota[posicao_atual + 1];
    return -1;
}

