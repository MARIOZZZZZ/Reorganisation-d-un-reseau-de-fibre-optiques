#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graphe.h"
#include "Struct_Liste.h"
#include "Dijkstra.h"
#include "evaluation_NChaines.h"

int main(int argc,char**argv){

  char filename[104],filenameres[104],filenamencha[104];;
  int chmeth, gamma = 0;
  double longueur, eval;

  if(argc!=3){
    printf("usage: %s <file> <numeromethod>\n",argv[0]);
    printf("where numeromethode = 1 if using Width firs search; 2 if using algorithme dijkstra\n");
    return 1;
  }

  chmeth=atoi(argv[2]);
  strcpy(filename,argv[1]);
  strcpy(filenameres,argv[1]);
  strcpy(filenamencha,argv[1]);
  strcat(filenameres,".res");
  strcat(filenamencha,".ncha");

  FILE *f=fopen(filenameres,"r");

  if (f==NULL){
    printf("Probleme lecture du fichier %s\n",filenameres);
    exit(1);
  }

  Graphe G;

  lecture_graphe(&G,f);

  fclose(f);

  afficheGrapheSVG(&G,filename);

  FILE *f2 = fopen(filenamencha, "w+");

  longueur = Application_Du_Dij(&G, &gamma, f2);

  printf("\n longueur = %.2f", longueur);
  printf("gamma = %d\n", gamma);

  fclose(f2);
  
  eval = evaluation_NChaines(gamma, longueur, "07397_pla");
  printf("Evaluation = %.2f\n", eval);


  return 0;
}
