#ifndef __DIKLSTRA_H__
#define __DIJKSTRA_H__

#include "Struct_Tas.h"
#include "Graphe.h"

typedef struct{
    double dist;
    int *path;
}Solu_dij;

Solu_dij *Dijkstra(Graphe *g, int r, int t, int *gamma);   /* r et t est les 2 extremites d'une commodite */

/* Appliquer l'algo dijkstra a chaque instance et generer la fichier .nch a partir de chaque instance */
double Application_Du_Dij(Graphe *g, int *gamma, FILE *f);   /* gamma nombre maximum par un cable, f est pour creer les fichiers .ncha */



#endif
