#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover input.raw\n");
        return 1;
    }

    // Open memory card file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", argv[1]);
        return 2;
    }

    // Set output file to a NULL
    FILE *output = NULL;

    // Create a buffer
    BYTE buffer[512];

    // String to hold a filename
    char filename[8] = {0};

    // Value to count jpeg found files
    int counter = 0;

    // Value of one block size
    int block_size = 1;

    // Reading input file
    while (fread(buffer, 512 * sizeof(BYTE), block_size, input) == block_size)
    {
        // Check if first 4 bytes of image are the same as jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close outpout file if jpg was found before
            // and start writing to a new file
            if (output != NULL)
            {
                fclose(output);
            }

            // Creating a new jpeg filename which starts form 000.jpeg, 001.jpg ... etc.
            sprintf(filename, "%03d.jpg", counter++);

            output = fopen(filename, "w");
        }

        // Writing 512 bytes to a new output file
        // and keep writing if new jpeg is not found
        if (output != NULL)
        {
            fwrite(buffer, 512 * sizeof(BYTE), block_size, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }

    fclose(input);
    return 0;
}