#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LENGHT 10
#define MAX 100

typedef unsigned long long int ullint;
typedef long int lint;

typedef struct coord{
  lint x;
  lint y;
}coord;

typedef struct info{
  lint init;
  int x;
  int y;
}info;

void error(int n);
struct coord finder(lint, int);


int main(){

  lint x, y;
  srand48(time(NULL));

  int L = LENGHT;
  double invRMAX = 1./(double)RAND_MAX;
  double rho = 0.1;
  lint sum = 0;
  lint i=0, ii=0, id;

  int r;

  if(L%2 == 1){ error(2);
    //L è richiesto essere un numero pari
    L++;
    printf("old L:%d New:%d\n", L-1, L);
  }

  lint **alveare;
  alveare = (lint **) calloc(L, sizeof(lint *));
  if(alveare == NULL) error(1);

  for(y=0; y<L; y++){
    alveare[y] = (lint *) calloc((L + (y%2) - 1), sizeof(lint));
    //Poiche' sto immaginando un alveare ho righe pari con colonne dispare
    //e righe dispare con colonne pari. Si assume lo zero numero pari.
    if(alveare[y] == NULL) error(1);
  }

  info *rubrica;
  rubrica = (info *) calloc((L*L - 0.5*L), sizeof(info));
  if(rubrica == NULL) error(1);

 //PRINTING STANDARD
  for(x=0; x<L; x++){

    if((L + x%2 - 1)%2 == 1) fprintf(stderr, " ");
    
    for(y=0; y<(L + (x%2) - 1); y++){
    
      i++;
      if((double)rand()*invRMAX < rho){
        alveare[x][y] = i;
        rubrica[sum].init = i;
        sum++;
      }
      
      else {
        alveare[x][y] = 0;
      }
      
      fprintf(stderr, "%03ld ", alveare[x][y]);
    }
   
    fprintf(stderr, "\n");
  }
  
  sum--; //poiche' nel if aggiungo uno dopo che sum e' stato indice di rubrica[i]
  
  rubrica = (info *) realloc(rubrica, sum*sizeof(info));
  if(rubrica == NULL) error(1);
  
  fprintf(stderr, "\ndiffusione api presenti %f %ld\n", sum/(double)((L*L) - 0.5*L), sum);


  for(i=0; i<sum; i++){
    fprintf(stderr, "%ld %ld\n", rubrica[i], sum);
  }



  //////////////////COSTRUZIONE ARRAY DI MOVIMENTO
  int pO[L-1], dO[L], pE[L-1], dE[L]; //EST OVEST righe pari e dispari
  
  for(i=0; i<L-1; i++){
    pO[i] = i-1;
    pE[i] = i+1;
  }
  
  pO[0]=L-2;
  pE[L-2]=0;

  for(i=0; i<L; i++){
    dO[i] = i-1;
    dE[i] = i+1;
  }

  dO[0]=L-1;
  dE[L-1]=0;

  int N[L], S[L];

  for(i=0; i<L; i++){
    N[i] = i+1;
    S[i] = i-1;
  }

  N[0]=L-1;
  S[L-1]=0;

  coord cella;

  for(i=0; i<MAX; i++){
    
    for(ii=0; ii<sum; ii++){

      id = lrand48()%sum;
   
      if(i==0){
        cella = finder(rubrica[id].init, L);
        x = cella.x;
        y = cella.y;
      }

      else{
        x = rubrica[id].x;
        y = rubrica[id].y;
      }

      fprintf(stderr, "name:%ld id:%d ", rubrica[id], id);


      r = lrand48()%6;

      fprintf(stderr, "r:%d x:%ld y:%ld\n", r, x, y);

      if(r == 0){ //Nord-Est
        if(y%2 == 0 && alveare[pE[x]][N[y]] == 0){
          alveare[pE[x]][N[y]] = alveare[x][y];
          rubrica[id].x = pE[x];
          rubrica[id].y = N[y];
        }
        else if(alveare[dE[x]][N[y]] == 0){
          alveare[dE[x]][N[y]] = alveare[x][y];
          rubrica[id].x = dE[x];
          rubrica[id].y = N[y];
        }
        else error(4);
      }
      else if(r == 1){ //Est
        if(y%2 == 0 && alveare[pE[x]][y] == 0){
          alveare[pE[x]][y] = alveare[x][y];
          rubrica[id].x = pE[x];
        }
        else if(alveare[dE[x]][y] == 0){
          alveare[dE[x]][y] = alveare[x][y];
          rubrica[id].x = dE[x];
        }
        else error(4);
      }
      else if(r == 2){ //Sud-Est
        if(y%2 == 0 && alveare[pE[x]][S[y]] == 0){
          alveare[pE[x]][S[y]] = alveare[x][y];
          rubrica[id].x = pE[x];
          rubrica[id].y = S[y];
        }
        else if(alveare[dE[x]][S[y]] == 0){
          alveare[dE[x]][S[y]] = alveare[x][y];
          rubrica[id].x = dE[x];
          rubrica[id].y = S[y];
        }
        else error(4);
      }
      else if(r == 3){ //Sud-Ovest
        if(y%2 == 0 && alveare[pO[x]][S[y]] == 0){
          alveare[pO[x]][S[y]] = alveare[x][y];
          rubrica[id].x = pO[x];
          rubrica[id].y = S[y];
        }
        else if(alveare[dO[x]][S[y]] == 0){
          alveare[dO[x]][S[y]] = alveare[x][y];
          rubrica[id].x = dO[x];
          rubrica[id].y = S[y];
        }
        else error(4);
      }
      else if(r == 4){ //Ovest
        if(y%2 == 0 && alveare[pO[x]][y] == 0){
          alveare[pO[x]][y]  = alveare[x][y];
          rubrica[id].x = pO[x];
        }
        else if(alveare[pO[x]][y] == 0){
          alveare[dO[x]][y] = alveare[x][y];
          rubrica[id].x = dO[x];
        }
        else error(4);
      }
      else if(r == 5){ //Nord-Ovest
        if(y%2 == 0 && alveare[pO[x]][N[y]] == 0){
          alveare[pO[x]][N[y]] = alveare[x][y];
          rubrica[id].x = pO[x];
          rubrica[id].y = N[y];
        }
        else if(alveare[dO[x]][N[y]] == 0){
          alveare[dO[x]][N[y]] = alveare[x][y];
          rubrica[id].x = dO[x];
          rubrica[id].y = N[y];
        }
        else error(4);
      }
      else error(3);
    }

    fprintf(stderr, "time:%ld\n", i);


  }

  free(alveare);
  free(rubrica);

  exit(0);
}


struct coord finder(lint n, int L){

  int flag=0;
  lint endline = 0;
  lint row = 0;
  lint column = 0;

  do{
    endline +=  (L + (row%2) - 1);
    if(n < endline) flag=1;
    else row++;
  }while(flag == 0);

  column = n - (row*L - row*0.5) - 1;

  coord cella;

  cella.x = column; 
  cella.y = row;

  return cella;
}





void error(int n){
  if(n == 1){
    fprintf(stderr, "ERROR memoria insufficiente,\n"
           "riserva e inizializzazione FALLITA!\n");
    exit(-1);
  }
  else if(n == 2){
    fprintf(stderr, "ATTENZIONE!\nIl codice è studiato per righe pari, il valore L"
           " verrà corretto\n");
  }
  else if(n == 3){
    fprintf(stderr, "Non so perche' ma hai un problema con il generatore di numeri rand()\n");
    exit(-1);
  }
  else if(n == 4){
    fprintf(stderr, "Dannazione, questo si che è un problema grave!\n");
    exit(-1);
  }
  else exit(-1);
}