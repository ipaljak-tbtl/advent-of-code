#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
   FILE *f = fopen("input1.txt", "r");

   char buff[100];
   int counter[100];

   fscanf(f, "%s", buff);

   int size = strlen(buff);

   for(int i = 0; i < size; ++i){
      if (buff[i] == '1') counter[i] = 1;
      if (buff[i] == '0') counter[i] = -1;
   }

   while(fscanf(f, "%s", buff) != EOF) {
      for(int i = 0; i < size; ++i) {
         if (buff[i] == '1') counter[i] += 1;
         if (buff[i] == '0') counter[i] += -1;
      }
   }

   fclose(f);

   int gamma = 0;
   int epsilon = 0;
   for (int i = size - 1; i >= 0; --i) {
      int add = 1<<(size - 1 - i);
      printf("%d %d\n", counter[i], add);
      if (counter[i] < 0) epsilon += add;
      else gamma += add;
   }

   printf("%d\n", epsilon * gamma);

   return 0;
}
