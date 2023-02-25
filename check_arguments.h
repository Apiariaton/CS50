#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int check_whether_number_of_arguments_is_correct(int *argc, char *argv[])
{
if (*argc != 2)
{

printf("Number of arguments: %i",*argc);

        for (int i = 0; i < *argc; i++)
        {
            printf("%s\n",argv[i]);
        }

printf("This number exceeds or falls beneath the acceptable number of arguments for this program (2)...");

return 1;
}
return 0;
}

int check_whether_number_of_full_stops_is_correct(int *argc, char *argv[])
{

int *count = malloc(sizeof(int) * 1);
*count = 0;

char *copied_value = malloc(sizeof(char) * 20);

for (int i = 1; i < *argc; i++)
{
    printf("%s\n",argv[i]);
    strcpy(copied_value,argv[i]);

    for (int j = 0; j < strlen(argv[i]);j++)
    {
        if (strncmp(&copied_value[j], ".", 1) == 0) //Changed from &copied_value[j] to *copied_value[j]
        {
        //printf("Full_stop_counted...");
        *count += 1;
        }
    }
    free(copied_value);
}

if (*count != 1)
{
    printf("Full stop count is %i\n",*count);
    printf("File should contain one full stop only...");
    return 1;
}


return 0;
}



int check_whether_arguments_correct (int *argc,char *argv[])
{
if (check_whether_number_of_arguments_is_correct(argc,argv) == 1)
{
return 1;
}
printf("Correct number of arguments\n");
if (check_whether_number_of_full_stops_is_correct(argc, argv) == 1)
{
return 1;
}
printf("Correct number of full stops\n");
printf("Argv 1 is %s...\n\n",argv[1]);
if (access(argv[1], F_OK) == -1)
{
printf("The file does not exist\n");
return 1;
}
printf("File exists\n");
FILE * fp = fopen(argv[1],"r");
if (fp == NULL)
{
printf("Implementation of file read function is incorrect...");
return 1;
}
printf("Implementation of file read function is correct...\n");
return 0;
}
