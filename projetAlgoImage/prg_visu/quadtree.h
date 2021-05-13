#ifndef __CREATE_OBJECT_H
#define __CREATE_OBJECT_H


typedef struct
{
    int pointNO;//indice de la coordonnée x du point
    int pointNE;
    int pointSO;
    int pointSE;

    Quadtree * enfantNO;
    Quadtree * enfantNE;
    Quadtree * enfantSO;
    Quadtree * enfantSE;
}Quadtree;

Quadtree createQuatree(int pointNO,int pointNE,int pointSO,int pointSE,Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);
void buildQuadtree(Quadtree * quadtree,float vertex_coord[]);
void addNodeQuadtree(Quadtree quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);
#endif