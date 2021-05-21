#include "quadtree.h"
#include "geometry.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "visu.h"
#include "create_object.h"


#define TAILLE_PIXELS 1

int loop=0;

Point3D createPointFromCoord(int coord){
    Point3D newPoint;
    newPoint.x=vertex_coord[3*coord];
    newPoint.y=vertex_coord[3*coord+1];
    newPoint.z=vertex_coord[3*coord+2];
    newPoint.coord=coord;
    return newPoint;
}

Node createNode(Point3D pointNO,Point3D pointNE, Point3D pointSO,Point3D pointSE)
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
    int NO=quadtree->ptsExt->pointNO.coord;
    int NE=quadtree->ptsExt->pointNE.coord;
    int SO=quadtree->ptsExt->pointSO.coord;
    int SE=quadtree->ptsExt->pointSE.coord;
printf(" (abs(NO-SO): %d\n (abs(NO-NE):%d\n", abs(NO-SO),abs(NO-NE));
    if((abs(NO-NE)==1) || (abs(NO-SO)==w))
    {
        printf("fin\n");
        return;
    }
    else
    {
        //création des enfants

        Point3D NO_NO=createPointFromCoord(NO);
        Point3D NO_NE=createPointFromCoord((int)((NO+NE)/2));
        Point3D NO_SO=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w));
        Point3D NO_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2);
        Point3D NE_NE=createPointFromCoord(NE);
        Point3D NE_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +l);
        Point3D SO_SO=createPointFromCoord(SO);
        Point3D SO_SE=createPointFromCoord(SO+(int)(l/2));
        Point3D SE_SE=createPointFromCoord(SE);

        Node nodeNO= createNode(NO_NO,
                                NO_NE,
                                NO_SO,
                                NO_SE);
        Quadtree quadNO = createQuadtree(&nodeNO);

        Node nodeNE=createNode(NO_NE,
                                NE_NE,
                                NO_SE,
                                NE_SE);       
        Quadtree quadNE = createQuadtree(&nodeNE);

        Node nodeSO=createNode( NO_SO ,
                                NO_SE,
                                SO_SO,
                                SO_SE);
        Quadtree quadSO = createQuadtree(&nodeSO);

        Node nodeSE =createNode( NO_SE,
                                NE_SE,
                                SO_SE,
                                SE_SE);
        Quadtree quadSE = createQuadtree(&nodeSE);

        printf("nodeNE.NO: %d\n", nodeNE.pointNO.coord);
        printf("nodeNE.NE: %d\n", nodeNE.pointNE.coord);
        printf("nodeNE.SE: %d\n", nodeNE.pointSE.coord);
        printf("nodeNE.SO: %d\n", nodeNE.pointSO.coord);

        printf("nodeNO.NO: %d\n", nodeNO.pointNO.coord);
        printf("nodeNO.NE: %d\n", nodeNO.pointNE.coord);
        printf("nodeNO.SE: %d\n", nodeNO.pointSE.coord);
        printf("nodeNO.SO: %d\n", nodeNO.pointSO.coord);

        printf("nodeSE.NO: %d\n", nodeSE.pointNO.coord);
        printf("nodeSE.NE: %d\n", nodeSE.pointNE.coord);
        printf("nodeSE.SE: %d\n", nodeSE.pointSE.coord);
        printf("nodeSE.SO: %d\n", nodeSE.pointSO.coord);

        printf("nodeSO.NO: %d\n", nodeSO.pointNO.coord);
        printf("nodeSO.NE: %d\n", nodeSO.pointNE.coord);
        printf("nodeSO.SE: %d\n", nodeSO.pointSE.coord);
        printf("nodeSO.SO: %d\n", nodeSO.pointSO.coord);

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

