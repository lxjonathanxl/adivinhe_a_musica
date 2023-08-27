#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "arquivowav.h"

#define LOWER 1024
#define UPPER 65536

#define QUANT_SONGS 10

typedef struct
{
  WAVHEADER wav_header_read;
  int16_t *samples;
  size_t total;
}song;

song musicas[QUANT_SONGS];

BYTE *temp = NULL;

int create_chosen_song (int musicas_chave);

int calculate_points (int musicas_chave);

int look_for_wav_files(void);

int main (void)
{
    int num_songs, musicas_chave, player1, player2;
    char nome1[20];
    char nome2[20];

    printf("Jogador 1: ");
    scanf(" %[^\n]", nome1);


    printf("Jogador 2: ");
    scanf(" %[^\n]", nome2);

    printf("\n");



    player1 = 0; player2 = 0;
    char name_song[30]; char name_artist[30];
    num_songs = look_for_wav_files();

    for (int i = 0; i < 3; i++)
    {
        //randomizaer
        srand(time(0));
        musicas_chave = (rand() % num_songs);

        //create file to listen
        create_chosen_song(musicas_chave);
        printf("Abra o arquivo musica e tente adivinhar o nome da musica e o nome do artista\n");

        //calcualte points
        player1 += calculate_points (musicas_chave);
        player2 += calculate_points (musicas_chave);
    }

    if (player1 > player2)
    {
        printf("%s venceu!!!\n", nome1);
    }
    else if (player2 > player1)
    {
        printf("%s venceu!!!\n", nome2);
    }
    else
    {
        printf("empate!!!\n");
    }




}


int look_for_wav_files(void)
{
    char name_song_file[8];
    int n_song = 0;
    while (n_song < QUANT_SONGS)
    {
        sprintf(name_song_file, "%02i.wav", n_song);
        FILE *input = fopen(name_song_file, "rb");
        if (input == NULL)
        {
            free(input);
            return -1;
        }
        // Read header
        fread(&musicas[n_song].wav_header_read, sizeof(WAVHEADER), 1, input);

        // Read blocks
        size_t increase = LOWER;
        size_t allocated = increase;
        musicas[n_song].samples = malloc(allocated * sizeof(int16_t));

        musicas[n_song].total = 0;

        while (!feof(input) && !ferror(input))
        {
            int16_t n_sample;
            fread(&n_sample, sizeof(int16_t), 1, input);
            musicas[n_song].samples[musicas[n_song].total] = n_sample;
            musicas[n_song].total++;

            if (musicas[n_song].total >= allocated)
            {
                if (increase >= UPPER)
                {
                    increase = UPPER;
                }

                allocated += increase;

                musicas[n_song].samples = realloc(musicas[n_song].samples, allocated * sizeof(int16_t));

                increase *= 2;
            }
        }

        if (ferror(input))
        {
            printf("Error reading from file!\n");
            return -1;
        }

        musicas[n_song].total = musicas[n_song].total - 1;
        musicas[n_song].samples = realloc(musicas[n_song].samples, musicas[n_song].total * sizeof(int16_t));

        fclose(input);
        n_song++;
    }
    return n_song;
}

int create_chosen_song(int musicas_chave)
{
    FILE* output = fopen("musica.wav", "wb");
    if (output == NULL)
    {
        printf("could not open output file\n");
        return -1;
    }

    fwrite(&musicas[musicas_chave].wav_header_read, sizeof(WAVHEADER), 1, output);

    fwrite(musicas[musicas_chave].samples, sizeof(int16_t), musicas[musicas_chave].total, output);

    fclose(output);

    return 0;
}

int calculate_points (int musicas_chave)
{
    char name_song[30]; char name_artist[30];
    int points = 0;
    //guess song
    printf("\nnome da musica: ");
    scanf(" %[^\n]", name_song);

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    // guess artist
    printf("\nnome do artista: ");
    scanf(" %[^\n]", name_artist);
    for (int i = 0; i < 10; i++)
    {
        printf("\n");
    }

    if (strcasecmp(name_song, musicas[musicas_chave].wav_header_read.nomeMusica) == 0)
    {
        points++;
    }

    if (strcasecmp(name_artist, musicas[musicas_chave].wav_header_read.nomeArtista) == 0)
    {
        points++;
    }

    return points;

}