#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

//Problem breakdown
//FUNCTION 1 int check_argument();
//1.0 First accept an argument only if the argument count is 1.
//Otherwise throw an error message by returning 1 and printing error message.
//A. How is the arg count calculated? Represented by argc. A second rule is that there should be no
//more than one full stop.

//int check_file_is_readable();
//2.0 Then open or attempt to open the image for reading. If the image cannot be read,
//return 1 after printing an error message "File not readable. Please try again,
//ensuring the file is interpretable as a series of JPEG images".
//B. How do you read a file in C?
//fopen() (add a FILE pointer to the file)
//assign a variable the function fopen()
//if the variable == NULL invalid function
//Not going to include file size calculation - were I to do this though, could use fseek();

//3.0 Going up in jumps of 512 bytes, the first four hexadecimals of the sequence should be read.
//If they match the number corresponding to the start of a JPEG, then the cumulative number stored
//will be used to allocate memory for the given image.
//while (!(check_byte_values_of_current_position(&current_position))
//{current_position += 512 bytes (pointer arithmetic)}

//fgets(char *first_four_hexadecimal_byte_values, int size (of hexadecimals), FILE *ptr (current index)

//while (fgets(additive_string, 512, pointer to file) != NULL)
//{
//if ([0:4] == Hexadecimal sequence)
//REALLOCATE SIZE OF IMAGE IN QUESTION IN RELATION TO ADDITIVE STRING
//COMBINE EXISTING STRING WITH ADDITIVE STRING
//WRITE THIS STRING TO A FILE CALLED NO. X
//INCREMENT FILE NUMBER SIZE
//FREE(MEMORY OF CURRENT JPEG STORE)
//MALLOC(512 bytes)
//else
////REALLOCATE SIZE OF IMAGE IN QUESTION IN RELATION TO ADDITIVE STRING
//COMBINE EXISTING STRING WITH ADDITIVE STRING
//}


//3.5 An image placeholder should be created where an individual JPEG stored. The size of this
//should be allocated by malloc(in proportion to the number of bytes taken up by the image).


//4.0 This image should be written to another file, whose name corresponds to an image number tracker,
//which increments with each image extracted.

//5.0 This file should then be closed upon finish. The memory allocated to the image should be freed.



















}
