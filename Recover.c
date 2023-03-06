#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "check_arguments.h"
#include "jpeg_file_structs_and_operations.h"


int main(int argc, char *argv[])
{

    if(check_whether_arguments_correct(&argc,argv) == 1)
    {
        return 1;
    }

report_file_size_in_terms_of_byte_blocks(argv);

image_file *original_image_file = malloc(sizeof(image_file));
image_file *copy_of_head_of_linked_file_list = original_image_file;


uint8_t copy_of_final_four_value_set[16];
uint8_t hex_value = 0xe0;

        for (int i = 0; i < 16; i++)
        {

            copy_of_final_four_value_set[i] = hex_value;
            hex_value++;

        }

J4 *FIRST_FOUR_BYTES = malloc(sizeof(J4));

    FIRST_FOUR_BYTES->three_values[0] = 0xff;
    FIRST_FOUR_BYTES->three_values[1] = 0xd8;
    FIRST_FOUR_BYTES->three_values[2] = 0xd8;

    //memcpy(FIRST_FOUR_BYTES->fourth_set_of_values,copy_of_final_four_value_set,2); //Problem here with the allocation of values to fourth_set_of_values - would like to find more stream-lined solution

    for (int i = 0; i < 16; i++)
    {
    FIRST_FOUR_BYTES->fourth_set_of_values[i] = copy_of_final_four_value_set[i];
    }

uint8_t four_bytes_of_this_512_byte_block[4];


IJS *unit_characteristic_storage = malloc(sizeof(IJS));

/*
typedef struct individual_JPEG_segment
{
int current_position_in_list_of_fifty_files;
char *current_JPEG_file_name;

long int unit_start_address_as_offset;

long int unit_end_address_as_offset;
} IJS;
*/

printf("%s\n",argv[1]);
FILE * ONE_FILE_BOUND_MARKER = fopen(argv[1],"rb");

unit_characteristic_storage->unit_start_address_as_offset = ftell(ONE_FILE_BOUND_MARKER);

/*
fseek(ONE_FILE_BOUND_MARKER, 0, SEEK_END);
fseek(ONE_FILE_BOUND_MARKER,0,SEEK_SET);
fseek(ONE_FILE_BOUND_MARKER,1,SEEK_CUR); //Relativised part of file - End of file is 506368 relative bytes
fseek(ONE_FILE_BOUND_MARKER,1L,SEEK_CUR); //Why does fseek get stuck at 4096 bytes?
fseek(ONE_FILE_BOUND_MARKER,1,SEEK_CUR);
fseek(ONE_FILE_BOUND_MARKER,1,SEEK_CUR);
fseek(ONE_FILE_BOUND_MARKER,1,SEEK_CUR);
fseek(ONE_FILE_BOUND_MARKER,1,SEEK_CUR);
*/

//Different approach as it appears that I am being constrained by the current file being limited by the I/O buffer mode which is in use and I need to use fread in order to write to
//buffer. First of all, I will be taking the following data type a uint8_t. fread(uint8_t buffer, 1, 512, ONE_FILE_BOUND_MARKER) if != realloc(buffer,sizeof(buffer) + 512);
//if == fwrite(buffer,sizeof(buffer),1,copy...->file_start_location)//fclose(copy...file_start_location)


uint8_t *JPEG_image_storage_unit = malloc(sizeof(uint8_t) * 512);
int new_writing_position = 0;
uint8_t return_position = 0;

fread(JPEG_image_storage_unit,1,512,ONE_FILE_BOUND_MARKER);
capture_file_four_bytes(FILE *ONE_FILE_BOUND_MARKER,file_four_bytes);

if (JPEG_beginning(FOUR_DISTINCT_JPEG_VALUES,file_four_bytes) == 0);
{
sprintf(copy_of_head_of_linked_list->file_name,"IMG_NO_%i.jpeg",current_position_in_JPEG_file_sequence);

copy_of_head_of_linked_list->file_start_location = fopen(copy_of_head_of_linked_list->file_name,"wb");

fwrite(JPEG_image_storage_unit,sizeof(JPEG_image_storage_unit),1,copy_of_head_of_linked_file_list->file_start_location);

fclose(copy_of_head_of_linked_file_list->file_start_location);

copy_of_head_of_linked_file_list->next = malloc(sizeof(image_file));

copy_of_head_of_linked_file_list = copy_of_head_of_linked_file_list->next;

JPEG_image_storage_unit = malloc(sizeof(uint8_t) * 512);

current_position_in_JPEG_file_sequence += 1;

//return_position = ftell(ONE_FILE_BOUND_MARKER);

if (fseek(ONE_FILE_BOUND_MARKER,508,SEEK_CUR) == NULL)
{
//Capture last file




return 0;
}

fseek(ONE_FILE_BOUND_MARKER,-508,SEEK_CUR);

fwrite(file_four_bytes,4,1,JPEG_image_storage_unit);
fwrite(ONE_FILE_BOUND_MARKER,508,1,(*JPEG_image_storage_unit + 4));

}

else
{
//return_position = ftell(ONE_FILE_BOUND_MARKER);
if (fseek(ONE_FILE_BOUND_MARKER,508,SEEK_CUR) == NULL)
{
//Capture part of last file which is current file
fseek(ONE_FILE_BOUND_MARKER,-508,SEEK_CUR);

new_writing_position = sizeof(JPEG_image_storage_unit);

JPEG_image_storage_unit = realloc(JPEG_image_storage_unit,512 + new_writing_position);


fwrite(file_four_bytes,4,1,(*JPEG_image_storage_unit + new_writing_position))

fwrite(ONE_FILE_BOUND_MARKER,508,1,(*JPEG_image_storage_unit + new_writing_position + 4));

copy_of_head_of_linked_list->file_start_location = fopen(copy_of_head_of_linked_list->file_name,"wb");

fwrite(JPEG_image_storage_unit,sizeof(JPEG_image_storage_unit),1,copy_of_head_of_linked_file_list->file_start_location);

fclose(copy_of_head_of_linked_file_list->file_start_location);

return 0;
}

new_writing_position = sizeof(JPEG_image_storage_unit);

JPEG_image_storage_unit = realloc(JPEG_image_storage_unit,512 + new_writing_position);

fwrite(file_four_bytes,4,1,(*JPEG_image_storage_unit + new_writing_position));

fwrite(ONE_FILE_BOUND_MARKER,508,1,(*JPEG_image_storage_unit + new_writing_position + 4)); //Return to this later



}












return 0;
}
