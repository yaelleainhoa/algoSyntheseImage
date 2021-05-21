#ifndef __QUADTREE_H
#define __QUADTREE_H

#include "geometry.h"
#include "valDeGris.h"

extern int loop;

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
    Node * ptsExt;
    struct Quadtree * enfantNO;
    struct Quadtree * enfantNE;
    struct Quadtree * enfantSO;
    struct Quadtree * enfantSE;
};


Point3D createPointFromCoord(int coord);
Node createNode(Point3D pointNO,Point3D pointNE, Point3D pointSO,Point3D pointSE);
Quadtree createQuadtree(Node *ptsExt);
void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l);
void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);
void inorderTravel(Quadtree * quadtree, Node nodes[], int *nodesCount);
int quadAppartientTriangle(Quadtree* quadtree);//, float xCam, float yCam, float xRegard, float yRegard, float zfar, float fov );
int camIntersectQuad(Quadtree *quadtree);
void travelQuadtree(Node *ptsVisibles[], Quadtree* quadtree, int* ptCount, HeightMap heightMap);
int pointAppartientQuadtree(Quadtree *quadtree, float Px, float Py);
int triangleAppartientQuadtree(Quadtree *quadtree);
#endif