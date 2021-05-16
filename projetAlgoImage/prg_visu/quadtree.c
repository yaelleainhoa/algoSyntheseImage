#include "quadtree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TAILLE_PIXELS 1

int loop=0;

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

void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE)
{
    quadtree->enfantNO=enfantNO;
    quadtree->enfantNE=enfantNE;
    quadtree->enfantSO=enfantSO;
    quadtree->enfantSE=enfantSE;
}

void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l)
{
    int NO=quadtree->ptsExt->pointNO;
    int NE=quadtree->ptsExt->pointNE;
    int SO=quadtree->ptsExt->pointSO;
    int SE=quadtree->ptsExt->pointSE;
printf(" (abs(NO-SO): %d\n (abs(NO-NE):%d\n", abs(NO-SO),abs(NO-NE));
    if((abs(NO-NE)==1) || (abs(NO-SO)==w))
    {
        printf("fin\n");
        return;
    }
    else
    {
        //création des enfants

        Node nodeNO= createNode(NO,
                                (int)((NO+NE)/2),
                                (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w),
                                (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2);
        Quadtree quadNO = createQuadtree(&nodeNO);

        Node nodeNE=createNode((int)((NO+NE)/2),
                                NE,
                                (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l/2,
                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +l);       
        Quadtree quadNE = createQuadtree(&nodeNE);

        Node nodeSO=createNode( (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) ,
                                (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2,
                                SO,
                                SO+(int)(l/2));
        Quadtree quadSO = createQuadtree(&nodeSO);

        Node nodeSE =createNode( (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2,
                                (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +l,
                                SO+(int)(l/2),
                                SE);
        Quadtree quadSE = createQuadtree(&nodeSE);

        printf("nodeNE.NO: %d\n", nodeNE.pointNO);
        printf("nodeNE.NE: %d\n", nodeNE.pointNE);
        printf("nodeNE.SE: %d\n", nodeNE.pointSE);
        printf("nodeNE.SO: %d\n", nodeNE.pointSO);

        printf("nodeNO.NO: %d\n", nodeNO.pointNO);
        printf("nodeNO.NE: %d\n", nodeNO.pointNE);
        printf("nodeNO.SE: %d\n", nodeNO.pointSE);
        printf("nodeNO.SO: %d\n", nodeNO.pointSO);

        printf("nodeSE.NO: %d\n", nodeSE.pointNO);
        printf("nodeSE.NE: %d\n", nodeSE.pointNE);
        printf("nodeSE.SE: %d\n", nodeSE.pointSE);
        printf("nodeSE.SO: %d\n", nodeSE.pointSO);

        printf("nodeSO.NO: %d\n", nodeSO.pointNO);
        printf("nodeSO.NE: %d\n", nodeSO.pointNE);
        printf("nodeSO.SE: %d\n", nodeSO.pointSE);
        printf("nodeSO.SO: %d\n", nodeSO.pointSO);

        //ajout des enfants au quadtree
        addChildQuadtree(quadtree,&quadNO,&quadNE,&quadSO,&quadSE);
        //Récursion
        printf("NO\n");
        buildQuadtree(quadtree->enfantNO, vertex_coord,w, (int)(l/2));  
        printf("NE\n");  
        buildQuadtree(quadtree->enfantNE, vertex_coord,w, l-(int)(l/2));
        printf("SO\n");
        buildQuadtree(quadtree->enfantSO, vertex_coord,w,(int)(l/2));
        printf("SE\n");
        buildQuadtree(quadtree->enfantSE, vertex_coord,w,l-(int)(l/2));
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
