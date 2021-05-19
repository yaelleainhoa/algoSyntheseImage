#ifndef __QUADTREE_H
#define __QUADTREE_H

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



Node createNode(Point3D pointNO,Point3D pointNE, Point3D pointSO,Point3D pointSE);
Quadtree createQuadtree(Node *ptsExt);
void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l);
void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE);
void inorderTravel(Quadtree * quadtree, Node nodes[], int *nodesCount);
void quadAppartientTriangle(Quadtree* quadtree, float xCam, float yCam, float xRegard, float yRegard );
void camIntersectQuad(Quadtree *quadtree);

#endif