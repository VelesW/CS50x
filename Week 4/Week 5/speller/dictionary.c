// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int wordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashNum = hash(word);

    // Create cursor
    node *cursor = table[hashNum];

    // Check
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *DICT = fopen(dictionary, "r");

    if (DICT == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(DICT, "%s", word) != EOF)
    {
        // Creating a new node for each word
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }
        // Copied word into tmp
        strcpy(tmp->word, word);

        // Using hash fun
        int hashNum = hash(word);

        // Check if the head is pointing to NULL
        if (table[hashNum] == NULL)
        {
            // Point tmp to NULL
            tmp->next = NULL;
        }
        else
        {
            // Point tmp to the first element of the linked list
            tmp->next = table[hashNum];
        }
        // Point the header to tmp
        table[hashNum] = tmp;

        wordCounter++;
    }

    // Closing the file
    fclose(DICT);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCounter;
}

void freenode(node *n)
{
    if (n->next != NULL)
    {
        freenode(n->next);
    }
    free(n);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freenode(table[i]);
        }
    }
    return true;
}