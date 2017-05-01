#ifndef _STRUCT_TAS_H
#define _STRUCT_TAS_H

#define CAPACITE_MAX 10000

typedef struct
{
    int i;
    double c;
} Element;

typedef struct
{
    int n;
    Element *H[CAPACITE_MAX];
    int A[CAPACITE_MAX];
} Tas2Clefs;

/* Fonctions de manipulation du tas */
Element *min(Tas2Clefs *t);
void insert(Tas2Clefs *t, int i, double c);
void suppMin(Tas2Clefs *t);
int estPresenter(Tas2Clefs *t, int i);
void suppElemt(Tas2Clefs *t, int i);

/* Fonctions du tas */
void echanger(Tas2Clefs *t, int i, int j);
void monter(Tas2Clefs *t, int i);
void descendre(Tas2Clefs *t, int i);
int plusPetitFils(Tas2Clefs *t, int i);
int racine();
int hasPere(int i);
int filsGauche(int i);
int filsDroit(int i);
int pere(int i);
#endif