//fonction qui regarde si un des points du quadtree est dans le triangle de la camera: 1 si oui 0 sinon
int quadAppartientTriangle(Quadtree* quadtree/*, float xCam, float yCam, float xRegard, float yRegard, float zfar, float fov*/ )
{
    Point3D NO=quadtree->ptsExt->pointNO;
    Point3D NE=quadtree->ptsExt->pointNE;
    Point3D SO=quadtree->ptsExt->pointSO;
    Point3D SE=quadtree->ptsExt->pointSE;

    if(pointAppartientTriangle(NO.x, NO.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(NE.x, NE.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(SO.x, SO.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(SE.x, SE.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov)*/))
    {
        return 1;
    }
    return 0;
}

//fonction qui regarde si un des sommets du triangle de la camera est dans le quadtree: 1 si oui 0 sinon
//a faire

int triangleAppartientQuadtree(Quadtree *quadtree){

    Point3D NO=quadtree->ptsExt->pointNO;
    Point3D NE=quadtree->ptsExt->pointNE;
    Point3D SO=quadtree->ptsExt->pointSO;
    Point3D SE=quadtree->ptsExt->pointSE;

    float xRegard2D = sin(longitude)+xCam;
    float yRegard2D = cos(longitude)+yCam;
    Point3D cam= createPoint(xCam,yCam,0.,0);
    Point3D direction_regard = createPoint(xRegard2D,yRegard2D,0.,0);

    Vector3D direction=normalize(createVectorFromPoints(cam,direction_regard));
    Vector3D R=createVector(cos(longitude-M_PI/2), sin(longitude-M_PI/2),0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(fov/2.)*zfar));
    Vector3D BC=multVector(multVector(R, tan(fov/2.)*zfar), -2.);
    //Vector3D CA=addVectors(multVector(direction, -zfar), multVector(R, tan(fov/2.)*zfar));

    Point3D B=createPoint(AB.x+cam.x, AB.y+cam.y, 0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y, 0.,0);

    if(pointAppartientQuadtree(quadtree, cam.x, cam.y)
    ||pointAppartientQuadtree(quadtree, B.x, B.y)
    ||pointAppartientQuadtree(quadtree, C.x, C.y))
    {
        return 1;
    }
    return 0;
}

//fonction qui regarde si un des vect du triangle de la cam intersect un des vecteurs des contours du quadtree
int camIntersectQuad(Quadtree *quadtree)
{
    Point3D NO=quadtree->ptsExt->pointNO;
    Point3D NE=quadtree->ptsExt->pointNE;
    Point3D SO=quadtree->ptsExt->pointSO;
    Point3D SE=quadtree->ptsExt->pointSE;

    //points exterieurs triangle caméra
    float xRegard2D = sin(longitude)+xCam;
    float yRegard2D = cos(longitude)+yCam;
    Point3D cam= createPoint(xCam,yCam,0.,0);
    Point3D direction_regard = createPoint(xRegard2D,yRegard2D,0.,0);

    Vector3D direction=normalize(createVectorFromPoints(cam,direction_regard));
    Vector3D R=createVector(cos(longitude-M_PI/2), sin(longitude-M_PI/2),0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(fov/2.)*zfar));
    Vector3D BC=multVector(multVector(R, tan(fov/2.)*zfar), -2.);
    //Vector3D CA=addVectors(multVector(direction, -zfar), multVector(R, tan(fov/2.)*zfar));

    Point3D B=createPoint(AB.x+cam.x, AB.y+cam.y, 0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y, 0.,0);

    //test  
        // vecteur AB  du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
        return 1; 
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
        return 1;
    }

        // vecteur BC du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
        return 1;
    }

        // vecteur AC du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
        return 1;
    }

    return 0;
}
//AVEC LOD

//fonction qui effectue les differents test tout au long de l'arbre
//renvoie la liste des coordonnées des points qui sont visibles

