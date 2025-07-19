#ifndef PACOTE_H
#define PACOTE_H

/*
    ESTADOS:
    1. Não foi postado
    2. Chegada escalonada a um armazém (postagem ou transporte)
    3. Armazenado na seção associada ao próximo destino de um armazém
    4. Removido da seção para transporte
    5. Entregue
*/

class Pacote {
private:
    int id;
    int tempo_postagem;
    int origem;
    int destino;
    int estado_atual;
    char remetente[50];
    char destinatario[50];
    char tipo[30];

    // rota 
    int tamanho_rota;
    int posicao_atual;
    int* rota; 
    
    // estatísticas
    int tempo_armazenado_total;
    int tempo_transporte_total;

public:
    Pacote();
    Pacote(const Pacote& outro);            // Construtor de cópia
    Pacote& operator=(const Pacote& outro); // Operador de atribuição
    ~Pacote();


    void inicializar(int id, const char* remetente, const char* destinatario, const char* tipo, int origem, int destino, int data_postagem, int tam_rota);

    void definirRota(int* rota);
    bool avancarNaRota();
    void avancarEstado();

    void registrarTempoArmazenado(int inicio, int fim);
    void registrarTempoTransporte(int inicio, int fim);

    void imprimirEstatisticas();
    
    //getters
    int getID();
    int getTempoPostagem();

    int getOrigem();
    int getDestino();

    int getArmazemAtual();
    int getProximoArmazem();

    int getTamanhoRota();
    int* getRota();
    int getEstado();

};

#endif