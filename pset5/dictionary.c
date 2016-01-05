/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// arbitary large number to prefer speed over memory size
#define HASH_SIZE 1000000

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
} node;

//idea from https://en.wikipedia.org/wiki/Hash_function
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0;word[i] != '\0';i++)
    {
       n = isalpha(word[i]) ? (word[i] - 'a' + 1) : 27;
       
       hash = ((hash << 3) + n) % HASH_SIZE;        
    }
    return hash;
}

node* hashTable[HASH_SIZE] = {NULL};
int dictionarySize = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //store a lower cased version of the given word
    char temp [LENGTH +1];
    int len = strlen(word);
    for(int i =0; i < len; i++)
        temp[i] = tolower(word[i]);
    temp[len] = '\0';
    
    //get location in the hash table
    int index = hash(temp);
    
    if (hashTable[index] == NULL)
        return false;
        
    node* cursor = hashTable[index];
    
    //if hashtable is valid at index, iterate through linked list to compare
    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
            return true;

        cursor = cursor->next;    
    }   
    
    return false; 
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    
    char word[LENGTH+1];
    
    // scan through the file, loading each item into
    // the hashtable at calculated index
    while(fscanf(file, "%s\n", word) != EOF) 
    {
        dictionarySize++;
        node* newWord = malloc(sizeof(node));
        
        strcpy(newWord->word,word);
        
        int index = hash(word);
        
        // if empty, append
        if (hashTable[index] == NULL)
        {
            hashTable[index] = newWord;
            newWord->next = NULL;
        }
        //if not empty, insert
        else
        {
            newWord->next = hashTable[index];
            hashTable[index] = newWord;
        }
        
    }
    fclose(file);
    
    return true;   
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int index = 0;
    
    while (index < HASH_SIZE)
    {
        //if table is empty at index, move to next next index
        if (hashTable[index] == NULL)
            index++;
            
        //go through all nodes at index and free them.
        else
        {
            while(hashTable[index] != NULL)
            {
                node* cursor = hashTable[index];
                hashTable[index] = cursor->next;
                free(cursor);
            }
            index++;
        }
    }
    return true;
}
