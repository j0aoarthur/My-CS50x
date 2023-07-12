#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // Open input file (forensic image)
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Set outfile pointer to NULL
    FILE *outptr = NULL;

    // Create an array of 512 elements to store 512 bytes from the memory card
    BYTE buffer[512];

    // Count amount of jpeg files found
    int jpeg = 0;

    // String to hold a filename
    char filename[8] = {0};

    // Read memory card untill the end of file
    while (fread(buffer, sizeof(BYTE) * 512, 1, inptr) == 1)
    {
        // Check if jpeg is found
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // Close outptr if jpeg was found before and written into ###.jpg
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03d.jpg", jpeg++);

            // Open a new outptr for writing a new found jpeg
            outptr = fopen(filename, "w");
        }

        // Keep writing to jpeg file if new jpeg is not found
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outptr);
        }
    }

    // Close last opened outptr
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    // Close input file (forensic image)
    fclose(inptr);

    return 0;
}