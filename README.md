# Trabalho 2 - Campeonato Computacional de Futebol

Este projeto implementa, em C, um sistema de gerenciamento de um campeonato de futebol com 10 clubes fixos. O programa carrega os dados de times e partidas a partir de CSV, mantém tudo em memória com listas encadeadas e permite consultar, inserir, atualizar, remover e listar os registros.

## Estrutura

```text
.
├── data
│   ├── times.csv
│   ├── partidas_vazio.csv
│   ├── partidas_parcial.csv
│   ├── partidas_completo.csv
│   ├── bd_partidas.csv
│   └── bd_classificacao.csv
├── src
│   ├── main.c
│   ├── time
│   │   ├── time.c
│   │   ├── time.h
│   │   ├── bd_time.c
│   │   └── bd_time.h
│   ├── partida
│   │   ├── partida.c
│   │   ├── partida.h
│   │   ├── bd_partida.c
│   │   └── bd_partida.h
│   └── utils
│       ├── menu.c
│       └── menu.h
├── Makefile
└── README.md
```

## TADs Principais

### Time
Modela um clube com ID, nome e estatisticas acumuladas: vitórias, empates, derrotas, gols marcados e gols sofridos. Os pontos ganhos e o saldo de gols são calculados sob demanda.

### BDTimes
Gerencia a lista encadeada de times. Carrega `data/times.csv`, busca por ID, busca por prefixo, reinicia estatísticas e imprime ou exporta a classificação ordenada.

### Partida
Representa um jogo único do campeonato com ID, IDs dos times envolvidos e placar.

### BDPartidas
Gerencia a lista encadeada de partidas. Carrega o CSV, consulta por prefixo e modo de busca, insere, atualiza e remove partidas, além de reprocessar o campeonato quando os dados mudam.

## Regras Implementadas

O sistema trabalha com os 10 clubes definidos no enunciado:
`JAVAlis`, `ESCorpiões`, `SemCTRL`, `GOrilas`, `PYthons`, `SeQueLas`, `NETunos`, `LOOPardos`, `RUSTicos` e `REACTivos`.

A classificação é ordenada por:
1. Pontos ganhos
2. Vitórias
3. Saldo de gols
4. Gols marcados
5. ID

## Como Compilar

```bash
make
```

O executável é gerado em `build/programa`.

## Como Executar

Por padrão o programa carrega `data/partidas_completo.csv`:

```bash
./build/programa
```

Para usar outro arquivo de partidas:

```bash
./build/programa data/partidas_parcial.csv
```

## Menu

1. Consultar time
2. Consultar partidas
3. Atualizar partida
4. Remover partida
5. Inserir partida
6. Imprimir tabela de classificacao
Q. Sair

## Decisões de Implementação

- Times e partidas foram migrados para listas encadeadas, como pede a Parte II.
- A classificação é recalculada a partir do histórico de partidas após cada alteração.
- A ordenação da tabela foi feita em memória, sem criar estruturas excessivas.
- O projeto exporta também `data/bd_partidas.csv` e `data/bd_classificacao.csv` como artefatos gerados da base atual.

## Autores

- Artur Pedro Carvalho Silva
- André Ulhôa Borges
