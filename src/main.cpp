
#include "../include/Grafo.hpp"
#include "../include/Armazem.hpp"
#include "../include/Transporte.hpp"
#include "../include/Pacote.hpp"
#include "../include/ListaPacotes.hpp"
#include "../include/Escalonador.hpp"

#include <iostream>
#include <fstream>   
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <input.txt>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o arquivo " << argv[1] << endl;
        return 1;
    }

    // variáveis de sistema
    int capacidade_transporte, tempo_transporte, intervalo_transporte, custo_remocao;
    file >> capacidade_transporte >> tempo_transporte >> intervalo_transporte >> custo_remocao;

    // inicializa as estruturas do sistema
    Grafo armazens;
    armazens.carregar(file);

    ListaPacotes pacotes;
    pacotes.carregar(file, armazens);   
    
    Transporte carreta;
    carreta.inicializar(capacidade_transporte, tempo_transporte, intervalo_transporte, custo_remocao);

    Escalonador escalonador;
        
    int relogio = 0;
    int pacotesEntregues = 0;

    // Agendar eventos iniciais de postagem
    NodoPacote* atual = pacotes.inicio;
    while (atual != nullptr) {
        Evento e;
        e.inicializar(1, atual->pacote.getTempoPostagem(), &(atual->pacote));
        escalonador.insereEvento(e);
        atual = atual->proximo;   

        
    }

    // Agendar eventos de transporte iniciais
    int n = armazens.getNumVertices();
    int** matriz = armazens.getMatriz();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (matriz[i][j] == 1) {
                // primeiro transporte após chegada do primeiro pacote no armazem de postagem
                relogio = pacotes.buscarPacotePorID(0)->getTempoPostagem();
                // Transporte i->j
                Evento evt;
                evt.inicializar(2, relogio + intervalo_transporte, nullptr);
                evt.setOrigem(i);
                evt.setDestino(j);
                evt.setContador(0);
                escalonador.insereEvento(evt);
                
                // Transporte j->i
                Evento evt2;
                evt2.inicializar(2, relogio + intervalo_transporte, nullptr);
                evt2.setOrigem(j);
                evt2.setDestino(i);
                evt2.setContador(0);
                escalonador.insereEvento(evt2);
            }
        }
    }

    // Loop principal da simulação (enquanto o escalonador ou os armazens não estiverem vazios)
    while (!escalonador.vazio() && pacotesEntregues < pacotes.tamanho) {
        Evento eventoAtual = escalonador.retiraProximo(); 
        relogio = eventoAtual.getExecucao();
        int tipo = eventoAtual.getTipo();
        
        if(tipo == 1){ // Evento de chegada de pacote ao armazém
            Pacote* p = eventoAtual.getPacote();
            if (!p) continue; // ← Isso evita crash
            //int estado = p->getEstado();

            if(p->getEstado() > 1){ // chegada no armazém de postagem
                p->avancarNaRota();
            }

            int armazemAtual = p->getArmazemAtual(); // retorna rota[posicao_atual]
            int proxArmazem  = p->getProximoArmazem();  // retorna rota[posicao_atual + 1]
            int destinoFinal = p->getDestino(); // retorna o ID do armazem de destino

            if (armazemAtual == destinoFinal) { // Chegada ao destino Final 
                printf("%07d pacote %03d entregue em %03d\n", 
                    relogio, p->getID(), destinoFinal);
                pacotesEntregues++;
            } else {
                // Armazena o pacote na seçao atual 
                Armazem* a = armazens.getArmazem(armazemAtual);
                a->armazenarPacote(p);
                
                printf("%07d pacote %03d armazenado em %03d na secao %03d\n", 
                      relogio, p->getID(), armazemAtual, proxArmazem);
                p->avancarEstado(); 
            }

        } else if(tipo == 2){ // evento de transporte 
            Armazem* a = armazens.getArmazem(eventoAtual.getOrigem());
            int destino = eventoAtual.getDestino();
            
            carreta.processarTransporte(a, destino, escalonador, relogio);
 
            // Agendar próximo evento de transporte
            Evento proxTransporte; 
            proxTransporte.inicializar(2, relogio + intervalo_transporte, nullptr);
            proxTransporte.setOrigem(a->getID());
            proxTransporte.setDestino(destino);
            escalonador.insereEvento(proxTransporte);
        
        }else if(tipo == -1){
            return 0;
        }
    }
    return 0;
}

