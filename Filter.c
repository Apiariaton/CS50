#include "helpers.h"
#include <math.h>

// 0.0
/*
Remember to test file you should:
make filter
./filter -g images/yard.bmp out.bmp
./filter -e images/yard.bmp out.bmp
./filter -b images/yard.bmp out.bmp
./filter -r images/yard.bmp out.bmp
*/



//1.0 Should take an image and turn into a black-and-white version of the same image.
//    Maths: Take three constituents: Red, Green and Blue, each represented by two digits of a hexadecimal or in this case an RGBTRIPLE with its constituent parts
//   BYTE  rgbtBlue;
//   BYTE  rgbtGreen;
//   BYTE  rgbtRed;
//   In order for a pixel to be greyscale, the value across Blue, Green and Red must be equal.
//   The sum of the three values is taken.
//   Then, this is divided by three.
//   Then, this is rounded. 2) Question

// A) Implementation of rounding function
/*
1) try round();

2) Look into some alternative solution

3)

*/
//   Then, each constituent part:
//   BYTE  rgbtBlue;
//   BYTE  rgbtGreen;
//   BYTE  rgbtRed;
//   How to assign this value to a struct? Using pointers?
//   Acquire this new, average value.
//
//   Assume that height starts at 0, that width starts at 0. Width should be represented by j; height should be represented by i.
//   This loop takes place up to/until equal to the width value provided? 1) Question
//   Then the value of i augments until equal to the height value provided.


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float colour_value = 0.00;
    for (int h = 0; h < height; h++)
    {

        for (int w = 0; w < width; w++)
        {
        colour_value += image[h][w].rgbtBlue;             //Is this correct notation or would it be image[][]/other? Since RGBTRIPLE is a struct, we can remove?
        colour_value += image[h][w].rgbtRed;
        colour_value += image[h][w].rgbtGreen;
        colour_value /= 3;
        colour_value = (int)(colour_value);
        if (colour_value > 255)
        {
            colour_value = 255;
        }
        image[h][w].rgbtBlue = (int)(colour_value);             //Is this correct notation or would it be image[][]/other? Would we need to assign values using pointers here?
        image[h][w].rgbtRed = (int)(colour_value);
        image[h][w].rgbtGreen = (int)(colour_value);
        }

    }
    return;                     // Would this function need a return value?
}


//2.0 Reflect the image horizontally.
// Maths: Calculate the width and find the halfway point.
//If width = 2, then halfway_point = 1;
//Else, width % 2 == 0
//If width % 2 == 0, halfway_point = width/2;
//If width % 2 != 0, halfway point = (width + 1)/2;
//while (w < halfway_point)
//w and width - w
//w++
// Store Red, Green, Blue values of image[w][h] to an array of size 3;
// Write the Blue, Green, Red values of width - w to image[w][h]
//Write the Red, Green, Blue values of the array to the image[width - w][height]

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
int w = 0;

int values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[3]; //0 - Red | 1 - Green | 2 - Blue

int halfway_point = 0;

if (width == 2)
{
    halfway_point = 1;
}
else if (width % 2 == 0)
{
halfway_point = width/2;
}
else
{
halfway_point = (width + 1)/2;
}

for (int h = 0; h < height; h++)
{

while (w < halfway_point)
{
values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[0] = image[h][w].rgbtRed;            // 0 - Red
values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[1] = image[h][w].rgbtGreen;          // 1 - Green
values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[2] = image[h][w].rgbtBlue;           // 2 - Blue

image[h][w].rgbtRed = image[h][width - w].rgbtRed;
image[h][w].rgbtGreen = image[h][width - w].rgbtGreen;
image[h][w].rgbtBlue = image[h][width - w].rgbtBlue;

image[h][width - w].rgbtRed = values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[0];
image[h][width - w].rgbtGreen = values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[1];
image[h][width - w].rgbtBlue = values_to_be_conveyed_from_w_RBG_to_width_minus_w_array[2];

w++;
}
w = 0;

}
    return;
}