void travelQuadtree(Node *ptsVisibles[], Quadtree* quadtree, int *ptCount, HeightMap heightMap)
{
    if(quadtree->enfantNO)
    {
        if(quadAppartientTriangle(quadtree->enfantNO) || camIntersectQuad(quadtree->enfantNO) || triangleAppartientQuadtree(quadtree->enfantNO))
        {
            float distNO=distance(quadtree->enfantNO->ptsExt->pointNO);
            float distSO=distance(quadtree->enfantNO->ptsExt->pointSO);
            float distSE=distance(quadtree->enfantNO->ptsExt->pointSE);
            float distNE=distance(quadtree->enfantNO->ptsExt->pointNE);
            int distMin = min(min(distNO,distNE),min(distSO,distSE));
            if(distMin>(2*heightMap.w/(quadtree->enfantNO->ptsExt->pointNO.x - quadtree->enfantNO->ptsExt->pointNE.x)))
            {
                ptsVisibles[*ptCount]=quadtree->enfantNO->ptsExt;
                (*ptCount)++;
                return;
            }
            else
            {
                travelQuadtree(ptsVisibles, quadtree->enfantNO,ptCount,heightMap);
            }
        }
    }

    if(quadtree->enfantNE)
    {
        if(quadAppartientTriangle(quadtree->enfantNE) || camIntersectQuad(quadtree->enfantNE) || triangleAppartientQuadtree(quadtree->enfantNE))
        {
            float distNO=distance(quadtree->enfantNE->ptsExt->pointNO);
            float distSO=distance(quadtree->enfantNE->ptsExt->pointSO);
            float distSE=distance(quadtree->enfantNE->ptsExt->pointSE);
            float distNE=distance(quadtree->enfantNE->ptsExt->pointNE);
            int distMin = min(min(distNO,distNE),min(distSO,distSE));
            if(distMin>(2*heightMap.w/(quadtree->enfantNE->ptsExt->pointNO.x - quadtree->enfantNE->ptsExt->pointNE.x)))
            {
                ptsVisibles[*ptCount]=quadtree->enfantNE->ptsExt;
                (*ptCount)++;
                return;
            }
            else
            {
                travelQuadtree(ptsVisibles, quadtree->enfantNE,ptCount,heightMap);
            }
        }
    }

    if(quadtree->enfantSO)
    {
        if(quadAppartientTriangle(quadtree->enfantSO) || camIntersectQuad(quadtree->enfantSO)||  triangleAppartientQuadtree(quadtree->enfantSO))
        {
            float distNO=distance(quadtree->enfantSO->ptsExt->pointNO);
            float distSO=distance(quadtree->enfantSO->ptsExt->pointSO);
            float distSE=distance(quadtree->enfantSO->ptsExt->pointSE);
            float distNE=distance(quadtree->enfantSO->ptsExt->pointNE);
            int distMin = min(min(distNO,distNE),min(distSO,distSE));
            if(distMin>(2*heightMap.w/(quadtree->enfantSO->ptsExt->pointNO.x - quadtree->enfantSO->ptsExt->pointNE.x)))
            {
                ptsVisibles[*ptCount]=quadtree->enfantSO->ptsExt;
                (*ptCount)++;
                return;
            }
            else
            {
                travelQuadtree(ptsVisibles, quadtree->enfantSO,ptCount,heightMap);
            }
        }
    }

    if(quadtree->enfantSE)
    {
        if(quadAppartientTriangle(quadtree->enfantSE) || camIntersectQuad(quadtree->enfantSE) || triangleAppartientQuadtree(quadtree->enfantSE))
        {
            float distNO=distance(quadtree->enfantSE->ptsExt->pointNO);
            float distSO=distance(quadtree->enfantSE->ptsExt->pointSO);
            float distSE=distance(quadtree->enfantSE->ptsExt->pointSE);
            float distNE=distance(quadtree->enfantSE->ptsExt->pointNE);
            int distMin = min(min(distNO,distNE),min(distSO,distSE));
            if(distMin>(2*heightMap.w/(quadtree->enfantSE->ptsExt->pointNO.x - quadtree->enfantSE->ptsExt->pointNE.x)))
            {
                ptsVisibles[*ptCount]=quadtree->enfantSE->ptsExt;
                (*ptCount)++;
                return;
            }
            else
            {
                travelQuadtree(ptsVisibles, quadtree->enfantSE,ptCount,heightMap);
            }
        }
    }

    else //si on rentre la c'est que le quadtree est une feuille
    {
        ptsVisibles[*ptCount]=quadtree->ptsExt;
        (*ptCount)++;
        return;
    }
}


