#include <stdio.h>
#include <stdlib.h>
#include "Parcour_en_largeur.h"
#include "Struct_File.h"

int maxE(int a, int b){
  if (a>b) return a;
  return b;
}

Path nbarcmin_entre_r_t(Graphe *g, int r, int t){
     Cellule_arete *cour;
     int u, v, i, s;
     int *visit = (int*)malloc((g->nbsom + 1)*sizeof(int));
     int pred[g->nbsom + 1];
     S_file F; Init_file(&F);
     Path p = malloc(sizeof(ElmntPath));
     Path np;
     p->s = -1;
     p->suiv = NULL;

     for(i=1; i<=g->nbsom; i++){
         visit[i] = -1;//le tab pour compter le nombre des arretes pour chaque sommet, en sommant depuis r
         pred[i] = -1;// le sommet pred. du sommet courant
     }
     visit[r] = 0;
     enfile(&F, r);

     while(!(estFileVide(&F))){
         u = defile(&F);
         cour = g->T_som[u]->L_voisin;

         while(cour != NULL){
             if(u == cour->a->u){
                 v = cour->a->v; //le cas ou le vpremier extremite est le voisin, on affaete l'autre extemite a v
             }else v = cour->a->u;//sinon on reprend l'autre extremite et on affacte a v'
             if(visit[v] == -1){ //si le voisin qui est v est a -1 dans le tableau visit alors
                 visit[v] = visit[u] + 1;  //alors on met sur l'indice v dans le tab visit la somme des arretes du sommet precedent + 1 
                 pred[v] = u; //on met le sommet que lon a depile dans le tab des sommets pred.
                 enfile(&F, v);
             }
             cour = cour->suiv;
         }
     }
     
     s = t;//on affecte le chiffre du sommet a s 
     if(visit[t] != -1){
         while(s != -1){
             np = malloc(sizeof(ElmntPath));
             np->s = s;
             np->suiv = p;
             p = np;
             s = pred[s];
         }
        return p;
     }
     else
        return NULL;
}

Path *touverDesChaines(Graphe *g){
    int i, r, t;
    Path *tabp = malloc(sizeof(ElmntPath*)*(g->nbcommod));

    for (i = 0; i < g->nbcommod; i++)
    {
        r = g->T_commod[i].e1;
        t = g->T_commod[i].e2;
        tabp[i] = nbarcmin_entre_r_t(g, r, t);
        if(!tabp[i]){printf("Il n'existe pas une chaine relieant la commodite %d->%d, une erreur peut-etre se produite dans la fonction PARCOURS EN LARGEUR!\n", r, t); exit(0);}
    }

    return tabp;
}
/*On parcours les commodites
et on ajoute +1 au gamma d'un sommet 
que l'on treaverse */
int rechercherGamma(Graphe *g, Path *tabp)
{
    int i, gamma = 0;
    Arete *a;
    ElmntPath *cour;
   
    for (i = 0; i < g->nbcommod; i++)
    {
        cour = tabp[i];
        while ((cour->suiv->s) != -1)
        {
            a = acces_arete(g, cour->s, cour->suiv->s);
            if (a != NULL)
            {
                a->calc_gamma += 1;
                gamma = maxE(gamma, a->calc_gamma);
            }
            cour=cour->suiv;
        }
    }

    return gamma;
}

double distanceTotale(Graphe *g, Path *tabp){
    int i;
    double longueurTotal = 0;
    Arete *a;
    ElmntPath *cour;

    for(i=0; i<g->nbcommod; i++){
        cour = tabp[i];
        while((cour->suiv->s)!=-1){
            a=acces_arete(g, cour->s, cour->suiv->s);
            if(a != NULL) longueurTotal += a->longueur;
            cour = cour->suiv;
        }
    }

    return longueurTotal;
}

void ecrireNch(Graphe *g, Path *tabp, FILE *f)
{
    int i;
    ElmntPath *cour;

    for (i = 0; i < g->nbcommod; i++)
    {
        cour = tabp[i];
        while (cour != NULL){
            fprintf(f, "%d ", cour->s);
            cour = cour->suiv;
        }
        
        fprintf(f, "\n");
    }
}