#ifndef __DIKLSTRA_H__
#define __DIJKSTRA_H__

#include "Parcour_en_largeur.h"

typedef struct{
    double dist;
    Path p;
}Solu_dij;

Path Dijkstra(Graphe *g, int r, int t);   /* r et t est les 2 extremites d'une commodite */

/* Appliquer l'algo dijkstra a chaque instance et generer la fichier .nch a partir de chaque instance */
Path *Application_Du_Dij(Graphe *g);   /* gamma nombre maximum par un cable, f est pour creer les fichiers .ncha */

/*Solu_dij *Dijkstra_Ammerliorer(Graphe *g, int r, )*/



#endif
