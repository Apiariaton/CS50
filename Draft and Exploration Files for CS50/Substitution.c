//Substitution cipher

#include <stdio.h>
#include <stdlib.h>

int main(void){
char key[30];
char string_to_be_encoded[26];
int numer_output_message[26];
int rel_position_in_ASCI = 0;


printf("Key:\n");
fgets(key,30,stdin);
printf("String to encode: ");
fgets(string_to_be_encoded,26,stdin);

printf("Key: %s \nThe String: %s ", key, string_to_be_encoded);
for (int i = 0; i < 26; i++){
    int rel_position_in_ASCI = ((int)(string_to_be_encoded[i]));
    rel_position_in_ASCI -= 97;
    numer_output_message[i] = key[rel_position_in_ASCI];
}
printf("%s","Your secret message: ");
for (int i = 0; i < 26; i++){
printf("%c",numer_output_message[i]);
}
//zbcdefghijklmnopqrstuvwxya

printf("\n Time to decrypt: \n");
printf("Decrypted message is:  ");
int j = 0;
int decrypted_message[30];
for (int i = 0; i < 30; i++){
    while (numer_output_message[i] != key[j]){
        j++;
    }
    decrypted_message[i] = 97 + j;
    printf("%c",(char)(decrypted_message[i]));
    j = 0;
}


