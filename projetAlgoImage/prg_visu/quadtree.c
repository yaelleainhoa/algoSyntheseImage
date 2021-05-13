#include "quadtree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_PIXELS 1;

Quadtree createQuadtree(int pointNO, int pointNE, int pointSO,int pointSE)
{
    Quadtree newQuadtree;

    newQuadtree.pointNO=pointNO;
    newQuadtree.pointNE=pointNE;
    newQuadtree.pointSO=pointSO;
    newQuadtree.pointSE=pointSE;

    newQuadtree.enfantNO=NULL;
    newQuadtree.enfantNE=NULL;
    newQuadtree.enfantSO=NULL;
    newQuadtree.enfantSE=NULL;
    
    return newQuadtree;
}

void addNodeQuadtree(Quadtree quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE)
{
    quadtree.enfantNO=enfantNO;
    quadtree.enfantNE=enfantNE;
    quadtree.enfantSO=enfantSO;
    quadtree.enfantSE=enfantSE;
}


void buildQuadtree(Quadtree * quadtree,float vertex_coord[])
{
    if(vertex_coord[quadtree->pointNO]-vertex_coord[quadtree->pointNE] /*difference des x*/==TAILLE_PIXELS 
        || vertex_coord[pointNO+1]-vertex_coord[pointSO+1]==TAILLE_PIXELS)
    {
        return;
    }
    else()
    {
        //création des enfants
        Quadtree *NO = createQuadtree(quadtree.pointNO,
                                    (int)((quadtree.pointNO+quadtree.pointNE)/2),
                                    int)((quadtree.pointNO+quadtree.poinSO)/2),
                                    (int)(quadtree.pointNO+quadtree.pointNE+quadtree.pointSE+quadtree.pointSO)/4));
        Quadtree *NE = createQuadtree((int)((quadtree.pointNO+quadtree.pointNE)/2),
                                    quadtree.pointNE, 
                                    (int)((quadtree.pointNO+quadtree.pointNE+quadtree.pointSE+quadtree.pointSO)/4),
                                    (int)((quadtree.pointNE+quadtree.poinSE)/2));
        Quadtree *SO = createQuadtree((int)((quadtree.pointNO+quadtree.pointSO)/2),
                                    (int)((quadtree.pointNO+quadtree.pointNE+quadtree.pointSE+quadtree.pointSO)/4),
                                    quadtree.pointSO,
                                    (int)((quadtree.pointSO+quadtree.poinSE)/2));
        Quadtree *SE = createQuadtree((int)((quadtree.pointNO+quadtree.pointNE+quadtree.pointSE+quadtree.pointSO)/4),
                                    (int)((quadtree.pointNE+quadtree.pointSE)/2),
                                    (int)((quadtree.pointSO+poinSE)/2),
                                    quadtree.pointSE);

        //ajout des enfants au quadtree
        addNodeQuadtree(quadtree,NO,NE,SO,SE);
        //Récursion
        buildQuadtree(quadtree->enfantNO, vertex_coord);
        buildQuadtree(quadtree->enfantNE, vertex_coord);
        buildQuadtree(quadtree->enfantSO, vertex_coord);
        buildQuadtree(quadtree->enfantSE, vertex_coord);
    }
}