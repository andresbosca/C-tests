#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mp3Tag
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[28];
    char bitRate[1];
    char sampleRate[1];
    int genre;
};

int fileNameLength = 1024;
int mp3TagSize = 128;

int main()
{
    struct mp3Tag *tagStruct = malloc(sizeof(struct mp3Tag));
    char fileName[fileNameLength + 1];
    FILE *mp3File;
    char buffer[mp3TagSize + 1];

    strcpy(fileName, "x.mp3");

    mp3File = fopen(fileName, "rb");
    buffer[mp3TagSize] = '\0'; // just a precaution

    if (mp3File)
    {
        printf("Yeah, %s has been opened \n", fileName);
    }
    else
    {
        printf("***Aborting*** Oops... Something went wrong opening %s \n", fileName);
        return 1;
    }

    // move file pointer to 128 bytes off the end of the file.
    fseek(mp3File, -(mp3TagSize), SEEK_END);
    if (mp3File == NULL)
    {
        printf("Could not seek, Aborting \n");
        return 1;
    }

    printf("Starting to get the data from de file... \n");

    // get the data
    if (fgets(buffer, mp3TagSize, mp3File) != NULL)
    {
        tagStruct = (struct mp3Tag *)buffer;
        printf("\nTag: %3s\n", tagStruct->tag);
        printf("Title: %30s\n", tagStruct->title);
        printf("Artist: %30s\n", tagStruct->artist);
        printf("Album: %30s\n", tagStruct->album);
        printf("Year: %4s\n", tagStruct->year);
        printf("Comment: %30s\n", tagStruct->comment);
        printf("BitRate: %1s\n", tagStruct->bitRate);
        printf("SampleRate: %1s\n", tagStruct->sampleRate);
        printf("Genre: %d\n", tagStruct->genre);

        printf("Successful read of %s \n", fileName);
    }
    else
    {
        printf("Error reading the ID3V1 tag.");
        return 1;
    }

    fclose(mp3File);
    return 0;
}
