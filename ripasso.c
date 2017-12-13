#include <stdlib.h>
#include <stdio.h>

int main(){
  
  int i;

  int *array;
  array = (int *) malloc(20 * sizeof(int));
  if(array == NULL) exit(-1);
  


  for(i=0; i<20; i++){
    array[i] = i*i+1;
    fprintf(stderr, "%d\n", array[i]);
  }

  array = (int *) realloc(array, 10*sizeof(int));
  free(array);

  int *malefico;
  malefico = (int *) malloc(10 * sizeof(int));
  if(malefico == NULL) exit(-1);

  for(i=0; i<10; i++) malefico[i]=i;


  for(i=0; i<20; i++){
    fprintf(stderr, "%d\n", array[i]);
  }


  return 0;
}