#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int length = strlen(key);

        //Check for right length
        if (length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        //Check for special characters
        for (int i = 0; i < length; i++)
        {
            if (!(((key[i] >= 'a') && (key[i] <= 'z')) || ((key[i] >= 'A') && (key[i] <= 'Z'))))
            {
                printf("Invalid input\n");
                return 1;
            }
        }

        //Check for repetition
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if ((i != j) && (key[i] == key[j]))
                {
                    printf("Invalid input\n");
                    return 1;
                }
            }
        }

        //Determine the difference
        int dif[length];
        for (int i = 0; i < length; i++)
        {
            if ((key[i] >= 'a') && (key[i] <= 'z'))
            {
                dif[i] = key[i] - (97 + i);
            }
            else if ((key[i] >= 'A') && (key[i] <= 'Z'))
            {
                dif[i] = key[i] - (65 + i);
            }
        }

        for (int i = 0; i < length; i++)
        {
            printf("%i\n", dif[i]);
        }


        //Plain text input
        string plain = get_string("plaintext: ");
        int lenplain = strlen(plain);

        //Convert to cipher
        string converted = plain;
        for (int i = 0; i < lenplain; i++)
        {
            if ((plain[i] >= 'a') && (plain[i] <= 'z'))
            {
                converted[i] = plain[i] + dif[(int) plain[i] - 97];
            }
            if ((plain[i] >= 'A') && (plain[i] <= 'Z'))
            {
                converted[i] = plain[i] + dif[(int) plain[i] - 65];
            }
        }
        printf("ciphertext: %s\n", converted);
        return 0;


    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}