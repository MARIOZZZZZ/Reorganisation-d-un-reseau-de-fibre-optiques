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
  Path *tabp;

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
 
  /* Selection de l'algorithme de recherche */
  if(chmeth == 1){
    tabp = touverDesChaines(&G);
  }else if(chmeth == 2){
    tabp = Application_Du_Dij(&G);
  }else{
    printf("Algo inconnu, numeromethode = 1 if using Width firs search; 2 if using algorithme dijkstra\n");
    exit(0);
  }

  
  ecrireNch(&G, tabp, f2);  
  fclose(f2);

  longueur = distanceTotale(&G, tabp);
  gamma = rechercherGamma(&G, tabp);
  eval = evaluation_NChaines(gamma, longueur, argv[1]);
  
  printf("Instance = %s, Evaluation = %.2f, gamma = %d, distance = %.2f\n", argv[1], eval, gamma, longueur);

  return 0;
}
