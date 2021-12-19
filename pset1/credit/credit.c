#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Number: ");
    int length = 0;

    //Calculate length
    long n = number;
    while (n > 0)
    {
        n /= 10;
        length += 1;
    }
//printf("%i\n", length);


    //Calculate sum of specified digits
    int sum = 0;
    int digit;
    int ddigit;
    int d2;
    long m = number;
    int i;
    for (i = 0; i < length ; i++)
    {
        if (i % 2 == 1)
        {
            digit = m % 10;
            ddigit = digit * 2;
            if (ddigit > 9)
            {
                d2 = ddigit % 10;
                sum = sum + 1 + d2;
            }
            else
            {
                sum = sum + ddigit;
            }
        }
        m /= 10;
    }

    long v = number;
    int j;
    for (j = 0; j < length ; j++)
    {
        if (j % 2 == 0)
        {
            digit = v % 10;
            sum = sum + digit;
        }
        v /= 10;
    }


    bool checksum = (sum % 10 == 0);
//printf("%d\n", checksum);

//Last two digits
    long value = 1;
    for (i = 0; i < (length - 2); i++)
    {
        value *= 10;
    }
    int firsttwo = number / value;
//printf("%i\n", firsttwo);

//Print results
    if (length == 15 && (firsttwo == 34 || firsttwo == 37) && checksum)
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (firsttwo == 51 || firsttwo == 52 || firsttwo == 53 || firsttwo == 54
                              || firsttwo == 55) && checksum)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 16 || length == 13) && firsttwo/10 == 4 && checksum)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}