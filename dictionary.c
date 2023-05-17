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

//Test to see if works:
/*
printf("Words stored and accessible by check function:");
for (int i = 0; i < 17576 ; i++)
{
printf("Table index %i %s\n",i,table[i]->word);
printf("Words in same linked list:");
node *origin_point = table[i];
while (table[i]->next != NULL)
{
table[i] = table[i]->next;
printf("-> [%i] %s\n",i,table[i]->word);
}
table[i] = origin_point;
printf("\n");
}
return true;
*/
//Test cases: word length: 1,2,3,4,5,6,7,8,9,10 etc
//Words that feature non-alphabetic characters


//unsigned int *hashed_word = (unsigned int *)(malloc(sizeof(unsigned int)));
unsigned int hashed_word;
char *lowercased_word = (char *)(malloc(strlen(word) + 1));

for (int i = 0; i < (strlen(word));i++) // Removed + 1
{
lowercased_word[i] = tolower(word[i]);
}
lowercased_word[(strlen(word))] = '\0';

//*(hashed_word) = hash(lowercased_word);
hashed_word = hash(lowercased_word);

node *starting_position = NULL;
starting_position = *(&table[hashed_word]);
/*
if (isalpha(*(&table[hashed_word]->word[0])) == 0)
{
printf("Value of table[*(hashed_word)]->word[0] %c",table[hashed_word]->word[0]);
printf("There is an error with the initial table[*(hashed_word)] of the node");
}
else
{
printf("No error with table[*(hashed_value)]...");
}
if (isalpha(starting_position->word[0]) == 0)
{
printf("Value of starting_position->word[0] %c",starting_position->word[0]);
printf("There is an error with the initial starting position of the node");
}
*/
int match = 0;
int rt = 0;
while (match == 0)
{
//INT -> 3
// < 3
//0 1 2
//Haven't moved the starting_position to the correct location on the basis of the given word
//What is the issue here - a match gets made for short words w same letters at start as long word
for (int i = 0; i < (strlen(lowercased_word) + 1 /*-1*/); i++)
{

    if (*(&table[hashed_word]->word[i]) != lowercased_word[i])
    {
        if (*(&table[hashed_word]->next) != NULL)
        {
        *(&table[hashed_word]) = *(&table[hashed_word]->next);
        rt = 0;
        i += strlen(lowercased_word);
        }

        else
        {
        *(&table[hashed_word]) = starting_position;
        //free(hashed_word);
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
*(&table[hashed_word]) = starting_position;
//free(hashed_word);
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


   /*
    return 0;
if (word == NULL)
{
printf("Word is a null pointer");
return 0;
}
*/

    // TODO: Improve this hash function 17576
    /*
    Value 1 = 26 * 1; yuppie 10971 yurlov 25 21 16 25 21 18
    Value 2 = 26 * 25;
    Value 3 = 26 * 26 * 25;
    */

   if (strlen(word) < 3)
   {
        if (strlen (word) == 2)
        {
            if ((word[0]) != 0 && isalpha(word[1]) != 0)
            {
            return (unsigned int)(((toupper(word[0]) - 'A')* 26 * 25) + ((toupper(word[1]) - 'A') * 25));
            }
            else if (isalpha(word[0])!= 0 && (!isalpha(word[1])))
            {
            return (unsigned int)((toupper(word[0]) - 'A')* 26 * 25);
            }
            else if ((!isalpha(word[0])) && isalpha(word[1]) != 0)
            {
            return (unsigned int)((toupper(word[1]) - 'A') * 25);
            }
            else
            {
            return (unsigned int) 0;
            }

        }
        else if (strlen(word) == 1)
        {
            if (isalpha(word[0]) != 0)
            {
            return (unsigned int)((toupper(word[0]) - 'A')* 26 * 25);
            }
            else
            {
            return (unsigned int) 0;
            }
        }
        else
        {
            printf("Unhashable... ");
            return 17576 * 2;
        }


   }
   // apostrophe_character_code = 39;
   else
   {
   if (isalpha(word[0]) != 0 && isalpha(word[1]) != 0 && isalpha(word[2]) != 0)
   {
   return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[1]) - 'A') * 25) + ((toupper(word[2]) - 'A')));
   }
   else if (isalpha(word[0]) != 0 && isalpha(word[1]) != 0 && isalpha(word[2]) == 0)
   {
   return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[1]) - 'A') * 25));
   }
    else if (isalpha(word[0]) != 0 && (isalpha(word[1])) == 0 && isalpha(word[2]) == 0)
   {
   return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[1]) - 'A') * 25));
   }
    else if (isalpha(word[0]) != 0 && isalpha(word[1]) == 0 && isalpha(word[2]) != 0)
   {
    return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[2]) - 'A')));
   }
    else if (isalpha(word[0]) == 0 && isalpha(word[1]) == 0 && isalpha(word[2]) != 0)
   {
   return (unsigned int)((toupper(word[2]) - 'A'));
   }
    else if (isalpha(word[0]) == 0 && isalpha(word[1]) != 0 && isalpha(word[2]) == 0)
   {
   return (unsigned int)((toupper(word[1]) - 'A') * 25);
   }
    else if (isalpha(word[0]) == 0 && isalpha(word[1]) != 0 && isalpha(word[2]) == 0)
   {
   return (unsigned int)(((toupper(word[0]) - 'A') * 26 * 25) + ((toupper(word[1]) - 'A') * 25));
   }
    else if (isalpha(word[0]) == 0 && isalpha(word[1]) == 0 && isalpha(word[2]) == 0)
   {
   return (unsigned int)(0);
   }
   else
   {
    return (unsigned int)(0);
   }
   }


}




// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
//The issue with load is that all previous nodes are being overwritten by the value of the final node.


int counter = 0;

for (int i = 0; i < N; i++)
{
    *(&table[i]) = (node *)(malloc(sizeof(node)));
    *(&table[i]->next) = NULL;

        if (&table[i] != NULL)
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


FILE *working_dictionary = fopen("this_is_the_dictionary_I_output.txt","w");
if (working_dictionary == NULL || ferror(working_dictionary))
{
printf("Error opening writing dictionary");
return false;
}


int index_2 = 0;
char character_of_file; //Denoted by '\n' (10 13) for dictionary file; \\ for word file, '\0' (32) //Getline stores the newline character and then a '\0'
char entry[LENGTH + 1];
int e_index = 0;
unsigned int hashed_entry = 0;
int words_stored = 0;
node * starting_point = NULL;
char *dictionary_entry_check = (char *)(malloc(1));

while (fread(&character_of_file,sizeof(char),1,open_dictionary))
{
    if (isalpha(character_of_file) != 0 || character_of_file == '\'')
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

//Implement a cursor successfully...
//The problematic code is here... The latest value is overwriting previous values associated with the node.

    starting_point = *(&table[hashed_entry]);//Replace hashed_entry with 0

    while (*(&table[hashed_entry]->next) != NULL) //table[hashed_entry]->word[0] != entry[0]) //What does this do? It takes us to the node which has a value but not a contiguous value.
    {
    *(&table[hashed_entry]) = *(&table[hashed_entry]->next);
    }

    *(&table[hashed_entry]->next) = (node *)(malloc(sizeof(node)));
    if (*(&table[hashed_entry]->next) == NULL)
    {
        printf("Error creating node...");
        return false;
    }

/// Edited up to here - Something is happening here - basically the value of the
//linked list is always on the basis of the last node added
//This is because the original node location is lost
//To counteract this a cursor should be added.
    while (isalpha(entry[e_index]) != 0 || entry[e_index] == '\'')
    {
    *(&table[hashed_entry]->word[e_index]) = entry[e_index];
    printf("%c",*(&table[hashed_entry]->word[e_index]));
    if (*(&table[hashed_entry]->word[e_index]) != entry[e_index])//If I change the value of cursor and table doesn't work, the two are not connected.
    {
    printf("Error happened while copying values from entry to table[hashed_entry]->word[i]");
    return false;
    }
    e_index++;
    }
    *(&table[hashed_entry]->word[e_index]) = '\0';

    dictionary_entry_check = (char *)(realloc(dictionary_entry_check, e_index));
    for (int i = 0; i <= e_index;i++)
    {
    *(dictionary_entry_check + i) = *(&table[hashed_entry]->word[i]);
    }
    fwrite(dictionary_entry_check,e_index,sizeof(char),working_dictionary);
    fwrite("\n",1,sizeof(char),working_dictionary);

    e_index = 0;

    printf("\n");
    *(&table[hashed_entry]->next->next) = NULL;
    /*if (table[hashed_entry]->next == NULL)
    {
    printf("Error happened while allocating memory to table[hashed_entry]->next");
    return false;
    }
    */
    *(&table[hashed_entry]) = starting_point;
    words_stored++;
    }
//eBook Produced possession property chapter chaise the them anything preference sure
//sure married though disclosed shall their cosnider surpassing acquaintance description intelligent
//arrival into for the their learn her with get which please quickness think about you
//likes concerto engaged their anybody's whom many there carriage MISS circumstance advantage choose
//hear he descending window interpolation
/*
he /4650/ first entry in linked list series of entries //is it present in load table? Y //is it present in check table? Y
her /4667/ first entry in linked list series of entries //is it present in load table? Y //is it present in check table? Y
them /12529/ first entry in linked list series of entries //is it present in load table?
shall /11875/ first entry in linked list series of entries //is it present in table?
though /12539/ first entry in linked list series of entries //is it present in table?
married /7817/ middle entry in linked list series //is it present in table?
carriage /1317/ first entry in linked list series of entries //is it present in table?
anybody's //GENUINE MISSPELLING
descending /2068/ middle entry in linked list series //is it present in load table Y?
intelligent /5544/ latter entry in linked list series //is it present in table?
acquaintance /66/ second entry in linked list series //is it present in load table Y? Is it present in check table? Y
//Errors with misspelling likely a product of an error in the check function relating to handling
//The data structure itself


interpolation /5544/ 64117 - 63535 - 582nd entry in linked list series //is it present in table?
//Make birthday cards using words from certain books in certain shapes - Christmas cards using certain typography
*/
}
free(dictionary_entry_check);
fclose(working_dictionary);
fclose(open_dictionary);
printf("%i",counter);
return true;
}





// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO - Cumulative total of nodes created - count each time node goes from empty to full and each time memory allocated to node

     unsigned int number_entries_in_dictionary = 0;
    /*

    for (int i = 0; i < N; i++)
    {
    if (isalpha(table[i]->word[0]) != 0 || table[i]->word[0] == '\'')
    {
    number_entries_in_dictionary++;
    }
    }

    */

    node *copy_of_table_starting_entry = NULL;
    for (int i = 0; i < N; i++)
    {

    copy_of_table_starting_entry = *(&table[i]);

        if (isalpha(copy_of_table_starting_entry->word[0]) != 0 || copy_of_table_starting_entry->word[0] == '\'')
        {
            number_entries_in_dictionary++;
        }

    copy_of_table_starting_entry = copy_of_table_starting_entry->next;

        while (copy_of_table_starting_entry != NULL)
        {

        if (isalpha(copy_of_table_starting_entry->word[0]) != 0 || copy_of_table_starting_entry->word[0] == '\'')
            {
                number_entries_in_dictionary++;
            }

        copy_of_table_starting_entry = copy_of_table_starting_entry->next;

        }

    }
    return number_entries_in_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
//By unloading memory, this means freeing the memory which was assigned by load.
//Closes the file, clears value of word, uses free for each sub-chain of node recursively (while node != NULL) node = node->next;
//Check for return values which indicate a failure of malloc
/*unsigned int free_entry(node *tabular_entry_referenced_by_address)
    {
    node *starting_point = *(&tabular_entry_referenced_by_address);
    node *copy_of_tabular_entry_referenced_by_address = *(&tabular_entry_referenced_by_address);
    unsigned int i = 0;

    while (copy_of_tabular_entry_referenced_by_address->next != NULL)
    {
    i++;
    copy_of_tabular_entry_referenced_by_address = copy_of_tabular_entry_referenced_by_address->next;
    }

    *(&tabular_entry_referenced_by_address) = copy_of_tabular_entry_referenced_by_address;

    free(tabular_entry_referenced_by_address);
    free(copy_of_tabular_entry_referenced_by_address);

    *(&tabular_entry_referenced_by_address) = starting_point;
    free(starting_point);

    return i;
    }
*/
bool free_memory(node * ref_to_tabular_entry)
 {
    if (ref_to_tabular_entry->next == NULL)
    {
    free(ref_to_tabular_entry);
    ref_to_tabular_entry = NULL;
    }
    else
    {
    free_memory(ref_to_tabular_entry->next);
    }
    free(ref_to_tabular_entry);
    ref_to_tabular_entry = NULL;
    return true;
 }





/*
   // TODO: Handle base case
    if (p->parents[0] == NULL && p->parents[1] == NULL)
    {
    free(p);
    p = NULL;
    }
    // TODO: Free parents recursively
    else
    {
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    }
    // TODO: Free child
    free(p);
    p = NULL;
*/

/*
    node *starting_point = ref_to_tabular_entry;
    while (starting_point != NULL)
    {

    while (ref_to_tabular_entry->next != NULL)
    {
        ref_to_tabular_entry = ref_to_tabular_entry->next;
    }

    if (starting_point == ref_to_tabular_entry)
    {
    starting_point = NULL;
    //starting_point = NULL;
    }

    free(ref_to_tabular_entry);
    ref_to_tabular_entry = NULL;
    ref_to_tabular_entry = starting_point;
    }
    free(ref_to_tabular_entry);
    ref_to_tabular_entry = NULL;
    return true;
*/
/*
    if (starting_point->next == NULL)
    {
    free(starting_point);
    starting_point = NULL;
    free(ref_to_tabular_entry);
    ref_to_tabular_entry = NULL;
    return true;
    }
    else
    {
    ref_to_tabular_entry = starting_point;
    free_memory(*(&ref_to_tabular_entry));
    }
    return false;
*/


bool unload(void)
{
    // TODO
    //Need to apply recursion here...

    bool memory_free_success;

    for (int i = 0; i < N; i++)
    {
         memory_free_success= free_memory(/* *(& */*(&table[i]))/*)*/;
         if (memory_free_success == false)
         {
            return false;
         }
    }

    return true;
    }

