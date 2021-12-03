#include<iostream>

using namespace std;


// down X increases your aim by X units.
// up X decreases your aim by X units.
// forward X does two things:
//     It increases your horizontal position by X units.
//     It increases your depth by your aim multiplied by X.

int main(void) {
   FILE *f = fopen("input1.txt", "r");

   char buff[100];
   int number;

   int x = 0;
   int y = 0;
   int aim = 0;

   while(fscanf(f, "%s %d", buff, &number) != EOF) {
      if (buff[0] == 'd') {aim += number;}
      if (buff[0] == 'u') {aim -= number;}
      if (buff[0] == 'f') {x += number; y+= aim * number;}
      printf("%d %d %d\n", x, y, aim);
   }

   fclose(f);

   printf("%d\n", x*y);

   return 0;
}