//SANS LOD
/*
//fonction qui effectue les differents test tout au long de l'arbre
//renvoie la liste des coordonnées des points qui sont visibles

void travelQuadtree(Node *ptsVisibles[], Quadtree* quadtree, int ptCount )
{
    if(quadtree->enfantNO)
    {
        if(quadAppartientTriangle(quadtree->enfantNO) || camIntersectQuad(quadtree->enfantNO) || triangleAppartientQuadtree(quadtree->enfantNO))
        {
            travelQuadtree(ptsVisibles, quadtree->enfantNO,ptCount);
        }
    }

    if(quadtree->enfantNE)
    {
        if(quadAppartientTriangle(quadtree->enfantNE) || camIntersectQuad(quadtree->enfantNE) || triangleAppartientQuadtree(quadtree->enfantNE))
        {
            travelQuadtree(ptsVisibles, quadtree->enfantNE,ptCount);
        }
    }

    if(quadtree->enfantSO)
    {
        if(quadAppartientTriangle(quadtree->enfantSO) || camIntersectQuad(quadtree->enfantSO)||  triangleAppartientQuadtree(quadtree->enfantSO))
        {
            travelQuadtree(ptsVisibles, quadtree->enfantSO,ptCount);
        }
    }

    if(quadtree->enfantSE)
    {
        if(quadAppartientTriangle(quadtree->enfantSE) || camIntersectQuad(quadtree->enfantSE) || triangleAppartientQuadtree(quadtree->enfantSE))
        {
            travelQuadtree(ptsVisibles, quadtree->enfantSE,ptCount);
        }
    }

    else //si on rentre la c'est que le quadtree est une feuille
    {
        ptsVisibles[ptCount]=quadtree->ptsExt;
        ptCount++;
    }
}
*/



//fonction qui effectue les differents test tout au long de l'arbre
//renvoie la liste des coordonnées des points qui sont visibles (moins lourds que les poins entiers mais à voir ce qui est mieux)

// void travelQuadtree(int ptsVisibles[], Quadtree* quadtree )
// {
//     if()
// }


