#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
uint8_t *number_list = malloc(sizeof(uint8_t) * 3);
number_list[0] = 1;
number_list[1] = 2;
number_list[2] = 3;

uint8_t *tmp = (uint8_t *) realloc(number_list,sizeof(uint8_t) * 4);
if (tmp == NULL)
{
return 1;
}
number_list = tmp;
number_list[3] = 4;
for (int i = 0; i < 4; i++)
{
printf("%i",*(number_list + i));
}

//No way to binary search
//No way to use square bracket indexing
//

typedef struct node
{

    int number;
    node *next;

} node;


node *list = NULL;

node *n = malloc(sizeof(node));
n->number = 1;
n->next = NULL;

list = n;

node *n2 = malloc(sizeof(node));
n2->number = 2;
n2->next = NULL;

n->next = n2;

node *n0 = malloc(sizeof(node));
n0->number = 0;
n0->next = n;


}