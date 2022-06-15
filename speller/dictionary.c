// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
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

// Keep track of number of words in dictionary
int count = 0;

// Choose number of buckets in hash table
const unsigned int N = (LENGTH+1) * 'z';

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Hash words to obtain a hash value
    int index = hash(word);

    // Acces linked list at that index in the hash table
    node *cursor = table[index];

    // Traverse linked list looking for that words using strcasecmp
    while (cursor != NULL)
    {

        if (strcasecmp(word, cursor->word) == 0)
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
	int sum = 0;
	for (int i = 0; i < strlen(word); i++)
	{
		sum += tolower(word[i]);
    }
	return (sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //Load dictionary file
    FILE *file = fopen(dictionary, "r");
    if(file == NULL){
        return false;
    }
    char placeholderword[LENGTH + 1];
    int hashIndex;

    while(fscanf(file, "%s", placeholderword) != EOF)
    {

            count++;

            // Create a new node for each word
            node *n = malloc(sizeof(node));
            if(n == NULL){
                return false;
                }
            n->next = NULL;

            // copy word into node
            strcpy(n->word, placeholderword);

            // Hash word to create a hash value
             hashIndex = hash(n->word);

            // Insert node into hash table at that value
            if (table[hashIndex] == NULL)
            {
                table[hashIndex] = n;
                n = NULL;

            }
            else if (table[hashIndex] != NULL)
            {
                n->next = table[hashIndex];
                table[hashIndex] = n;
                n = NULL;
            }
    }
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    // Create pointers tmp and cursor
    node *cursor = NULL;
    node *tmp = NULL;

    for(int i = 0; i < N; i++){

        cursor = tmp = table[i];
        while(cursor != NULL){
            // Move cursor to next node of linked list
            cursor = cursor->next;

            // Free current node
            free(tmp);

            // Set tmp to next node
            tmp = cursor;
        }
    }

    if(cursor != NULL){
        return false;
    }
    return true;
}
