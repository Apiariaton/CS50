#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct Thought {
char *thought_content;
};

struct Brain {
struct Thought thought[5];
};

struct Human {
char *name;
struct Brain brain[1];
};

struct Camp_Fire {
struct Human human[4];
};

struct Pixel {
int RGB[3];
};

struct Picture
{
struct Pixel px[3];
};

int main(void)
{

struct Camp_Fire Man_First_Fire;

Man_First_Fire.human[0].name = malloc(9);
strcpy(Man_First_Fire.human[0].name,"Gareth");
Man_First_Fire.human[0].brain[0].thought[0].thought_content = malloc(50);
Man_First_Fire.human[0].brain[0].thought[0].thought_content = "Hmmm I think Nenar is beautiful";
printf(Man_First_Fire.human[0].name,"%s");
printf(Man_First_Fire.human[0].brain[0].thought[0].thought_content,"%s");

for (int i = 0; i < 4; i++)
{
printf("No. %i: %s",i,Man_First_Fire.human[i].name);
}

struct Picture triangle =
{
{{1,2,1},
{3,3,3},
{1,2,1}
}
};


uint8_t list[3];
list[0] = 1;
list[1] = 2;
list[2] = 3;
for (int i = 0; i <3; i++)
{printf("%u",list[i]);}


return 0;
}
