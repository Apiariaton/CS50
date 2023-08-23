#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

typedef struct tree
{
char *person[7];
int number;
struct tree *left;
struct tree *right;

} tree;

bool search(tree *tree, int number_to_be_found)
{
if (tree->number == number_to_be_found)
{
    printf("%i",tree->number);
    return true;
}
else if (tree->number < *number_to_be_found)
{
tree = tree->left;
return search(tree->left, number_to_be_found);
}
else if (tree->number > *number_to_be_found)
{
tree = tree->right;
return search(tree->right, number_to_be_found);
}
else
{
    return false;
}

}


int main(void)
{




















}