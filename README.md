## cadmusicas e guesssong

### cadmusicas: Processamento de Arquivos de Áudio

Este trecho de código trata do processamento de arquivos de áudio no formato WAV. Ele executa as seguintes etapas:

1. **Lê os dados de áudio de um arquivo de entrada.**
2. **Modifica o cabeçalho** para incluir informações sobre a música e o artista.
3. **Escreve o áudio modificado** juntamente com o novo cabeçalho em um arquivo de saída.

#### Arquivos de Cabeçalho Necessários

- `stdint.h`: Fornece tipos inteiros com larguras especificadas.
- `stdio.h`: Fornece funções padrão de entrada/saída.
- `stdlib.h`: Fornece funções de alocação de memória e de saída.
- `string.h`: Fornece funções de manipulação de strings.
- `"arquivowav.h"`: Inclui um arquivo de cabeçalho definido pelo usuário chamado `"arquivowav.h"`.

#### Definições e Constantes

- As constantes `false` e `true` são definidas com os valores 0 e 1, respectivamente.

#### Declarações de Funções

- São declarados os protótipos das funções `check_format()` e `get_block_size()`.

#### Função `main()`

1. **Verifica os argumentos da linha de comando** para garantir que sejam exatamente dois.
2. **Abre um arquivo de entrada** para leitura.
3. **Lê o cabeçalho WAV** do arquivo de entrada.
4. **Chama a função `check_format()`** para verificar se o arquivo está no formato WAV.
5. **Abre um arquivo de saída** para escrita.
6. **Obtém do usuário os nomes da música e do artista.**
7. **Modifica o cabeçalho WAV** com as informações fornecidas.
8. **Escreve o novo cabeçalho** no arquivo de saída.
9. **Calcula o tamanho do bloco** usando a função `get_block_size()`.

### guesssong.c: Jogo de Adivinhação de Músicas

Este trecho de código apresenta um jogo onde os jogadores ouvem trechos de músicas e tentam adivinhar as informações da música e do artista. Os pontos são concedidos por respostas corretas.

#### Arquivos de Cabeçalho Necessários

Os arquivos de cabeçalho necessários são incluídos da mesma forma que no primeiro trecho de código.

#### Constantes e Definições

- São definidas as constantes `LOWER` e `UPPER`, além da constante `QUANT_SONGS`, que indica a quantidade de músicas no jogo.

#### Estruturas de Dados

- É criada uma estrutura chamada `song` que armazena informações sobre uma música, incluindo o cabeçalho WAV e amostras de áudio.

#### Declarações de Funções

- São declarados os protótipos das funções `create_chosen_song()`, `calculate_points()`, e `look_for_wav_files()`.

#### Função `main()`

1. **Solicita os nomes dos jogadores.**
2. **Executa um loop** onde três músicas são selecionadas aleatoriamente.
3. **Cria um arquivo de áudio** para a música escolhida.
4. **Os jogadores tentam adivinhar** os nomes das músicas e dos artistas.
5. **Os pontos são calculados** com base nas respostas dos jogadores.
6. **O vencedor é determinado** e exibido.

#### Função `look_for_wav_files()`

- Procura por arquivos WAV no diretório e carrega as informações das músicas na estrutura de dados `musicas`.

#### Funções `create_chosen_song()` e `calculate_points()`

- Essas funções são responsáveis por criar o arquivo de áudio selecionado e calcular os pontos, respectivamente.
