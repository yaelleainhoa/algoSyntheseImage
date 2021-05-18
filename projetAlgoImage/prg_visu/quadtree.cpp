#include "quadtree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus

extern "C"{

#define TAILLE_PIXELS 1

Node createNode(int pointNO,int pointNE, int pointSO,int pointSE)
{
    Node newNode;

    newNode.pointNO=pointNO;
    newNode.pointNE=pointNE;
    newNode.pointSO=pointSO;
    newNode.pointSE=pointSE;

    return newNode;
}

Quadtree createQuadtree(Node* ptsExt)
{
    Quadtree newQuadtree;

    newQuadtree.ptsExt=ptsExt;

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


void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int w)
{
    if((abs(quadtree->ptsExt->pointNO-quadtree->ptsExt->pointNE)==1) || 
        (abs(quadtree->ptsExt->pointNO+1-quadtree->ptsExt->pointSO+1)==w))
    {
        printf("%f vertex_coord[pointNE]",vertex_coord[quadtree->ptsExt->pointNE]);

        return;
    }
    else
    {
        //création des enfants
        Node nodeNO= createNode(quadtree->ptsExt->pointNO,
                                (int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE)/2),
                                (int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointSO)/2),
                                (int)(quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE+quadtree->ptsExt->pointSO)/4);
        Quadtree NO = createQuadtree(&nodeNO);

        Node nodeNE=createNode((int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE)/2),
                                quadtree->ptsExt->pointNE, 
                                (int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE+quadtree->ptsExt->pointSO)/4),
                                (int)((quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE)/2));                
        Quadtree NE = createQuadtree(&nodeNE);

        Node nodeSO=createNode((int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointSO)/2),
                                (int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE+quadtree->ptsExt->pointSO)/4),
                                quadtree->ptsExt->pointSO,
                                (int)((quadtree->ptsExt->pointSO+quadtree->ptsExt->pointSE)/2));
        Quadtree SO = createQuadtree(&nodeSO);

        Node nodeSE =createNode((int)((quadtree->ptsExt->pointNO+quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE+quadtree->ptsExt->pointSO)/4),
                                (int)((quadtree->ptsExt->pointNE+quadtree->ptsExt->pointSE)/2),
                                (int)((quadtree->ptsExt->pointSO+quadtree->ptsExt->pointSE)/2),
                                quadtree->ptsExt->pointSE);
        Quadtree SE = createQuadtree(&nodeSE);

        printf("nodeNO: %d", nodeNE.pointNE);

        //ajout des enfants au quadtree
        addNodeQuadtree(*quadtree,&NO,&NE,&SO,&SE);
        //Récursion
        buildQuadtree(quadtree->enfantNO, vertex_coord, (int)(w/2));     
        buildQuadtree(quadtree->enfantNE, vertex_coord, w-(int)(w/2));
        buildQuadtree(quadtree->enfantSO, vertex_coord,w);
        buildQuadtree(quadtree->enfantSE, vertex_coord,w-(int)(w/2));
    }
}


void inorderTravel(Quadtree * quadtree, Node* nodes[], int nodesCount) {
    // fill nodes array with all nodes with inorder travel
    nodes[nodesCount]=quadtree->ptsExt;
    nodesCount++;
    if(quadtree->enfantNE)
    {
        inorderTravel(quadtree->enfantNE,nodes,nodesCount);
    }
    if(quadtree->enfantNO)
    {
        inorderTravel(quadtree->enfantNO,nodes,nodesCount);
    }
        if(quadtree->enfantSE)
    {
        inorderTravel(quadtree->enfantSE,nodes,nodesCount);
    }
        if(quadtree->enfantSO)
    {
        inorderTravel(quadtree->enfantSO,nodes,nodesCount);
    }
}
}
#endif