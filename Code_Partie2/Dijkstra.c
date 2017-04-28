#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"

#define IN 999999999 /* Infinie */

int maxE(int a, int b){
  if (a>b) return a;
  return b;
}

Solu_dij *dijkstra(Graphe *g, int r, int t, int *gamma)
{
    Tas2Clefs *bord;
    int pred[g->nbsom], marque[g->nbsom], chemin[g->nbsom];
    double dist[g->nbsom];
    int start, i, j, ext, gmax = *gamma;
    Cellule_arete *cour;
    Arete *a;
    Solu_dij *Resultat;

    for (i = 1; i <= g->nbsom; i++)
    {
        dist[i] = IN;
        pred[i] = -1;
        marque[i] = 0;
        chemin[i] = -1;
    }

    bord = malloc(sizeof(Tas2Clefs));
    if (!bord)
        exit(0);

    dist[r] = 0;
    insert(bord, r, 0); /* Ajouter r a distance 0 dans Bordure */
    marque[r] = 1;

    while (bord->n != 0)
    {
        start = min(bord)->i;
        suppMin(bord);
        marque[start] = 1;
      
        ///////////////////////////////////////////////////////////////////////////////
        /* Mettre a jour du Bordure */
        cour = g->T_som[start]->L_voisin;
        while (cour)
        {
            if (cour->a->u == start)
                ext = cour->a->v;
            else
                ext = cour->a->u;
            if (marque[ext] == 0)
            {
                if (dist[ext] > (dist[start] + cour->a->longueur))
                {
                    dist[ext] = (dist[start] + cour->a->longueur);
                    pred[ext] = start;
                    insert(bord, ext, dist[ext]);
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
        while (start != r)
        {
            chemin[i] = start;
            start = pred[start];
            i++;
        }
        chemin[i] = r;

        Resultat = malloc(sizeof(Solu_dij));
        Resultat->dist = dist[t];
        Resultat->path = chemin;

        for(j=0; j<i-1; j++){
            a = acces_arete(g, chemin[j], chemin[j+1]);
            if(a!=NULL){
                a->calc_gamma+=1;
                gmax = maxE(gmax, a->calc_gamma);
            }
        }
        *gamma = gmax;

       // printf("\n calcgamma = %d\n", *gamma);
        return Resultat;
    }
    else
        return NULL;
}

double Application_Du_Dij(Graphe *g, int *gamma, FILE *f)
{
    if (!g)
        exit(0);

    int i, j, r, t;
    double longueur = 0;
    Solu_dij *resul;

    for (i = 0; i < g->nbcommod; i++)
    {
        r = g->T_commod[i].e1;
        t = g->T_commod[i].e2;
        resul = dijkstra(g, r, t, gamma);
        if (!resul)
        {
            printf("Il n'existe pas une chaine relieant la commodite %d->%d, une erreur se produite dans la fonction dijkstra!!!!!\n", r, t);
            exit(0);
        }

        longueur += resul->dist;
        
        /* Generation du fichier .nch */
        j=0;
        while(resul->path[j] != -1)
            j++;
    
        for(j=j-1; j>=0; j--){
            fprintf(f, "%d ", resul->path[j]);
        }
        fprintf(f, "-1\n");
    }

    return longueur;
}