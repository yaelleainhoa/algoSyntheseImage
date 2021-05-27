#ifndef __QUADTREE_H
#define __QUADTREE_H

#include "geometry.h"
#include "valDeGris.h"


extern int loop;
//--------------------Structure------------------------
typedef struct 
{
    Point3D pointNO;
    Point3D pointNE;
    Point3D pointSO;
    Point3D pointSE;
}Node;

typedef struct Quadtree Quadtree;

struct Quadtree
{
    Node ptsExt;
    struct Quadtree * enfantNO;
    struct Quadtree * enfantNE;
    struct Quadtree * enfantSO;
    struct Quadtree * enfantSE;
};

//----------------------------------------------------------

//-------------Initialisations------------------------------

Node createNode(Point3D pointNO,Point3D pointNE, Point3D pointSO,Point3D pointSE);
Quadtree createQuadtree(Node *ptsExt);
void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l);
void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);

//-----------------------------------------------------------

//--------Fonctions pour le parcours du quadtree-------------
int quadAppartientTriangle(Node node);
int camIntersectQuad(Quadtree *quadtree);
int pointAppartientQuadtree(Node node, float Px, float Py);
int triangleAppartientQuadtree(Node node);

void travelQuadtree(Node ptsVisibles[], Quadtree quadtree, int* ptCount);

//fonction pour tester
void printNode(Node node);


#endif