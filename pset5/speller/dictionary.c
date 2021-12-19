// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

bool search(node *list, const char *word);
int copied = 0;

// Number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //printf("1\n");
    int clet = hash(word);
    node *cursor = table[clet];
    //printf("Check success\n");
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //printf("3\n");
    char letter = word[0];
    int cletter = 0;

    if ((letter > 64) && (letter < 91))
    {
        cletter = (int) letter - 64;
    }
    else if ((letter > 95) && (letter < 123))
    {
        cletter = (int) letter - 96;
    }
    else
    {
        return 1;
    }

    //printf("Hash success\n");
    return cletter;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //printf("4\n");
    int index = 0;
    char buffer[LENGTH];

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    while (fscanf(dict, "%s", buffer) != EOF)
    {
        //fscanf(dict, "%s", buffer);
        //printf("%s\n", buffer);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        //copied++;
        //printf("Load problem\n");
        index = hash(buffer);
        n->next = table[index];
        table[index] = n;
    }

    fclose(dict);
    //printf("Load success\n");
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //printf("5\n");

    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }

        free(cursor);
    }


    return counter;

    //printf("Count success\n");
    //return copied;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //printf("6\n");
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;

            if (tmp == NULL)
            {
                return false;
            }

            cursor = cursor->next;

            free(tmp);
        }
    }

    //printf("Unload success\n");
    return true;
}
