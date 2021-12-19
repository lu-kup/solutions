#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string letter = get_string("letter: ");
                if ((letter[0] > 'a') && (letter[0] < 'z'))
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
                
                int newletter = letter[0] - 2;
                printf("%c\n", newletter);
}