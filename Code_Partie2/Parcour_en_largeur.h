#ifndef _PARCOUR_EN_LARGEUR_H
#define _PARCOUR_EN_LARGEUR_H

#include "Graphe.h"

typedef struct element{
    int s;
    struct element *suiv;
} ElmntPath;

typedef ElmntPath* Path;

int maxE(int a, int b);
Path nbarcmin_entre_r_t(Graphe *g, int r, int t);
Path *touverDesChaines(Graphe *g);
int rechercherGamma(Graphe *g, Path *tabp);
double distanceTotale(Graphe *g, Path *tabp);
void ecrireNch(Graphe *g, Path *tabp, FILE *f);
#endif