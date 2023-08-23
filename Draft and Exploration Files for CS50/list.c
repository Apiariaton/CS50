#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct node
{
    int number;
    struct node *next;

} node;


int main(void)
{
//Creating a basic list...


node *item_1 = malloc(sizeof(node));
node *item_2 = malloc(sizeof(node));
node *item_3 = malloc(sizeof(node));

item_1->number = 1;
item_2->number = 2;
item_3->number = 3;

item_1->next = item_2;
item_2->next = item_3;
item_3->next = item_1;

node *item_to_be_printed = item_1;
for (int i = 0; i < 6; i++)
{
printf("This is item_%i: %i,",i,item_to_be_printed->number);
item_to_be_printed = item_to_be_printed->next;
}


return 0;
}