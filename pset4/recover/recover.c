#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

char *filename(int number);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    FILE *output;

    if (raw == NULL)
    {
        printf("File could not be opened\n");
        return 1;
    }

    typedef uint8_t BYTE;
    int BLOCK_SIZE = 512;
    uint8_t buffer[BLOCK_SIZE];
    int jpg_number = 0;
    int digit = 0;
    char *name = malloc(8);

    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, raw) != 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            if (jpg_number != 0)
            {
                fclose(output);
            }

            jpg_number++;

            name = filename(jpg_number);

            output = fopen(name, "w");
        }

        if (jpg_number != 0)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    fclose(raw);
    fclose(output);
    free(name);
}

char *filename(int number)
{
    number = number - 1;
    int tmp_number = number;
    int digits = 0;
    char *generated_name = malloc(8);

    for (int i = 0; i < 3; i++)
    {
        if (tmp_number != 0)
        {
            tmp_number = tmp_number / 10;
            digits++;
        }
    }

    if (digits == 3)
    {
        sprintf(generated_name, "%i.jpg", number);
    }

    if (digits == 2)
    {
        sprintf(generated_name, "0%i.jpg", number);
    }

    if (digits == 1)
    {
        sprintf(generated_name, "00%i.jpg", number);
    }

    if (digits == 0)
    {
        sprintf(generated_name, "000.jpg");
    }

    return generated_name;

    free(generated_name);
}