#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Dijkstra.h"
#include "Struct_Tas.h"
#include "Parcour_en_largeur.h"

#define IN 9999999999 /* Infinie */

Path dijkstra(Graphe *g, int r, int t)
{
    Tas2Clefs *bord;
    int pred[g->nbsom + 1], marque[g->nbsom + 1];
    double dist[g->nbsom + 1];
    int start, i, j, ext;
    Cellule_arete *cour;
    Arete *a;
    Path p = (ElmntPath *)malloc(sizeof(ElmntPath));
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
    if (!bord)
    {
        printf("Ereur de allocation du tas\n");
        exit(0);
    }
    bord->n = 0;
    for (i = 0; i < CAPACITE_MAX; i++)
    {
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
    if (marque[t] != 0)
    {
        while (start != -1)
        {
            np = malloc(sizeof(ElmntPath));
            np->s = start;
            np->suiv = p;
            p = np;
            start = pred[start];
        }
        return p;
    }
    else
        return NULL;
}

Path *Application_Du_Dij(Graphe *g)
{
    if (!g)
        exit(0);

    int i, j, r, t;
    Path *tabp = malloc(sizeof(ElmntPath *) * (g->nbcommod));

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

double fonctionCout(Graphe *G, double g, int t, int courant)
{
    double f, h;

    h = sqrt((G->T_som[t]->x - G->T_som[courant]->x) * (G->T_som[t]->x - G->T_som[courant]->x) + (G->T_som[t]->y - G->T_som[courant]->y) * (G->T_som[t]->y - G->T_som[courant]->y));
    f = g + h;
    return f;
}

Path AlgoA(Graphe *g, int r, int t)
{
    Tas2Clefs *tas;
    int pred[g->nbsom], dist[g->nbsom], marque[g->nbsom];
    int i, v, ext, start;
    Path p;
    Arete *a;
    Cellule_arete *cour;

    p = (ElmntPath *)malloc(sizeof(ElmntPath));
    Path np;
    p->s = -1;
    p->suiv = NULL;

    for (i = 0; i < g->nbsom; i++)
    {
        pred[i] = -1;
        dist[i] = -1;
        marque[i] = 0;
    }

    tas = malloc(sizeof(Tas2Clefs));
    if (!t)
    {
        printf("Erreur d'allocation du tas\n");
        exit(0);
    }
    for (i = 0; i < CAPACITE_MAX; i++)
    {
        tas->H[i] = NULL;
        tas->A[i] = -1;
    }
    tas->n = 0;

    dist[r] = 0;

    insert(tas, r, fonctionCout(g, dist[r], t, r));

    while (v != t)
    {
        printf("v=%d\n",v);
        v = min(tas)->i;

        marque[v] = 1;
        suppMin(tas);

        cour = g->T_som[v]->L_voisin;
        while (cour)
        {
            if (v == cour->a->v)
                ext = cour->a->u;
            else
                ext = cour->a->v;

            if (marque[ext] == 0)
            {
                printf("ext = %d\n", ext);
                insert(tas, ext, fonctionCout(g, dist[v], t, ext));
                pred[ext] = v;
                a = acces_arete(g, v, ext);
                if (!a)
                    printf("Oups!! pas bon!!\n");
                dist[ext] = dist[v] + a->longueur;
            }
            cour = cour->suiv;
        }
    }

    start = t;
    if (marque[t] != 0)
    {
        while (start != -1)
        {
            np = malloc(sizeof(ElmntPath));
            np->s = start;
            np->suiv = p;
            p = np;
            start = pred[start];
        }
        return p;
    }
    else
        return NULL;
}

Path *Application_Du_A(Graphe *g)
{
    if (!g)
        exit(0);

    int i, j, r, t;
    Path *tabp = malloc(sizeof(ElmntPath *) * (g->nbcommod));

    for (i = 0; i < g->nbcommod; i++)
    {

        r = g->T_commod[i].e1;
        t = g->T_commod[i].e2;
        tabp[i] = AlgoA(g, r, t);
        if (!tabp[i])
        {
            printf("Il n'existe pas une chaine relieant la commodite %d->%d, une erreur se produite dans la fonction dijkstra!!!!!\n", r, t);
            exit(0);
        }
    }

    return tabp;
}
