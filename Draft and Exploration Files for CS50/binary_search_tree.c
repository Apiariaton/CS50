#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/*Brief:
    Create a binary search tree that returns the
    pointer to a value when this value is located.
    This bst is created from a series of inputted arguments.
*/

int main(int argc, char *argv[])
{

int tmp1[argc - 1];
int tmp2[argc - 1];
for (int i = 1; i < argc; i++)
{
tmp1[i] = atoi(argv[i]);
}

int store = 0;
int A = 0;
int sort_interval = 2;
while (sort_interval <= sizeof(tmp1))
{

    for (int i = 0; i < (sizeof(tmp1)/2); i++)
    {

            for (int q = 0; q < sizeof(tmp1); q += sort_interval)
            {

                    for (int k = q; k < q + sort_interval; k++)
                    {
                            if (tmp1[k + 1] < tmp1[k] && A % 2)
                            {
                               tmp2[k] = tmp1[k + 1];
                               tmp2[k + 1] = tmp1[k];
                            }

                            else if (tmp2[k + 1] < tmp2[k] && A % 2 != 0)
                            {
                                tmp1[k] = tmp2[k+1];
                                tmp1[k + 1] = tmp2[k];
                            }

                            else
                            {


                            }

                    }


            }
            A++;

    }

sort_interval *= 2;
}







binreturn 0;
}