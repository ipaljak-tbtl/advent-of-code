#include<iostream>

using namespace std;

int main(void) {
   FILE *f = fopen("input1.txt", "r");

   char buff[100];
   int number;

   int x = 0;
   int y = 0;

   while(fscanf(f, "%s %d", buff, &number) != EOF) {
      if (buff[0] == 'f') x += number;
      if (buff[0] == 'd') y += number;
      if (buff[0] == 'u') y -= number;
   }

   fclose(f);

   printf("%d %d\n", x, y);

   printf("%d\n", x*y);

   return 0;
}
