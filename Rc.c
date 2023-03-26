#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "check_arguments.h"
#include "jpeg_file_structs_and_operations.h"
#include <stdio.h>


int main(int argc, char *argv[])
{

    if(check_whether_arguments_correct(&argc,argv) == 1)
    {
        return 1;
    }

FILE *card_raw = fopen(argv[1],"r");
fseek(card_raw,0,SEEK_END);
long int file_size = ftell(card_raw);
fclose(card_raw);

//uint8_t magic_number_set[4] = {0xd8,0xd8,0xff,0xe0}; //Final number to have bitwise comparison performed

uint8_t *buffer_to_store_file_stream = (uint8_t *) malloc(513);

for (int i = 0; i < 513; i++)
{
*(buffer_to_store_file_stream + i) = 0;
}

FILE *card_dot_raw = fopen(argv[1],"r");
int JPEG_magic_number_sequence_start_found = 0;
long int relative_position_of_start_of_JPEG_sequence_within_file = 0;
long int pos_within_512_bytes = 0;

while (JPEG_magic_number_sequence_start_found == 0)
{
fread(buffer_to_store_file_stream,1,512,card_dot_raw);


for (int i = 0; i < 512; i++)
{
printf("%u",*(buffer_to_store_file_stream + i));
}

for (int i = 0; i < 512; i++)
{
if (*(buffer_to_store_file_stream + i) == 0xff )
{
    if (*(buffer_to_store_file_stream + i + 1) == 0xd8 )
    {
        if (*(buffer_to_store_file_stream + i + 2) == 0xff)
        {
            //
            if (((*(buffer_to_store_file_stream + i + 3)) & 0xf0) == 0xe0)
            {
            printf("First four numbers of magic number sequence found");
            relative_position_of_start_of_JPEG_sequence_within_file += i;
            pos_within_512_bytes = i;
            printf("This is where the JPEG file sequence starts: %lu", relative_position_of_start_of_JPEG_sequence_within_file);
            JPEG_magic_number_sequence_start_found = 1;
            }

        }
    }
}

}
relative_position_of_start_of_JPEG_sequence_within_file += 512;
}
fseek(card_dot_raw,-(512 - pos_within_512_bytes),SEEK_CUR); //Now next step...

int first_file_read = 0;
int current_file_number = 0;
char *current_file_name = (char *) malloc(9);



int bytes_read = 0;
int how_many = 0;
uint8_t *buffer_new = (uint8_t *) malloc(512);
for (int i = 0; i < 512; i++)
{
*(buffer_new + i) = 0;
printf("%u", *(buffer_new + i));
}

sprintf(current_file_name,"%03d.jpeg",current_file_number++);
FILE * current_JPEG_file = fopen(current_file_name,"w");

long long position_cdr = 0;

int i = 0;

//while (i == 0)
//{
while (i == 0)
{
while (bytes_read < 512)
{
how_many = fread(buffer_new++,1,1,card_dot_raw); //Possible segmentation error unless buffer reset
if (how_many == 0)
{
//Break the loop but first we need to identify whether the first four numbers of the buffer match those of the JPEG magic number sequence: if they don't, write
//to existing current_JPEG_file - if they do, write a new current_JPEG_file
i = 1;
}
position_cdr = ftell(card_dot_raw);
bytes_read += how_many;
printf("%i",bytes_read);
//printf("Position CDR:%lld",position_cdr);
}

if (first_file_read == 0)
{
buffer_new -= 512;
int number_written = fwrite(buffer_new,1,512,current_JPEG_file);
first_file_read = 1;
}
///
else
{
buffer_new -= 512;

if (*(buffer_new) == 0xff)// && printf("This is buffer_new's first value %u",*(buffer_new)))
{
    if (*(buffer_new + 1) == 0xd8 )
    {
        if (*(buffer_new + 2) == 0xff)
        {
            //
            if (((*(buffer_to_store_file_stream + 3)) & 0xf0) == 0xe0)
            {
            fclose(current_JPEG_file);
            printf("First four numbers of magic number sequence found");
            sprintf(current_file_name,"%03d.jpeg",current_file_number++);// \0 may be unnecessary
            puts(current_file_name);
            current_JPEG_file = fopen(current_file_name,"w");
            fwrite(buffer_new,1,512,current_JPEG_file);
            }

        }
    }
}
printf("This is the size of buffer_new %lu",sizeof(buffer_new));
for (int q = 0; q < 512; q++)
{printf("No. %i: %u",q,*(buffer_new + q));} //If all data can be seen error is with current_JPEG_file
fwrite(buffer_new,1,512,current_JPEG_file); //What is my diagnosis of the problem?
//Problem speculation: fwrite is attempting to read to memory that is not accessible to current_JPEG_file
//because there is another variable "in the way"
//Easiest to solve - because current_JPEG_file is unnaturally big and should be smaller, meaning there is an issue with fclose
//because memory is being read from buffer_new in such a way that the data ends before the read is complete
}
//What tests can we create?


bytes_read = 0;
how_many = 0;
}
}

/* Pseudocode script
1. First check that arguments are correct.
2. Second open with "r" and determine file size, using fseek, followed by ftell. Store as a long int.
3. Close the file in question.
--Test phase 0--
4. Next create a value with uint8_t: this is going to be the value referred to by malloc. Malloc needs to be typecast to uint8_t to coincide with the value type.
5. Write a file start loop. Open the argument in read mode. While the start has not been found, read 512 bytes from card_dot_raw to the buffer.
--Test phase 0.5
6. Cycle through this buffer, storing the relative position to as a r_file_position_marker.
7. When the bytes of the buffer coincide with the magic number JPEG sequence, store ftell as the buffer end variable.
8. Separately, write a variable called difference between buffer end and start.
9. Store the value of ftell buffer end minus r_file_position_marker to starting_position_of_JPEG_photobook.
10. Move the file pointer to this position using -starting_position_of_JPEG_photobook and fseek (SEEK_CUR).
11. Check that fseek's return value is 0.
--Test phase 1 --
12. Using sprintf, write the current name of the file to the file_pointer_name and augment the file number.
13. Read the content of the file, character by character while incrementing x, into a file_pointer for JPEG_storage.
    -If fread returns 0,
    -Close the current file
14. Use ferror to test the file from which data is being read. If return value is not 0, an error has been produced.
15. When x is 512, reset to 0. Write the first four numbers to a magic number buffer.
--Test phase 2 --
16. Check that the numbers in the buffer do not match the magic number sequence.
17. If they do, move the file pointer back using fseek -4 SEEK_CUR.
    -Then close the file to which the JPEG was being written.
18. If not write previously, following steps 12 to 15.
--Test phase 3--
*/
