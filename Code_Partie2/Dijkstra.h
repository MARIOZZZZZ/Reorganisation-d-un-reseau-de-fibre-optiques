#ifndef __DIKLSTRA_H__
#define __DIJKSTRA_H__

#include "Struct_Tas.h"
#include "Graphe.h"

typedef struct{
    double dist;
    int *path;
}Solu_dij;

Solu_dij *Dijkstra(Graphe *g, int r, int t);



#endif
