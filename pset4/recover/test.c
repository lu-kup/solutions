#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int number)
{

    int tmp_number = number;
    int digits = 0;
    char *name = malloc(8);

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
        sprintf(name, "%i.jpg", number);
    }

    if (digits == 2)
    {
        sprintf(name, "0%i.jpg", number);
    }

    if (digits == 1)
    {
        sprintf(name, "00%i.jpg", number);
    }

    return name;


}