//3.0 Blur image - take the average of a 3 x 3 square in which the pixel in question is the central square, then add and divide by the number of squares in question
// Maths: height value cannot be below 0 nor equal to height; width value cannot be below 0 nor equal to width;
//Each time the divisor value is set to 9
// If w - 1 < 0 || w + 1 >= width, then the divisor -= 3; As three squares are unavailable
// If h -1 < 0 || h + 1 >= height, then the divisor -= 3; As three squares are unavailable
// If w - 1 < 0 || w + 1 >= width && h - 1 < 0 || h + 1 >= height, then the divisor -= 5 //Is it possible to place an or statement next to an and statement like this

//How do we work out which values are relevant?
//Blur value = 0;
//Work out the thresholds of our square - how are these calculated by testing the four statements and storing them to an array where w1 lowest w2 highest h1 lowest h1 highest
// w - 1 less than 0
//if not, store this as lowest bound, else store w
// w + 1 = width
//if not, store this as lowest bound, else store w
// h - 1 less than 0
//if not, store this as lowest bound, else store h
// h + 1 = height
//if not, store this as lowest bound, else store h
// Thresholds lowest to highest w value and lowest to highest h value, create for loops on this basis where the blur value is the sum of a for h and a for w loop
// This sum value is then divided by the divisor
// This blur value is then allocated to the central value in question only and the for loop h and for loop i progress


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
int divisor = 9;
int threshold_w1_w2_h1_h2[4];
float blur_value_R = 0.00;
float blur_value_G = 0.00;
float blur_value_B = 0.00;
for (int h = 0; h < height; h++)
{


    for (int w = 0; w < width; w++)
    {

    divisor = 9;

    if (w - 1 < 0 || w + 1 >= width)
    {
    divisor -= 3;

            if (h - 1 < 0 || h + 1 >= height)
            {
            divisor -= 2;
            }
    }

    else if (h - 1 < 0 || h + 1 >= height)
    {
    divisor -= 3;
    }

    //w1
    if (w - 1 < 0) //w1 default = w
    {
    threshold_w1_w2_h1_h2[0] = w;
    }
    else
    {
    threshold_w1_w2_h1_h2[0] = w - 1;
    }


    //w2
    if (w + 1 == height) // w2 default = w              //Unsure if two else if statements are necessary here?
    {
    threshold_w1_w2_h1_h2[1] = w;
    }
    else
    {
    threshold_w1_w2_h1_h2[1] = w + 1;
    }



    //h1
    if (h - 1 < 0) // h1 default = h
    {
    threshold_w1_w2_h1_h2[2] = h;
    }
    else
    {
    threshold_w1_w2_h1_h2[2] = h - 1;
    }



    //h2
    if (h + 1 == height) //h2 default = h
    {
    threshold_w1_w2_h1_h2[3] = h;
    }
    else
    {
    threshold_w1_w2_h1_h2[3] = h + 1;
    }


    for (int up = threshold_w1_w2_h1_h2[2];up <= threshold_w1_w2_h1_h2[3]; up++) //Height
    {
    for (int side = threshold_w1_w2_h1_h2[0]; side <= threshold_w1_w2_h1_h2[1]; side++) //Width                              //Can you increment an array value like this?
    {
    blur_value_R += image[up][side].rgbtRed;
    blur_value_G += image[up][side].rgbtGreen;
    blur_value_B += image[up][side].rgbtBlue;
    }
    }

    image[h][w].rgbtRed = round(blur_value_R/divisor);
    image[h][w].rgbtGreen = round(blur_value_G/divisor);
    image[h][w].rgbtBlue = round(blur_value_B/divisor);

    blur_value_R = 0.00;
    blur_value_G = 0.00;
    blur_value_B = 0.00;
    }





}


    return;
}






// Detect edges
//4.0 Detect the edges of an image - each pixel has a Red, Blue and Green value.


//Three arrays are created, each with total pixel count;
//Gx[pixel_count][RGB];
//Gy[pixel_count][RGB];

//Final_pixel_values[pixel_count][RGB]
//for (pixel_count)
//RGB[0] = square_root(Red_Gx + Red_Gy) etc

//for (h < height)
//for (w < width)
// image[h][w] = Final_pixel_value[pixel_count_index][0]; //Red
// image[h][w] = Final_pixel_value[pixel_count_index][1]; //Green
// image[h][w] = Final_pixel_value[pixel_count_index][2]; //Blue
//augment pixel_count_index value

