# Trabalho 1 - Estruturas de Dados

Este projeto implementa, em C, uma base simples para gerenciamento de um campeonato de futebol a partir de arquivos CSV. A aplicação carrega os times e as partidas para a memória, percorre os dados para teste e libera toda a memória alocada ao final da execução.

## Objetivo da implementação

A proposta atual do projeto é organizar os dados do campeonato em TADs, separando:

- os dados de cada time;
- os dados de cada partida;
- as estruturas que funcionam como "bancos" em memória para armazenar coleções de times e partidas.

Com isso, o programa cria uma base que pode ser expandida para funcionalidades como classificação, estatísticas e consultas sobre o campeonato.

## Estrutura do projeto

```text
.
├── data/
│   ├── times.csv
│   ├── partidas_completo.csv
│   ├── partidas_parcial.csv
│   ├── partidas_vazio.csv
│   ├── bd_partidas.csv
│   └── bd_classificacao.csv
├── src/
│   ├── main.c
│   ├── time/
│   │   ├── time.c
│   │   ├── time.h
│   │   ├── bd_time.c
│   │   └── bd_time.h
│   ├── partida/
│   │   ├── partida.c
│   │   ├── partida.h
│   │   ├── bd_partida.c
│   │   └── bd_partida.h
│   └── utils/
│       ├── loader.c
│       ├── loader.h
│       ├── menu.c
│       └── menu.h
└── Makefile
```

## Organização dos módulos

### `src/time`

Responsável pelo TAD `Time` e pelo banco de times.

#### `time.h` / `time.c`

Define a estrutura `Time`, que armazena:

- `id`
- `nome`
- `vitorias`
- `empates`
- `derrotas`
- `gols_marcados`
- `gols_sofridos`

Também implementa:

- `criaTime(int id, const char *nome)`: cria dinamicamente um time;
- `liberaTime(Time *t)`: libera a memória associada ao time.

#### `bd_time.h` / `bd_time.c`

Define a estrutura `BDTimes`, que mantém um vetor de ponteiros para até 10 times e a quantidade carregada.

Funções principais:

- `criaBDTimes()`: inicializa o banco de times;
- `carregaTimes(const char *path)`: lê o arquivo `times.csv`, ignora o cabeçalho e cria os times em memória;
- `liberaBDTimes(BDTimes *bd)`: libera todos os times e depois o próprio banco.

### `src/partida`

Responsável pelo TAD `Partida` e pelo banco de partidas.

#### `partida.h` / `partida.c`

Define a estrutura `Partida`, com:

- `id`
- `id_time1`
- `id_time2`
- `gols_time1`
- `gols_time2`

Função implementada:

- `criaPartida(int id, int idt1, int idt2, int gt1, int gt2)`: monta e retorna uma partida.

Existe também a assinatura de `calculaEstatisticas(Partida *p)`, indicando uma intenção de expansão para atualização automática das estatísticas dos times.

#### `bd_partida.h` / `bd_partida.c`

Define a estrutura `BDPartidas`, que armazena até 150 partidas em memória e controla a quantidade carregada.

Funções principais:

- `criaBDPartidas()`: cria o banco de partidas;
- `carregaPartidas(const char *path)`: lê um CSV de partidas, ignora o cabeçalho e armazena cada registro;
- `liberarBDPartidas(BDPartidas *bd)`: libera o banco de partidas.

### `src/utils`

Contém arquivos auxiliares para futuras funcionalidades.

- `loader.c` / `loader.h`: possuem a ideia de um carregador genérico de CSV, mas essa parte ainda está incompleta;
- `menu.c` / `menu.h`: reservados para uma interface de menu e visualização da classificação, mas ainda sem implementação funcional.

## Fluxo atual do programa

O arquivo `src/main.c` executa o seguinte fluxo:

1. carrega os times a partir de `data/times.csv`;
2. carrega as partidas a partir de `data/partidas_completo.csv`;
3. verifica se os dados foram carregados corretamente;
4. imprime alguns times e todas as partidas como teste de leitura;
5. libera a memória alocada antes de encerrar o programa.

Ou seja, o foco atual da implementação está na leitura dos arquivos, criação das estruturas em memória e gerenciamento básico de memória.

## Formato dos arquivos de entrada

### `data/times.csv`

Formato:

```csv
ID,Time
0,JAVAlis
1,ESCorpiões
...
```

### `data/partidas_completo.csv`

Formato:

```csv
ID,Time1ID,Time2ID,GolsTime1,GolsTime2
0,5,7,4,1
1,9,1,2,5
...
```

## Como compilar e executar

O projeto usa `gcc` e um `Makefile`.

### Compilar e executar direto

```bash
make
```

Pelo `Makefile` atual, o alvo padrão compila e executa o programa automaticamente.

### Apenas executar após compilar

```bash
make run
```

### Limpar os arquivos gerados

```bash
make clean
```

## Principais decisões da implementação

- uso de TADs para separar responsabilidades;
- alocação dinâmica para os times, permitindo controlar melhor o ciclo de vida dos dados;
- leitura de arquivos CSV com `fgets`, `strtok` e `atoi`;
- separação entre entidades do domínio (`Time` e `Partida`) e estruturas de armazenamento (`BDTimes` e `BDPartidas`).

## Estado atual do projeto

Atualmente, a implementação já cobre:

- carregamento dos times a partir de CSV;
- carregamento das partidas a partir de CSV;
- armazenamento em memória usando estruturas próprias;
- desalocação da memória ao final da execução.

Pontos que ainda aparecem como próximos passos:

- cálculo de classificação e estatísticas a partir das partidas;
- implementação real de `calculaEstatisticas`;
- criação de um menu para interação com o usuário;
- consolidação de um carregador genérico em `utils/loader.c`;
- uso efetivo de arquivos como `bd_classificacao.csv`.

## Observações

- A estrutura `BDTimes` foi dimensionada para até 10 times.
- A estrutura `BDPartidas` foi dimensionada para até 150 partidas.
- O programa atual tem caráter de teste e validação da leitura dos dados.
- Alguns arquivos em `src/utils` já existem como preparação para as próximas etapas, mas ainda não estão finalizados.

## Autores

Preencha esta seção com os nomes dos integrantes do grupo, disciplina, turma e semestre, se isso fizer sentido para a entrega.
