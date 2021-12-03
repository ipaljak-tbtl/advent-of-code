#include <iostream>
#include <cstring>

using namespace std;

int main(void) {
   FILE *f = fopen("input1.txt", "r");

   char buff[1005][100];
   int row_size = 0;
   while(fscanf(f, "%s", buff[row_size++]) != EOF);
   fclose(f);

   int col_size = strlen(buff[0]);
   row_size--;

   bool skip_row[1005] = {0};
   char *o2;

   for(int curr_col = 0 ; curr_col < col_size ; ++curr_col) {
      int count_0 = 0;
      int count_1 = 0;
      for(int i = 0 ; i < row_size ; ++i) {
         if (skip_row[i]) continue;
         if (buff[i][curr_col] == '0') count_0++;
         if (buff[i][curr_col] == '1') count_1++;
      }

      int count_left = 0;
      for(int i = 0 ; i < row_size ; ++i) {
         if (skip_row[i]) continue;
         if (count_1 >= count_0 && buff[i][curr_col] == '0') skip_row[i] = true;
         else if (count_1 < count_0 && buff[i][curr_col] == '1') skip_row[i] = true;
         else {count_left++; o2 = buff[i];}
      }
      if (count_left == 1) break;
   }

   printf("%s\n", o2);

   for(int i = 0 ; i < row_size;++i) skip_row[i] = false;
   char *co2;

   for(int curr_col = 0 ; curr_col < col_size ; ++curr_col) {
      int count_0 = 0;
      int count_1 = 0;
      for(int i = 0 ; i < row_size ; ++i) {
         if (skip_row[i]) continue;
         if (buff[i][curr_col] == '0') count_0++;
         if (buff[i][curr_col] == '1') count_1++;
      }

      int count_left = 0;
      for(int i = 0 ; i < row_size ; ++i) {
         if (skip_row[i]) continue;
         if (count_1 < count_0 && buff[i][curr_col] == '0') skip_row[i] = true;
         else if (count_1 >= count_0 && buff[i][curr_col] == '1') skip_row[i] = true;
         else {count_left++; co2 = buff[i];}
      }
      if (count_left == 1) break;
   }

   printf("%s\n", co2);

   int o2_num = 0;
   int co2_num = 0;

   for(int i = 0 ; i < col_size ; ++i) {
      int add = 1<<(col_size - 1 - i);
      if (o2[i] == '1') o2_num += add;
      if (co2[i] == '1') co2_num += add;
   }

   printf("%d %d\n", o2_num, co2_num);

   printf("%d\n", o2_num * co2_num);

   return 0;
}
