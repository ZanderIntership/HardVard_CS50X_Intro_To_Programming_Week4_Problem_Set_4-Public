#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define block size
#define BLOCK_SIZE 512

// Define a byte type
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open memory card file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create variables
    BYTE buffer[BLOCK_SIZE];
    FILE *img = NULL;
    char filename[8];
    int file_count = 0;
    int found_jpeg = 0;


    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {

            if (found_jpeg)
            {
                fclose(img);
            }
            else
            {
                found_jpeg = 1;
            }


            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create output file.\n");
                fclose(file);
                return 1;
            }

            file_count++;
        }


        if (found_jpeg)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }


    if (img != NULL)
    {
        fclose(img);
    }

    fclose(file);
    return 0;
}
