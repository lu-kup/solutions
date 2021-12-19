#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int height_left = height;
    int spaces = height - 1;
    int hashes = 1;
    string wall;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }


}