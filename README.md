# Armazéns Hanoi - Simulação Logística com Eventos Discretos

Este projeto simula um sistema logístico de transporte de pacotes entre armazéns conectados em uma rede com topologia de grafo. Utiliza programação orientada a objetos em C++ e modelagem por eventos discretos para representar o fluxo de pacotes, armazenamento em seções e transporte entre os nós da rede.

## 🧠 Objetivo

O objetivo é estudar e implementar um sistema de simulação realista envolvendo:
- Roteamento de pacotes entre armazéns
- Armazenamento com política LIFO (Last-In, First-Out)
- Transporte periódico e com capacidade limitada
- Agendamento e execução de eventos discretos
- Coleta e análise de métricas experimentais de desempenho

## 🛠️ Estrutura do Projeto

```
├── src/
│   ├── main.cpp                # Função principal e loop da simulação
│   ├── Grafo.cpp               # Representação da rede de armazéns
│   ├── Armazem.cpp             # Armazenamento e seções
│   ├── Pacote.cpp              # Dados e estado de cada pacote
│   ├── Transporte.cpp          # Módulo de transporte com rearmazenamento
│   ├── ListaPacotes.cpp        # Lista ligada com pacotes
│   └── Escalonador.cpp         # Fila de prioridade para eventos
├── include/                    # Headers correspondentes
├── bin/                        # Binários compilados
├── input.txt                   # Arquivo de entrada com configuração e pacotes
├── README.md                   # Este arquivo
└── Makefile                    # Compilação automatizada
```

## ▶️ Execução

### Compilar
```bash
make
```

### Executar
```bash
./bin/tp2.out input.txt
```

> O arquivo `input.txt` deve conter a configuração do sistema (parâmetros logísticos, matriz de conexões e pacotes a serem transportados).

## 📊 Análise Experimental

A simulação foi utilizada para investigar o impacto de diferentes fatores, como:

- Variação do número de armazéns
- Quantidade de pacotes
- Capacidade de transporte
- Intervalos e tempos de transporte

### Métricas observadas:
- Tempo médio de entrega
- Número de rearmazenamentos
- Tempo de execução

Gráficos e tabelas estão disponíveis na documentação em LaTeX.

## 🔐 Robustez e Engenharia

O projeto aplica:
- Programação defensiva (checagens de ponteiros nulos, limites de array, falhas de abertura de arquivos)
- Liberação de memória dinâmica (destrutores customizados, `delete[]`)
- Cópia profunda em objetos complexos (`Pacote`)
- Validação de entradas e controle de estado

## 🧪 Tecnologias

- C++11
- Estruturas de dados: listas ligadas, heaps, pilhas, matrizes
- Simulação orientada a eventos
- Algoritmos de busca em largura (BFS)
- Modelagem discreta de sistemas logísticos

## 📘 Documentação

A documentação técnica completa foi elaborada em LaTeX e inclui:
- Diagrama de classes UML
- Análise de complexidade de funções principais
- Estratégias de robustez
- Análise experimental com gráficos

## 👨‍💻 Autor

Vinicius Sv13  
Contato: [Seu e-mail ou LinkedIn]

## 📝 Licença

Este projeto é de uso acadêmico e pessoal. Sinta-se à vontade para estudar, modificar e expandir.
