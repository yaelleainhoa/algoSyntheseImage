#ifndef __QUADTREE_H
#define __QUADTREE_H

extern int loop;

typedef struct 
{
    int pointNO;//indice de la coordonnée x du point
    int pointNE;
    int pointSO;
    int pointSE;
}Node;

typedef struct Quadtree Quadtree;

struct Quadtree
{
    Node * ptsExt;
    struct Quadtree * enfantNO;
    struct Quadtree * enfantNE;
    struct Quadtree * enfantSO;
    struct Quadtree * enfantSE;
};



Node createNode(int pointNO,int pointNE, int pointSO,int pointSE);
Quadtree createQuadtree(Node *ptsExt);
void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l);
void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);
void inorderTravel(Quadtree * quadtree, Node nodes[], int *nodesCount);

#endif