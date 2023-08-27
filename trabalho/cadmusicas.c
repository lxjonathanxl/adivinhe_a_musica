
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivowav.h"

#define  false 0
#define  true 1



int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("usage: ./cadmusicas input output\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("could not open file\n");
        return 1;
    }
    // Read header
    // TODO #3
    WAVHEADER wav_header_read;

    fread(&wav_header_read, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(wav_header_read) == false)
    {
        printf("file must be of type WAVE\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("could not open output file\n");
        return 1;
    }

    //giving the name of the song and the artist name
    char name_song[30];
    char name_artist[30];

    printf("\nnome da musica: ");
    scanf(" %[^\n]", name_song); // Add a space before %[^\n] to consume leading whitespace

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("\nnome do artista: ");
    scanf(" %[^\n]", name_artist);

    printf("\n");

    int n = strlen(name_song);
    for (int i = 0; i < n; i++)
    {
        wav_header_read.nomeMusica[i] = (int) name_song[i];
    }
    wav_header_read.nomeMusica[n] = '\0';
    n = strlen(name_artist);
    for (int i = 0; i < n; i++)
    {
       wav_header_read.nomeArtista[i] = (int) name_artist[i];
    }
    wav_header_read.nomeArtista[n] = '\0';
    // Write header to file
    fwrite(&wav_header_read, sizeof(WAVHEADER), 1, output);


    // Use get_block_size to calculate size of block
    int block_size = get_block_size(wav_header_read);

    // Write audio to file
    BYTE place_holder_for_block[block_size];

    while (!feof(input) && !ferror(input))
    {
        fread(place_holder_for_block, block_size, 1, input);

        fwrite(place_holder_for_block, block_size, 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;


}

int check_format(WAVHEADER header)
{
    // TODO #4
    int validator = 0;
    char word_WAVE[4] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] == word_WAVE[i])
        {
            validator++;
        }
    }

    if (validator == 4)
    {
        return true;
    }
    else
    {
        return false;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}