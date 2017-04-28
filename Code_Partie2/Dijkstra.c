#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"

#define IN 9999999999  /* Infinie */

Solu_dij* dijkstra(Graphe *g, int r, int t){
    Tas2Clefs *bord;
    int pred[g->nbsom], marque[g->nbsom], chemin[g->nbsom];
    double dist[g->nbsom];
    int start, i;
    Cellule_arete *cour;

    for(i=1; i<=g->nbsom; i++)
    {
        dist[i] = IN;
        pred[i] = -1;
        marque[i] = 0;
        chemin[i] = -1;
    }

    bord = malloc(sizeof(Tas2Clefs));
    if(!bord) exit(0);

    dist[r] = 0;
    insert(bord, r, 0);     /* Ajouter r a distance 0 dans Bordure */
    marque[r] = 1;

    while (bord->n != 0)
    {
        start = min(bord);
        suppMin(bord);
        marque[start] = 1;
       ///////////////////////////////////////////////////////////////////////////////
       /* Mettre a jour du Bordure */
       cour = g->T_som[start]->L_voisin;
       while(cour){
           if (marque[cour->a->v] == 0)
           {
               if (dist[cour->a->v] > (dist[start] + cour->a->longueur))
               {
                   dist[cour->a->v] = (dist[start] + cour->a->longueur);
                   pred[cour->a->v] = start;
                   insert(bord, cour->a->v, dist[cour->a->v]);
               }
           }
           cour = cour->suiv;
       }
       ///////////////////////////////////////////////////////////////////////////////
    }

    start = t;
    i = 0;
    if (marque[start] != 0)
    {
        chemin[i] = start;
        i += 1;
    }
    while (pred[start] != -1)
    {
        chemin[i] = pred[start];
        start = pred[start];
        i++;
    }

    Resultat = malloc(sizeof(Solu_dij));
    Resultat->dist = dist[t];
    Resultat->path = chemin;

    return Resultat;
 }