//archives
/*
//stand by
void inorderTravel(Quadtree * quadtree, Node nodes[], int * nodesCount) {
    // fill nodes array with all nodes with inorder travel
    printf("count : %d \n",*nodesCount);
    printf("test %d\n", quadtree->enfantNE->ptsExt->pointSO);
    nodes[*nodesCount]=*(quadtree->ptsExt);
        printf("TRAVEL : NO: %d ,NE:%d, SO:%d,SE:%d, count :%d\n" ,
		nodes[*nodesCount].pointNO,
		nodes[*nodesCount].pointNE,
		nodes[*nodesCount].pointSO,
		nodes[*nodesCount].pointSE,
        *nodesCount);
    (*nodesCount)++;
    if(quadtree->enfantNE)
    {
        printf("NE\n");
        inorderTravel(quadtree->enfantNE,nodes,nodesCount);
    }
    if(quadtree->enfantNO)
    {
        printf("N0\n");
        inorderTravel(quadtree->enfantNO,nodes,nodesCount);
    }
        if(quadtree->enfantSE)
    {
        printf("SE\n");
        inorderTravel(quadtree->enfantSE,nodes,nodesCount);
    }
        if(quadtree->enfantSO)
    {
        printf("S0\n");
        inorderTravel(quadtree->enfantSO,nodes,nodesCount);
    }
}





// void camIntersectQuad(Quadtree *quadtree)
// {
//     //points exterieurs triangle caméra
//     float xRegard = sin(longitude)*sin(latitude)+xCam;
//     float yRegard = cos(longitude)*sin(latitude)+yCam;
//     Point3D cam= createPoint(xCam,yCam,0.,0L);
//     Point3D direction_regard = createPoint(xRegard,yRegard,0.,0);

//     Vector3D direction=normalize(createVectorFromPoints(cam,direction_regard));
//     Vector3D R= createVector(cos((M_PI/180)*longitude-M_PI/2),sin((M_PI/180)*longitude-M_PI/2),0.,0);
//     Vector3D AB = addVectors(multVector(direction,zfar),multVector(R,tan((M_PI/180)*fov/2.)*zfar));
//     Vector3D BC=multVector(multVector(R,tan((M_PI/180)*fov/2.)*zfar),-2.);
//     //Vector3D CA = addVectors(multVector(direction,-zfar),multVector(R,tan((M_PI/180)*fov/2.)*zfar));

//     Point3D B=createPoint(AB.x+cam.x, AB.y+cam.y, 0.,0);
//     Point3D C=createPoint(BC.x+B.x, BC.y+B.y, 0.,0);

//     //test  
//     if(intersectionDeuxSegments(xCam,yCam,direction_regard.x,direction_regard.y, B.x,B.y,C.x,C.y))
// 			//{sin(longitude)*sin(latitude)+xCam,cos(longitude)*sin(latitude)+yCam);}
// }

// void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l)
// {
//     int NO=quadtree->ptsExt->pointNO.coord;
//     int NE=quadtree->ptsExt->pointNE.coord;
//     int SO=quadtree->ptsExt->pointSO.coord;
//     int SE=quadtree->ptsExt->pointSE.coord;
// printf(" (abs(NO-SO): %d\n (abs(NO-NE):%d\n", abs(NO-SO),abs(NO-NE));
//     if((abs(NO-NE)==1) || (abs(NO-SO)==w))
//     {
//         printf("fin\n");
//         return;
//     }
//     else
//     {
//         //création des enfants

//         Node nodeNO= createNode(NO,
//                                 (int)((NO+NE)/2),
//                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w),
//                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2);
//         Quadtree quadNO = createQuadtree(&nodeNO);

//         Node nodeNE=createNode((int)((NO+NE)/2),
//                                 NE,
//                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l/2,
//                                  (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +l);       
//         Quadtree quadNE = createQuadtree(&nodeNE);

//         Node nodeSO=createNode( (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) ,
//                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2,
//                                 SO,
//                                 SO+(int)(l/2));
//         Quadtree quadSO = createQuadtree(&nodeSO);

//         Node nodeSE =createNode( (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2,
//                                 (int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +l,
//                                 SO+(int)(l/2),
//                                 SE);
//         Quadtree quadSE = createQuadtree(&nodeSE);

//         printf("nodeNE.NO: %d\n", nodeNE.pointNO);
//         printf("nodeNE.NE: %d\n", nodeNE.pointNE);
//         printf("nodeNE.SE: %d\n", nodeNE.pointSE);
//         printf("nodeNE.SO: %d\n", nodeNE.pointSO);

//         printf("nodeNO.NO: %d\n", nodeNO.pointNO);
//         printf("nodeNO.NE: %d\n", nodeNO.pointNE);
//         printf("nodeNO.SE: %d\n", nodeNO.pointSE);
//         printf("nodeNO.SO: %d\n", nodeNO.pointSO);

//         printf("nodeSE.NO: %d\n", nodeSE.pointNO);
//         printf("nodeSE.NE: %d\n", nodeSE.pointNE);
//         printf("nodeSE.SE: %d\n", nodeSE.pointSE);
//         printf("nodeSE.SO: %d\n", nodeSE.pointSO);

//         printf("nodeSO.NO: %d\n", nodeSO.pointNO);
//         printf("nodeSO.NE: %d\n", nodeSO.pointNE);
//         printf("nodeSO.SE: %d\n", nodeSO.pointSE);
//         printf("nodeSO.SO: %d\n", nodeSO.pointSO);

//         //ajout des enfants au quadtree
//         addChildQuadtree(quadtree,&quadNO,&quadNE,&quadSO,&quadSE);
//         //Récursion
//         printf("NO\n");
//         buildQuadtree(quadtree->enfantNO, vertex_coord,w, (int)(l/2));  
//         printf("NE\n");  
//         buildQuadtree(quadtree->enfantNE, vertex_coord,w, l-(int)(l/2));
//         printf("SO\n");
//         buildQuadtree(quadtree->enfantSO, vertex_coord,w,(int)(l/2));
//         printf("SE\n");
//         buildQuadtree(quadtree->enfantSE, vertex_coord,w,l-(int)(l/2));
//     }

// }



*/
