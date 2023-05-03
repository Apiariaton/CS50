// Implements a dictionary's functionality
#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table - what is a hash table?
//Hash table is an array of linked lists.
//Since we are dealing with a hash table where the length of the word is 45,

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table - each index will represent a unique sequence of three letters - 26 to the power of three
const unsigned int N = 17576; //Since 26 letters in total, will have 17576 entries (26 ** 3 to minimise average retrieval time for each word)

// Hash table -  this will contain a number of unique identifiable keys by which the words can be obtained
node *table[N];
/*
bool check_match (unsigned int hash, node *depth[hash], const char *word) {
int match = 1;
printf("This is the hashed value %i",hash);
printf("This is the value of the word %s,",word);
for (int i = 0; i < strlen(word + 1); i++)
{
if ((depth[hash])->word[i] != word[i])
{
match = 0;
i += strlen(word);
}
}
if (match == 1)
{
return true;
}
else if (depth[hash]->next != NULL)
{
check_match(hash,&depth[hash]->next, word);
}
else
{
return false;
}
return false;
}
*/


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
// TODO
unsigned int *hashed_word = malloc(sizeof(unsigned int));
char *lowercased_word = (char *)(malloc(strlen(word) + 1));

for (int i = 0; i < (strlen(word) + 1);i++)
{
lowercased_word[i] = tolower(word[i]);
}

*(hashed_word) = hash(lowercased_word);

int match = 0;
int rt = 0;
while (match == 0)
{

for (int i = 0; i < strlen(lowercased_word) + 1;i++)
{

    if (table[*(hashed_word)]->word[i] != lowercased_word[i])
    {
        if (table[*(hashed_word)]->next != NULL)
        {
        table[*(hashed_word)] = table[*(hashed_word)]->next;
        rt = 0;
        i += strlen(lowercased_word);
        }

        else
        {
        free(hashed_word);
        free(lowercased_word);
        return false;
        }

    }
    else
    {

    }

}

if (rt == 1)
{
free(hashed_word);
free(lowercased_word);
return true;
}
rt = 1;
}
return true;
}




// Hashes word to a number - converts it into a unique identifiable key, so that it can be located in table

unsigned int hash(const char *word)
{
    // TODO: Improve this hash function 17576
    /*
    Value 1 = 26 * 1; yuppie 10971 yurlov 25 21 16 25 21 18
    Value 2 = 26 * 25;
    Value 3 = 26 * 26 * 25;
    */
   if ((isalpha(word[0]) != 0) && (isalpha(word[1]) != 0) && (isalpha(word[2])!= 0))
   {
   return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[1]) - 'A') * 25) + ((toupper(word[2]) - 'A')));
   }
   else if ((isalpha(word[0])!= 0) && (isalpha(word[1])!= 0))
   {
   return (unsigned int)(((toupper(word[0]) - 'A')* 26 * 25) + ((toupper(word[1]) - 'A') * 25));
   }
   else if (isalpha(word[0]) != 0)
   {
   return (unsigned int)((toupper(word[0]) - 'A')* 26 * 25);
   }
   else
   {
    printf("Unhashable... ");
    return 17576 * 2;
   }


}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

int counter = 0;

for (int i = 0; i < N; i++)
{
    table[i] = (node *)(malloc(sizeof(node)));
    table[i]->next = NULL;

        if (table[i] != NULL)
        {
        counter++;
        }

        else
        {
        printf("The value of counter is %i",counter);
        return false;
        }

}
printf("The value of counter is %i",counter);


FILE *open_dictionary = fopen(dictionary,"r");
if (open_dictionary == NULL || ferror(open_dictionary))
{
printf("Error opening dictionary");
return false;
}

int index_2 = 0;
char character_of_file; //Denoted by '\n' (10 13) for dictionary file; \\ for word file, '\0' (32) //Getline stores the newline character and then a '\0'
char entry[LENGTH + 1];
int e_index = 0;
unsigned int hashed_entry = 0;
int words_stored = 0;
while (fread(&character_of_file,sizeof(char),1,open_dictionary))
{
    if (isalpha(character_of_file) || character_of_file == '\'')
    {
    entry[e_index++] = character_of_file;
    }
    else
    {
    entry[e_index] = '\0';
    e_index = 0;
    //printf("%s",entry);
    hashed_entry = hash(entry);
    //printf("%ui",hashed_entry);

    while (table[hashed_entry]->next != NULL)
    {
    table[hashed_entry] = table[hashed_entry]->next;
    }
    while (isalpha(entry[e_index]) != 0 || entry[e_index] == '\'')
    {
    table[hashed_entry]->word[e_index] = entry[e_index];
    printf("%c",table[hashed_entry]->word[e_index]);
    if (table[hashed_entry]->word[e_index] != entry[e_index])
    {
    printf("Error happened while copying values from entry to table[hashed_entry]->word[i]");
    return false;
    }
    e_index++;
    }
    table[hashed_entry]->word[e_index] = '\0';
    e_index = 0;

    printf("\n");
    table[hashed_entry]->next = (node *)(malloc(sizeof(node)));
    if (table[hashed_entry]->next == NULL)
    {
    printf("Error happened while allocating memory to table[hashed_entry]->next");
    return false;
    }
    table[hashed_entry]->next->next = NULL;
    words_stored++;
    }

}
for (int i = 0; i < N; i++)
{
printf("%s",table[i]->word);
}
printf("Words stored: %i",words_stored);


fclose(open_dictionary);
return true;
}





// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO - Cumulative total of nodes created - count each time node goes from empty to full and each time memory allocated to node
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
//By unloading memory, this means freeing the memory which was assigned by load.
//Closes the file, clears value of word, uses free for each sub-chain of node recursively (while node != NULL) node = node->next;
//Check for return values which indicate a failure of malloc
bool unload(void)
{
    // TODO
    return true;
}

