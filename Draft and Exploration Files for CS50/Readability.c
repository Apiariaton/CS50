//Coleman Liau quick build
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int number_of_letters;
int number_of_words;
int number_of_sentences;
char analysis_sequence[500];

int main (void){
    number_of_letters = 0;
    number_of_sentences = 0;

    printf("%s","Text for analysis: ");
    fgets(analysis_sequence,500,stdin);


        printf("%s",analysis_sequence);

    int count_letters(){
    for (int i = 0; i < 500; i++){
        int char_to_num = (int)(analysis_sequence[i]);
        //printf("%i \n", char_to_num);
        if(64 < char_to_num){
            if (char_to_num < 91){
                number_of_letters++;
            }
            else if (char_to_num > 96){
                if (char_to_num < 122){number_of_letters++;}
                else {}
            }
            else {}

            //printf("\n %i",number_of_letters);
                }else {}

    }
    printf("Letters: %i \n",number_of_letters);
    }

    int count_words(){
        number_of_words += 1;
        int i = 0;
        while (i < 500){
        int char_to_num = (int)(analysis_sequence[i]);
        if (char_to_num == 32){
            number_of_words++;
        }
        else {}
        i++;

        }
        printf("Words: %i \n",number_of_words);
    }

count_words();


int count_sentences(){
    int i = 0;
    for (int i = 0; i < 500; i++){

    int char_to_num = (int)(analysis_sequence[i]);
    int previous_char_to_num = (int)(analysis_sequence[i - 1]);

    if (i > 0){
    if (previous_char_to_num != 46 && previous_char_to_num != 33 && previous_char_to_num != 63){
       if (char_to_num == 33 || char_to_num == 46 || char_to_num == 63)
       {
          number_of_sentences++;
       }
       else {}
    }
    else {}
    }else{}}
    printf("Sentences %i",number_of_sentences);
    return number_of_sentences;
}




    count_letters();
    count_sentences();

printf("\n \n Data going into CLformula: \n Number of letters %i \n Number of words %i \n Number of sentences %i \n",number_of_letters,number_of_words,number_of_sentences);

float L = ((float)(number_of_letters)/((float)(number_of_words))) * 100; //Letters / Words x 100;
printf("\n Number of sentences %i", number_of_sentences); //Sentences/Words x 100

float S = ((float)(number_of_sentences)/(float)(number_of_words)) * 100;
printf(" \n This is L %f",L);
printf(" \n This is S %f",S);


float CLindex = (0.0588 * L) - (0.296* S) - 15.8;
float CLindexs = (0.0588 * L) - 15.8;

float Dummyfloat = 1.234;
int Dummyint = (int)(Dummyfloat);
printf("\n Dummyfloat indexed float %f",Dummyfloat - Dummyint);



if ((CLindex) < 1)
{
    printf("\n The Grade Level for this text is below 1");
}




else{
int final_answer = 0;
float round_up = CLindex - (int)(CLindex);
printf("\n Round up is %f", round_up);

if (round_up >= 0.5){
    printf("\n Round up \n");
    final_answer = (int)(CLindex) + 1;
}
else {final_answer = (int)(CLindex); }
printf("\n The Grade Level for this text is %i",final_answer);
}
}
