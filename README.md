# Trabalho 1 - Campeonato de Futebol

Este projeto consiste na implementação de um sistema em linguagem C para gerenciamento e consulta de dados de um campeonato de futebol. O sistema é alimentado por arquivos persistidos em formato CSV (times e partidas), processa os resultados em memória e disponibiliza consultas detalhadas e tabelas de classificação para o usuário.

O projeto foi desenvolvido com foco em modularização, uso inteligente de memória (combinando alocação dinâmica e estática) e integridade de dados por meio de encapsulamento em Tipos Abstratos de Dados (TADs).

## Regras do Campeonato

* Composição: O campeonato possui exatamente 10 clubes fixos (indexados de 0 a 9).

* Formato: Disputado em turno único de pontos corridos (todos contra todos, sem repetição).

* Pontuação: Vitória confere 3 pontos, empate confere 1 ponto e derrota 0 pontos.

* Critérios de Classificação: Vitórias (V), Empates (E), Derrotas (D), Gols Marcados (GM), Gols Sofridos (GS), Saldo de Gols (S = GM - GS) e Pontos Ganhos (PG = 3V + E).

---

## Estrutura do Projeto

Separamos nossa implementação por módulos, dividindo source(src) de dados (data), e subdividindo o módulo src em time, partidas, e utils (responsável pelo display do menu) além de build para conter nosso arquivo compilado

```
    └── 📁build
        ├── programa
    └── 📁data
        ├── bd_classificacao.csv
        ├── bd_partidas.csv
        ├── partidas_completo.csv
        ├── partidas_parcial.csv
        ├── partidas_vazio.csv
        ├── times.csv
    └── 📁src
        └── 📁partida
            ├── bd_partida.c
            ├── bd_partida.h
            ├── partida.c
            ├── partida.h
        └── 📁time
            ├── bd_time.c
            ├── bd_time.h
            ├── time.c
            ├── time.h
        └── 📁utils
            ├── menu.c
            ├── menu.h
        ├── main.c
    ├── Makefile
    └── README.md
```
Diagrama feito pela extensão do vscode Draw Folder Structure

---

## Organização dos Módulos e TADs



### Time
### TAD Time
* time.h e time.c: Definem a estrutura de dados(TAD) Time que encapsula o ID, nome e as variáveis acumuladoras de desempenho (Vitórias, Empates, Derrotas, Gols Marcados e Gols).

* Decisão de Implementação: Cumprindo as competências do projeto, cada time é criado e alocado dinamicamente na memória via malloc.

* Cálculos: Para garantir o correto encapsulamento dos dados, os Pontos Ganhos (PG) e o Saldo de Gols (S) não são armazenados em variáveis; eles são calculados dinamicamente por funções sempre que solicitados (obterPontosGanhos e obterSaldoGols).

### TAD BDTimes
* bd_time.h e bd_time.c: Controla a coleção dos 10 clubes participantes.

* Estrutura: Armazena os times em um vetor fixo de 10 ponteiros (Time *times[10]), onde o ID de cada time mapeia diretamente o seu índice de armazenamento.

* Funcionalidades: 
  * carregaTimes: Abre o arquivo CSV, ignora a linha de cabeçalho e popula o banco de dados.

  * consultarTime: Realiza a busca por prefixo utilizando strncmp.

  * imprimirTabelaClassificacao: Lista a classificação atualizada estruturada por IDs.


### Partida
### TAD Partida
* partida.h e partida.c: Modela um único confronto do campeonato, registrando o ID do jogo, os IDs das equipes (mandante/visitante) e os gols de cada lado.

* Decisão de Implementação: Como as partidas são armazenadas em um vetor puramente estático, a função criaPartida gera o registro sem alocações dinâmicas individuais.

### TAD BDPartidas
* bd_partida.h e bd_partida.c: Gerencia o histórico de jogos carregados.

* Estrutura: Baseado na restrição do enunciado de usar um vetor estático de registros para previsibilidade de memória, utiliza um array de structs dimensionado estaticamente com um teto seguro de 200 posições para suportar quaisquer cenários.

* processarCampeonato: Função que varre o histórico de partidas salvas em memória, avalia as regras de vitória/empate/derrota e distribui de forma acumulada os gols e resultados diretamente nas instâncias correspondentes do BDTimes.

* Funcionalidade: consultarPartidas realiza a listagem cruzada de placares filtrando por prefixos em modo mandante, visitante ou ambos.
---

## Como Compilar e Executar

Caso não tenha o compilador GCC, atualize os pacotes de sua distribuição

```bash
 sudo apt update
```

Instale o pacote
```bash
sudo apt install build-essential
```

Para compilar o projeto completo gerando o executável automatizado

```bash
make
```

Obs: o arquivo compilado será gerado na subpasta /build


## Decisões de Implementação Importantes

* Prevenção de Memory Leaks: O gerenciador de times implementa desalocação completa através do ```liberarBDTimes```, aumentando a segurança do sistema ao garantir que cada ponteiro criado dinamicamente por malloc seja liberado individualmente via ```free``` antes de limpar a estrutura pai.

* Consumo Previsível: O banco de partidas abdica de ponteiros duplos e alocação dinâmica, resolvendo a leitura de diferentes volumes de arquivos (0, 45 ou 100 linhas) puramente pelo controle do contador interno qtd sobre o vetor estático.

* Tratamento de Strings: Strings vindas do arquivo CSV passam por limpeza via strcspn para expurgar caracteres ocultos de quebra de linha (\n) capturados pelo fgets antes de passarem pela tokenização do strtok.

---

## Criadores

* Artur Pedro Carvalho Silva
* André Ulhôa Borges