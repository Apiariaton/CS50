#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    char name[3];
    struct node *next;
} node;


char name[28][3] = {"A","Ab","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","\0"};
int number_key[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};

//Do I have a clear idea of what I want to do here?
//No.
//Ok what do I want to do?
//Visualise this.

int main(void)
{
int character_to_number = 64;

node *pointer_to_my_first_node = (node * )(malloc(sizeof(node)));
if (pointer_to_my_first_node == NULL)
{
printf("Oops");
return 1;
}

node * copy_to_pointer_to_first_node = pointer_to_my_first_node;
if (copy_to_pointer_to_first_node == NULL)
{
printf("Oops");
return 1;
}
/*
for (int i = 0; i < 5; i++)
{
printf("First_pointer:%p and Copy_of_first_pointer: %p",pointer_to_my_first_node++,copy_to_pointer_to_first_node);
}
*/
int up_integer = 0;
/*
pointer_to_my_first_node->number = up_integer++;
printf("First_pointer_number:%i and Copy_of_first_pointer_number: %i",pointer_to_my_first_node->number,copy_to_pointer_to_first_node->number);
*/
int size_limit = 25;
int index = 0;
for (int i = 0; i < size_limit; i++)
{
        copy_to_pointer_to_first_node->number = up_integer++;
        for (int q = 0; q < (sizeof(name)/(sizeof(char))); q++)
        {
                if ((int)(name[q][0]) - character_to_number == copy_to_pointer_to_first_node->number)
                {
                        if (strcpy(&copy_to_pointer_to_first_node->name[index++],name[q]) == NULL)
                        {
                                printf("No value copied...\n");
                        }

                }

        }
        index = 0;

        if (size_limit - 1 == i)
        {
        copy_to_pointer_to_first_node->next = NULL;
        }

        else
        {

        copy_to_pointer_to_first_node->next = (node *) malloc(sizeof(node));
        copy_to_pointer_to_first_node = copy_to_pointer_to_first_node->next;

        }

}

while (pointer_to_my_first_node->next != NULL)
{
        printf("%i\n",pointer_to_my_first_node->number);
        printf("%s\n",pointer_to_my_first_node->name);
        pointer_to_my_first_node = pointer_to_my_first_node->next;

}

}