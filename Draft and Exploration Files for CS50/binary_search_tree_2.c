#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;

}
node;

int main(int argc, char *argv[])
{

node *list = NULL;
int number;

for (int i = 1; i < argc; i++)
{
    number = atoi(argv[i]);
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
    return 1;
    }
    n->number = number;
    n->next = NULL;

    n->next = list;
    list = n;

    node *list_2 = list;

    while (list_2 != NULL)
    {
    printf("%i",list_2->number);
    list_2 = list_2->next;
    }

}





struct node first, second, third;
first.number = 1;
first.next = &second;
second.number = 2;
second.next = &third;
third.number = 3;

struct node remaining_numbers[5];
for (int i = 0; i < 5; i++)
{
remaining_numbers[i].number = i + 3;
if (i < 4)
{
remaining_numbers[i].next = &remaining_numbers[i + 1];
}
}
int position = 0;
struct node *bookmark;
bookmark = &remaining_numbers[0];
while (position < 4)
{

printf("%i\n",bookmark->number);
bookmark = bookmark->next;
position++;
}





    int array_to_sort[] = {1,3,2,6,3,6,4,5,9,2,10}; //Last thing I need to do is get the value of the halfway indexse
    int *array_to_store_1 = NULL;
    array_to_store_1 = (int *) malloc(sizeof(int) * 3);
    if (array_to_store_1 == NULL)
    {
    printf("Array_to_store_1 is NULL");
    return 1;
    }
    int *array_to_store_2 = (int *) malloc(sizeof(int) * 4);
    if (array_to_store_2== NULL)
    {
    printf("Array_to_store_2 is NULL");
    return 1;
    }
    int index = 0;
    int location_of_q_index = 0;
    int location_of_i_index = 0;
    size_t running_size_of_array;
    int half_point;

    if ((sizeof(array_to_sort)/sizeof(int)) % 2 != 0)
    {
        running_size_of_array = 4;
        half_point = (int)(sizeof(array_to_sort)/sizeof(int) / 2);
    }
    else
    {
        running_size_of_array = 3;
        half_point = (int)(sizeof(array_to_sort) + 1/sizeof(int) / 2);
    }

    for (int h = 0; h  < (sizeof(array_to_sort)/sizeof(int)); h++)
    {
        printf("%i,",array_to_sort[h]);
    }

int i = 0;
int q = (int)(sizeof(array_to_sort)/sizeof(int)) - 1;





//What problems are appearing? //First error arises when i == 2 and q == sizeof(array_to_sort) /sizeof(int) - 3
//The comparison is good between positions i and q
//The comparison with index needs a condition if index of array_to_store_1 equals 0


    while (i != q && i != half_point) 
    //for (int i = 0, int q = (int)(sizeof(array_to_sort)/sizeof(int)) - 1; i != (int)(sizeof(array_to_sort)/sizeof(int) / 2) && i != q; )
    {

        if (array_to_sort[i] > array_to_sort[q] || array_to_sort[i] == array_to_sort[q]) //Need to add a separate clause here for else if
        {

           while (array_to_sort[q] > array_to_store_1[index] && index < (running_size_of_array - 1) && array_to_store_1[index] != 0)
           {

            index++;

           }

           location_of_q_index = index;

           while (array_to_sort[i] > array_to_store_1[index] && index < (running_size_of_array - 1) && array_to_store_1[index] != 0)
           {

            index++;

           }

                index++; //Upshift by one to account for inserted value

            location_of_i_index = index;
        }

        else if (array_to_sort[i] < array_to_sort[q])
        {

           while (array_to_sort[i] > array_to_store_1[index] && index < (running_size_of_array - 1) && array_to_store_1[index] != 0)
           {

           index++;

           }

           location_of_i_index = index;

           while (array_to_sort[q] > array_to_store_1[index] && index < (running_size_of_array - 1) && array_to_store_1[index] != 0)
           {

           index++;

           }


                index++; //Upshift by one to account for inserted value




                location_of_q_index = index;


        }
        else
        {

        }
           index = 0;
           running_size_of_array += 2;;
           array_to_store_2 = (int *) realloc(array_to_store_2, (running_size_of_array * sizeof(int)));
           if (array_to_store_2 == NULL)
           {
           printf("Array_to_store_2 is NULL");
           return 1;
           }


           int back_marker = 0;
           for (int k = 0; k < running_size_of_array; k++) //Issue with this section of code - print out these lines
           {
                if (k == location_of_q_index)
                {
                *(array_to_store_2 + k) = *(array_to_sort + q);
                back_marker++;
                }
                else if (k == location_of_i_index)
                {
                *(array_to_store_2 + k) = *(array_to_sort + i);
                back_marker++;
                }
                else
                {
                *(array_to_store_2 + k) = *(array_to_store_1 + (k - back_marker));// Possible source of error
                }

           }

           array_to_store_1 = (int *) realloc(array_to_store_1, running_size_of_array * sizeof(int));

           if (array_to_store_1 == NULL)
           {
           printf("Array_to_store_1 is NULL");
           return 1;
           }

           printf("\n");
           for (int l = 0; l < running_size_of_array; l++)
           {
           *(array_to_store_1 + l) = *(array_to_store_2 + l);
           printf("%i, ", *(array_to_store_1 + l));
           }
           printf("\n");




    i++;
    q--;
    }

if (i == half_point)
{
index = 0;

        while (array_to_sort[i] > array_to_store_1[index])
        {
            index++;
        }
        location_of_i_index = index;

           int back_marker = 0;
           for (int k = 0; k < running_size_of_array; k++) //Issue with this section of code - print out these lines
           {
                if (k == location_of_i_index)
                {
                *(array_to_store_2 + k) = *(array_to_sort + i);
                back_marker++;
                }
                else
                {
                *(array_to_store_2 + k) = *(array_to_store_1 + (k - back_marker));// Possible source of error
                }

           }

           array_to_store_1 = (int *) realloc(array_to_store_1, running_size_of_array * sizeof(int));

           if (array_to_store_1 == NULL)
           {
           printf("Array_to_store_1 is NULL");
           return 1;
           }

           printf("\n");
           for (int l = 0; l < running_size_of_array; l++)
           {
           *(array_to_store_1 + l) = *(array_to_store_2 + l);
           printf("%i, ", *(array_to_store_1 + l));
           }
           printf("\n");






}



    for (int h = 0; h  < running_size_of_array; h++)
    {
        printf("%i,",array_to_store_1[h]);
    }





return 0;
}


