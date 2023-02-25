#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "check_arguments.h"
#include "jpeg_file_manipulations.h"



struct magic_number_JPEG {
    int first_value[1];
    int second_value[1];
    int third_value[1];
    int fourth_value[16];
};

//Number one: Initialise - J4 *FIRST_FOUR_JPEG_BYTES

//Number two: Initialise - image_file *original_image_file by using malloc, but not assigning values

//Number three: Initialise values for copy_of_head_of_linked_list, START_FILE_BOOKMARK, END_FILE_BOOKMARK, current_position_in_JPEG_file_sequence, file_size
    //Initialise END_FILE_BOOKMARK by doing the following:
        //*START_FILE_BOOKMARK = fopen(argv[1],"rb");
        //*END_FILE_BOOKMARK = *START_FILE_BOOKMARK
        //fseek(END_FILE_BOOKMARK,512,SEEK_CUR);

//At this point we can then start the loop of functions testing to see whether write_JPEG_section_to_a_file returns 1
//capture_file_four_bytes(...);
//if (JPEG_beginning(...) == 0)
//      {
//          if (write_JPEG_section_to_a_file(...) == 1)
            //return 0;
//      }





int main(int argc, char *argv[])
{

    if(check_whether_arguments_correct(&argc,argv) == 1) //Something is going wrong - diagnose with Valgrind or with ChatGPT/StackOverflow
    {
        return 1;
    }

//Number one: Initialise - J4 *FIRST_FOUR_JPEG_BYTES

//Number two: Initialise - image_file *original_image_file by using malloc, but not assigning values

//Number three: Initialise values for copy_of_head_of_linked_list, START_FILE_BOOKMARK, END_FILE_BOOKMARK, current_position_in_JPEG_file_sequence, file_size
    //Initialise END_FILE_BOOKMARK by doing the following:
        //*START_FILE_BOOKMARK = fopen(argv[1],"rb");
        //*END_FILE_BOOKMARK = *START_FILE_BOOKMARK
        //fseek(END_FILE_BOOKMARK,512,SEEK_CUR);

//At this point we can then start the loop of functions testing to see whether write_JPEG_section_to_a_file returns 1
//capture_file_four_bytes(...);
//if (JPEG_beginning(...) == 0)
//      {
//          if (write_JPEG_section_to_a_file(...) == 1)
            //return 0;
//      }






return 0;
}


