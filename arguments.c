#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int i = 0; i < argc; i++)
    {
    int number = atoi(argv[i]);

    node *n = malloc(sizeof(node));

        if (n == NULL)
        {
        return 1;
        }
    n->number = number;
    n->next = NULL;

    n->next = list;
    list = n;
    }

node *ptr = list;

for (node *ptr = list; ptr != NULL ; ptr->next)
{

    
}



    while (ptr != NULL)
    {
    node *next = ptr;
    printf("%i\n",next->number);
    free(ptr);
    ptr = next->next;
    }
free(ptr);





}