//These values are the product of rounding (Gx**2 and Gy**2); Gx values (R,G,B) are computed
//by finding the sum of the following pixels (w - 1, h - 1), (w , h - 1), (w + 1, h - 1) | (w - 1, h), (w, h), (w + 1, h) | (w - 1, h + 1), (w, h + 1), (w + 1, h + 1)/9

//This can be expressed with a for h and a for w loop to move between all the values in the set and a for loop embedded in the w for loop with a new value for h - 1 up to h + 1
//and a new value for w - 1 up to w +1
//new value hm1 and
//if new value == h, then multiplier is 2
//otherwise multiplier is 1
//if new value is w, then multiplier is 0
//if new value < w, multiplier is x-1
//if new value > w, multiplier is x1

//if w - 1 < width
//if w + 1 > width
//if h - 1  < height
//if h + 1 > height
//then multiplier = 0
//value = 0

//Gy values are computed:
//if new value == w, then multiplier is 2 otherwise multiplier is 1
//if new value is h, then multiplier is 0
//if new value < h, multiplier is x-1
//if new value is greater than 1, multiplier is x1

//if w - 1 < width
//if w + 1 > width
//if h - 1  < height
//if h + 1 > height
//then multiplier = 0
//value = 0

//and
void edges(int height, int width, RGBTRIPLE image[height][width])
{
int GX_array[height * width][3];
int GY_array[height * width][3];
int tracking_index_for_each_half_array = 0;

int Final_values_for_image[height * width][3];
int GX_sum_value_r = 0;
int GX_sum_value_g = 0;
int GX_sum_value_b = 0;

int GY_sum_value_r = 0;
int GY_sum_value_g = 0;
int GY_sum_value_b = 0;


int multiplier = 0;
//GX_array_loop + GX_array_loop
for (int h = 0; h < height; h++)
{





            for (int w = 0; w < width; w++)
            {




            //GX_loop
            GX_sum_value_r = 0;
            GX_sum_value_g = 0;
            GX_sum_value_b = 0;
                    for (int hm1 = h - 1; hm1 <= h + 1; hm1++)
                    {

                            for (int wm1 = w - 1; wm1 <= w + 1; wm1++)
                            {

//new value hm1 and
//if new value == h, then multiplier is 2
//otherwise multiplier is 1
//if new value is w, then multiplier is 0
//if new value < w, multiplier is x-1
//if new value > w, multiplier is x1

                            if (hm1 == h)
                            {
                            multiplier = 2;
                            }
                            else
                            {
                            multiplier = 1;
                            }

                            if (wm1 == w)
                            {
                            multiplier = 0;
                            }
                            else if (wm1 < w)
                            {
                            multiplier *= -1;
                            }
                            else if (w < wm1)
                            {
                            multiplier *= 1;
                            }




                            }
                    }
//GY_loop








//////
//Divide both values by 9, then square the result
GX_sum_value_r = round(power(GX_sum_value_r/9));
GX_sum_value_g = round(power(GX_sum_value_g/9));
GX_sum_value_b = round(power(GX_sum_value_b/9));

GY_sum_value_r = round(power(GY_sum_value_r/9));
GY_sum_value_g = round(power(GY_sum_value_g/9));
GY_sum_value_b = round(power(GY_sum_value_b/9));




///Store the result to the GX and GY array
GX_array[tracking_index_for_each_half_array][0] =  GX_sum_value_r;               //0 - Red
GX_array[tracking_index_for_each_half_array][1] =  GX_sum_value_g;               //1 - Green
GX_array[tracking_index_for_each_half_array][2] =  GX_sum_value_b;               //2 - Blue

GY_array[tracking_index_for_each_half_array][0] = GY_sum_value_r;                //0 - Red
GY_array[tracking_index_for_each_half_array][1] = GY_sum_value_g;                //1 - Green
GY_array[tracking_index_for_each_half_array][2] = GY_sum_value_b;                //2 - Blue

tracking_index_for_each_half_array++;




            }








}
    return;
}
