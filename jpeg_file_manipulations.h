#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



typedef struct JPEG_4
{
long three_values[3];
long fourth_set_of_values[16];
} J4;


typedef struct node
{
char * file_name;
FILE * file_start_location;
long file_size;
struct node *next;
}
image_file;


void capture_file_four_bytes(FILE *END_FILE_BOOKMARK,long *file_four_bytes[4])
{
memset(file_four_bytes, (long) 0, sizeof(*file_four_bytes));
fread(file_four_bytes,sizeof(long),4,END_FILE_BOOKMARK);
}


int JPEG_beginning(struct JPEG_4 *J4,long file_four_bytes[4])
{

    for (int i = 0; i < 4; i++)
    {

        if (J4->three_values[i] != file_four_bytes[i])
        {
        return 1;
        }

    }


    for (int i = 0; i < 16; i++)
    {

        if (J4->fourth_set_of_values[i] == file_four_bytes[3])
        {
        return 0;
        }

    }

return 1;
}

//When we open card.raw, this should be in rb?



int write_JPEG_section_to_a_file(image_file **copy_of_head_of_linked_list, FILE ** START_FILE_BOOKMARK, FILE ** END_FILE_BOOKMARK, int *current_position_in_JPEG_file_sequence, long int *file_size)
{
//Do these files need to be pointers to ensure we are not just copying the values?

//Trigger this if JPEG_beginning returns true - what do we need here?

//Start bookmark and end bookmark - these are going to be file pointers
//Start bookmark is intially going to be the value of fopen("card.raw","r") which should return a file pointer;

//After a function call, it will be assigned the value of JPEG_FILE_BOOKMARK
//End bookmark is going to be the same as JPEG_FILE_BOOKMARK
sprintf((*copy_of_head_of_linked_list)->file_name,"IMG_NO_%i.jpeg",*current_position_in_JPEG_file_sequence);

(*copy_of_head_of_linked_list)->file_start_location = fopen((*copy_of_head_of_linked_list)->file_name,"wb");

*file_size = (long) END_FILE_BOOKMARK - (long) START_FILE_BOOKMARK;

fwrite(START_FILE_BOOKMARK,sizeof(int),((*file_size)/4),(*copy_of_head_of_linked_list)->file_start_location);

fclose((*copy_of_head_of_linked_list)->file_start_location);

//We then need to write to a struct image_file - beforehand we will have assigned to file name by cycling through head and assigning an augmented file name

//To write to this node, we will use the pointers START_FILE_BOOKMARK and JPEG_FILE_BOOKMARK as NAME_OF_image_file->file_start
//We will determine the size of the file, allocate a corresponding block of memory
//We will then close the file using the following notation fclose(NAME_OF_image_file->file_start)
//Then assign start bookmark the value of end book mark


//If FSEEK SEEKSET returns NULL for card.raw using the END_FILE_BOOKMARK - we will return 1

//By default the function will return 0
(*copy_of_head_of_linked_list)->next = malloc(sizeof(image_file));

*copy_of_head_of_linked_list = (*copy_of_head_of_linked_list)->next;

*START_FILE_BOOKMARK = *END_FILE_BOOKMARK;

if (fseek(*END_FILE_BOOKMARK,512,SEEK_CUR) != 0)
{
return 1;
}

(*current_position_in_JPEG_file_sequence)++;


return 0;
}


