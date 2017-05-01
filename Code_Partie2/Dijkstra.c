#include <stdio.h>
#include <stdlib.h>
#include "Dijkstra.h"
#include "Struct_Tas.h"
#include "Parcour_en_largeur.h"

#define IN 9999999999 /* Infinie */

Path dijkstra(Graphe *g, int r, int t)
{
    Tas2Clefs *bord;
    int pred[g->nbsom+1], marque[g->nbsom+1];
    double dist[g->nbsom+1];
    int start, i, j, ext;
    Cellule_arete *cour;
    Arete *a;
    Path p = (ElmntPath*)malloc(sizeof(ElmntPath));
    Path np;
    p->s = -1;
    p->suiv = NULL;

    for (i = 1; i <= g->nbsom; i++)
    {
        dist[i] = IN;
        pred[i] = -1;
        marque[i] = 0;
    }

    bord = malloc(sizeof(Tas2Clefs));
    if (!bord){
        printf("Ereur de allocation du tas\n");
        exit(0);
    }
    bord->n = 0;
    for(i=0; i<CAPACITE_MAX; i++){
        bord->H[i] = NULL;
        bord->A[i] = -1;
    }

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
    if(marque[t] != 0){
        while(start != -1){
            np = malloc(sizeof(ElmntPath));
            np->s=start;
            np->suiv = p;
            p = np;
            start = pred[start];
        }
        return p;
    }
    else return NULL;

}

Path *Application_Du_Dij(Graphe *g)
{
    if (!g)
        exit(0);

    int i, j, r, t;
    Path *tabp =malloc(sizeof(ElmntPath*)*(g->nbcommod));
   
    for (i = 0; i < g->nbcommod; i++)
    {

        r = g->T_commod[i].e1;
        t = g->T_commod[i].e2;
        tabp[i] = dijkstra(g, r, t);
        if (!tabp[i])
        {
            printf("Il n'existe pas une chaine relieant la commodite %d->%d, une erreur se produite dans la fonction dijkstra!!!!!\n", r, t);
            exit(0);
        }
    }

    return tabp;
}