#include <stdio.h>
#include <stdlib.h>
#include "Struct_Tas.h"

Element *min(Tas2Clefs *t){
    return t->H[racine()];
}

void insert(Tas2Clefs *t, int i, double c){
    Element *nE = malloc(sizeof(Element));
    if(!nE) exit(0);

    nE->i = i;
    nE->c = c;
    t->n++;
    t->H[t->n]=nE;
    t->A[i] = t->n;
    monter(t, t->n);
}

void suppMin(Tas2Clefs *t){
    echanger(t, t->n, racine());
    t->n--;
    decendre(t, racine());
}

int estPresenter(Tas2Clefs *t, int i){
    if(t->A[i] == -1) return 0;
    return (t->A[i] <= t->n);
 }

void suppElemt(Tas2Clefs *t, int i){
    if(estPresenter(t, i) == 0) return;
    echanger(t, t->n, t->A[i]);
    t->n--;
    decendre(t, racine());
}

void echanger(Tas2Clefs *t, int i, int j){
    Element *tmp = t->H[i];
    int tmpi = t->A[t->H[i]->i];
    t->A[t->H[i]->i] = t->A[t->H[j]->i];
    t->A[t->H[j]->i] = tmpi;
    t->H[i] = t->H[j];
    t->H[j] = tmp;
}

void monter(Tas2Clefs *t, int i){
    if(!hasPere(i)) return;

    int papa = pere(i);
    if(t->H[papa]->c > t->H[i]->c){
        echanger(t, i, papa);
        monter(t, papa);
    }
}

void descendre(Tas2clefs *t, int i){
    if(!(filsGauche(i) <= t->n)) return;

    int fiston = plusPetitFils(t, i);
    if(t->H[i]->c > t->H[fiston]->c){
        echanger(t, fiston, i);
        descendre(t, fiston);
    }
}

int plusPetitFils(Tas2clefs *t, int i){
    if(!(filsDroit(i) <= t->n)) return filsGauche(i);

    int fg = filsGauche(i);
    int fd = filsDroit(i);
    return (t->H[fg]->c < t->H[fd]->c)?fg:fd;
}

int racine(){
    return 1;
}

int hasPere(int i){
    return i != racine();
}

int filsGauche(int i){
    return (2 * i);
}

int filsDroit(int i){
    return (2 * i +1);
}

int pere(int i){
    return (i/2);
}