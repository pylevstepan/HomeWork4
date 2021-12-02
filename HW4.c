#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char symbol;
int f, f2, f3, f4, f5, elm, i, j, count_a, count_b, max_a, max_b, max, g, sum;
int *a, *b;

int main(void) {
  FILE* file_a;
  FILE* file_b;
  FILE* file_c;
  count_a = 0;
  count_b = 0;
  f = 0;
  g = 1;
  max_a = -1;
  max_b = -1;
  i = 1;
  j = 1;
  f2 = 0;
  f3 = 0;
  f5 = 0;
  sum = 0;

  //Draw Graphs A B

  system("dot a.dot -Tpng -o a.png");
  system("dot b.dot -Tpng -o b.png");

  //Open files and find number of lines

  file_a = fopen("a.dot", "r");
  while ((symbol = getc(file_a)) != EOF) {
    putc(symbol, stdin);
    if (symbol == '\n')
      count_a ++;

  }

  file_b = fopen("b.dot", "r");
  while ((symbol = getc(file_b)) != EOF) {
    putc(symbol, stdin);
    if (symbol == '\n')
      count_b ++;
  }
  
  fclose(file_a);
  fclose(file_b);

  count_a *= 2;
  count_b *= 2;

  a = (int*)malloc(count_a * sizeof(int));
  b = (int*)malloc(count_b * sizeof(int));

  //Get number of tops from files and write to arrays

  file_a = fopen("a.dot", "r");
  while ((symbol = getc(file_a)) != EOF) {
    if ((symbol <= '9') && (symbol >= '0')){
      elm = elm * 10 + (int)(symbol - '0');
      f3 = 1;
    }
    if (symbol == '-')
      f++;
    if (symbol == '\n')
      g++;
    if (f > 0)
      g = 0;
    if (((f == 2) || (symbol == '\n')) && (f3 == 1)) {
      if (g == 2) {
        a[i] = elm;
        a[i+1] = elm;
        i = i + 2;
        g = 1;
      } else {
        a[i] = elm;
        f = 0;
        i++;
      }
        elm = 0;
    }
    if (count_a == i)
      break;
  }

  f = 0;
  g = 1;
  f3 = 0;
  f4 = 0;
  file_b = fopen("b.dot", "r");
  while ((symbol = getc(file_b)) != EOF) {
    if ((symbol <= '9') && (symbol >= '0')){
      elm = elm * 10 + (int)(symbol - '0');
      f3 = 1;
    }
    if (symbol == '-')
      f++;
    if (symbol == '\n')
      g++;
    if (f > 0)
      g = 0;
    if (((f == 2) || (symbol == '\n')) && (f3 == 1)) {
      if (g == 2) {
        b[j] = elm;
        b[j+1] = elm;
        j = j + 2;
        g = 1;
      } else {
        b[j] = elm;
        f = 0;
        j++;
      }
        elm = 0;
    }
    if (count_b == j)
      break;
  }

  //Sorting arrays and find Max

  count_a -= 2;
  count_b -= 2;
  for (int i = 1; i<=count_a; i += 2)
    if (a[i]<a[i+1]){
      int t = a[i];
      a[i] = a[i+1];
      a[i+1] = t;
    }
  for (int i = 1; i<=count_b; i += 2)
    if (b[i]<b[i+1]){
      int t = b[i];
      b[i] = b[i+1];
      b[i+1] = t;
    }
  for (int i = 1; i<=count_a; i++)
    if (a[i]>max_a)
      max_a = a[i];
  for (int i = 1; i<=count_b; i++)
    if (b[i]>max_b)
      max_b = b[i];

  if (max_a > max_b){
    max = max_a;
  } else{
    max = max_b;
  }

  //Write information to the table

  int **mtrx_a=(int**)calloc(max_a+2, sizeof(int*));
  for(int i=1; i<=max_a; i++)
  mtrx_a[i]=(int*)calloc(max_a+2, sizeof(int));
  for (int j = 1; j<= count_a; j++){
    if ((j % 2) == 1){
      int x = a[j];
      int y = a[j+1];
      mtrx_a[x][y] += 1;
    }
  }

  int **mtrx_b=(int**)calloc(max_b+2, sizeof(int*));
  for(int i=1; i<=max_b; i++)
  mtrx_b[i]=(int*)calloc(max_b+2, sizeof(int));
  for (int j = 1; j<= count_b; j++){
    if ((j % 2) == 1){
      int x = b[j];
      int y = b[j+1];
      mtrx_b[x][y] += 1;
    }
  }

  //Searching for alone tops

  for (int i = 1; i<=max_a; i++){
    if (mtrx_a[i][i] != 0){
      for (int j = 1; j<=max_a; j++){
        if (i != j) {
        sum = sum + mtrx_a[i][j] + mtrx_a[j][i];
        }
      }
      if (sum == 0){
        while (mtrx_a[i][i] > 0)
        mtrx_a[i][i] --;
      }
      else sum = 0;
      }
  }

  for (int i = 1; i<=max_b; i++){
    if (mtrx_b[i][i] != 0){
      for (int j = 1; j<=max_b; j++){
      if (i != j)
        sum = sum + mtrx_b[i][j] + mtrx_b[j][i];
      }
      if (sum == 0){
        mtrx_b[i][i] = 0;;
      }
      else sum = 0;
    }
  }


  //Create and write information to result table

  int **mtrx_c=(int**)calloc(max+2, sizeof(int*));
  for(int i=1; i<=max; i++)
    mtrx_c[i]=(int*)calloc(max+2, sizeof(int));
  if ((max_a == max) || (max_a == max_b))
    for (int i = 1; i<= max; i++){
      for (int j = 1; j<= max; j++)
        mtrx_c[i][j] = mtrx_a[i][j];
      }
  if (max_b > max_a)
    for (int i = 1; i<= max; i++){
      for (int j = 1; j<= max; j++)
        if ((i <= max_a) && (j <= max_a))
          mtrx_c[i][j] = mtrx_a[i][j];
    }
  if (max_a == max){
    for (int i = 1; i<= max; i++){
      for (int j = 1; j<= max; j++){
        if ((i <= max_b) && (j <= max_b)) {
          if (mtrx_b[i][j] == mtrx_a[i][j])
            f5 = 1; 
          if ((mtrx_b[i][j] != 0) && (f5 = 1))
            if (mtrx_b[i][j] > mtrx_a[i][j])
              mtrx_c[i][j] = mtrx_b[i][j];
          }
        }
      }
    }
  f5 = 0;
  if (max_b == max){
    for (int i = 1; i<= max; i++){
      for (int j = 1; j<= max; j++){
        if ((i <= max_a) && (j <= max_a)) {
          if (mtrx_b[i][j] == mtrx_a[i][j])
            f5 = 1; 
          if ((mtrx_b[i][j] != 0) && (f5 = 1))
            if (mtrx_b[i][j] > mtrx_a[i][j])
              mtrx_c[i][j] = mtrx_b[i][j];
          }
          if ((mtrx_b[i][j] != 0) && (f5 = 1))
          mtrx_c[i][j] = mtrx_b[i][j];
        }
      }
    }

  fclose(file_a);
  fclose(file_b);

  //Write information in new file and draw the result Graph

  file_c = fopen("c.dot", "w+");
  fprintf(file_c, "graph new{\n");
  if (f5 != 0){
  for (int i = 1; i<= max; i++){
    for (int j = 1; j<= max; j++){
      while (mtrx_c[i][j] != 0){
        fprintf(file_c, "%d--%d\n", i, j);
        mtrx_c[i][j] --;
      }
    }
  }
  }
  fprintf(file_c, "}");


  fclose(file_c);
  system("dot c.dot -Tpng -o c.png");

  //Schindler's list
  
  free(b);
  free(a);
  free(mtrx_a);
  free(mtrx_b);
  free(mtrx_c);
}

