# Trabalho 1 - Campeonato de Futebol (Parte I)

Este projeto consiste na implementação de um sistema em linguagem C para gerenciamento e consulta de dados de um campeonato de futebol. O sistema é alimentado por arquivos persistidos em formato CSV (times e partidas), processa os resultados em memória e disponibiliza consultas detalhadas e tabelas de classificação para o usuário.

O projeto foi desenvolvido com foco em modularização, uso inteligente de memória (combinando alocação dinâmica e estática) e integridade de dados por meio de encapsulamento em Tipos Abstratos de Dados (TADs).

## 🎯 Regras do Campeonato

* Composição: O campeonato possui exatamente 10 clubes fixos (indexados de 0 a 9).
* Formato: Disputado em turno único de pontos corridos (todos contra todos, sem repetição).
* Pontuação: Vitória confere 3 pontos, empate confere 1 ponto e derrota 0 pontos.
* Critérios de Classificação: Vitórias (V), Empates (E), Derrotas (D), Gols Marcados (GM), Gols Sofridos (GS), Saldo de Gols (S = GM - GS) e Pontos Ganhos (PG = 3V + E).

---

## 📁 Estrutura do Projeto

Para garantir a organização exigida, o código foi dividido estritamente em módulos lógicos dentro do diretório src:

.
├── data/
│   ├── times.csv
│   ├── partidas_vazio.csv
│   ├── partidas_parcial.csv
│   └── partidas_completo.csv
├── src/
│   ├── main.c
│   └── time/
│       ├── time.c
│       ├── time.h
│       ├── bd_time.c
│       ├── bd_time.h
│       ├── partida.c
│       ├── partida.h
│       ├── bd_partida.c
│       └── bd_partida.h
└── Makefile

---

## ⚙️ Organização dos Módulos e TADs

### 1. Submódulo Time (Entidade Individual)
* time.h / time.c: Define a estrutura elementar Time que encapsula o ID, nome e as variáveis acumuladoras de desempenho (V, E, D, GM, GS).
* Decisão de Implementação: Cumprindo as competências do projeto, cada time é criado e alocado dinamicamente na memória via malloc.
* Cálculos Sob Demanda: Para garantir a integridade absoluta dos dados, os Pontos Ganhos (PG) e o Saldo de Gols (S) não são armazenados em variáveis; eles são calculados dinamicamente por funções sempre que solicitados (obterPontosGanhos e obterSaldoGols).

### 2. Submódulo BDTimes (Gerenciador de Times)
* bd_time.h / bd_time.c: Controla a coleção dos 10 clubes participantes.
* Estrutura: Armazena os times em um vetor fixo de 10 ponteiros (Time *times[10]), onde o ID de cada time mapeia diretamente o seu índice de armazenamento, tornando buscas por ID instantâneas.
* Funcionalidades: 
  * carregaTimes: Abre o arquivo CSV, ignora a linha de cabeçalho e popula o banco de dados.
  * consultarTime: Realiza a busca por prefixo utilizando strncmp.
  * imprimirTabelaClassificacao: Lista a classificação atualizada estruturada por IDs.

### 3. Submódulo Partida (Entidade Individual)
* partida.h / partida.c: Modela um único confronto do campeonato, registrando o ID do jogo, os IDs das equipes (mandante/visitante) e os gols de cada lado.
* Decisão de Implementação: Como as partidas são armazenadas em um vetor puramente estático, a função criaPartida gera e retorna a struct por valor (cópia), criando o registro sem alocações dinâmicas individuais e simplificando o ciclo de vida dos dados.

### 4. Submódulo BDPartidas (Gerenciador e Motor de Jogos)
* bd_partida.h / bd_partida.c: Gerencia o histórico de jogos carregados.
* Estrutura: Baseado na restrição do enunciado de usar um vetor estático de registros para previsibilidade de memória, utiliza um array de structs (Partida partidas[MAX_PARTIDAS]) dimensionado estaticamente via #define com um teto seguro de 200 posições para suportar quaisquer cenários de teste de estresse.
* O Motor do Campeonato (processarCampeonato): Função essencial que varre o histórico de partidas salvas em memória, avalia as regras de vitória/empate/derrota e distribui de forma acumulada os gols e resultados diretamente nas instâncias correspondentes do BDTimes.
* Funcionalidade: consultarPartidas realiza a listagem cruzada de placares filtrando por prefixos em modo mandante, visitante ou ambos.

---

## 🛠️ Interface e Formatação Visual

Toda a exibição de dados em formato de tabelas (Tabela de Classificação e Consultas de Times) foi padronizada utilizando caracteres de tabulação pura (\t) combinados com quebras de linha (\n), removendo máscaras numéricas rígidas de formatação. O uso de tabuladores duplos (\t\t) após os nomes garante o perfeito alinhamento vertical das colunas de estatísticas no terminal Linux, independentemente do comprimento do nome do clube.

---

## 🚀 Como Compilar e Executar

O projeto está totalmente preparado para o ambiente Linux Ubuntu 22.04 utilizando o compilador GCC 11.

### Automação com o Makefile

Para compilar o projeto completo gerando o executável automatizado:
make

Para rodar a aplicação após a compilação:
make run

Para limpar o executável e arquivos binários residuais antes de reestruturar o envio:
make clean

### Compilação Manual Alternativa
Caso prefira compilar manualmente via terminal incluindo a flag de diretório de inclusão (-I):
gcc -Isrc/time src/main.c src/time/time.c src/time/bd_time.c src/time/partida.c src/time/bd_partida.c -o programa

---

## 📝 Decisões de Implementação Importantes

* Prevenção de Memory Leaks: O gerenciador de times implementa uma desalocação profunda (liberarBDTimes), aumentando a segurança do sistema ao garantir que cada ponteiro criado dinamicamente por malloc seja liberado individualmente via free antes de limpar a estrutura pai.
* Consumo Previsível: O banco de partidas abdica de ponteiros duplos e alocação dinâmica, resolvendo a leitura de diferentes volumes de arquivos (0, 45 ou 100 linhas) puramente pelo controle do contador interno qtd sobre o vetor estático.
* Tratamento de Strings: Strings vindas do arquivo CSV passam por limpeza via strcspn para expurgar caracteres ocultos de quebra de linha (\n) capturados pelo fgets antes de passarem pela tokenização do strtok.

---

## 👥 Autores

* Artur Carvalho
* Disciplina: Estruturas de Dados
* Instituição: Instituto Federal do Espírito Santo - IFES Campus Serra
* Semestre: 2026/1