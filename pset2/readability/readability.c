#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string t = get_string("Text: ");
    int l = count_letters(t);
    int w = count_words(t);
    int s = count_sentences(t);
    //printf("%i letter(s)\n", l);
    //printf("%i word(s)\n", w);
    //printf("%i sentence(s)\n", s);

    float W = (float) w / 100;
    //printf("%f\n", W);
    float L = (float) l / W;
    //printf("%f\n", L);
    float S = (float) s / W;
    //printf("%f\n", S);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //printf("%f\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = (int) round(index);
        printf("Grade %i\n", grade);
    }
}


int count_letters(string text)
{
    int length = strlen(text);
    int letters = 0;
    for (int i = 0; i < length; i++)
    {
        int ascii = (int) text[i];
        if ((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int spaces = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        //int comparison = strcmp(text[i], " ");
        if (text[i] == ' ')
        {
            spaces++;
        }
    }
    int words = spaces + 1;
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
    }
    return sentences;
}