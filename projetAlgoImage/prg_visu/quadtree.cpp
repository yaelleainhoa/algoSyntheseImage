#include "quadtree.h"
#include "geometry.h"
#include "geometry.h"
#include "create_object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define TAILLE_PIXELS 1

int loop=0;

//fonction d'aide pour tester
void printNode(Node node){
    printf("\n NO(%f,%f, %d), NE(%f,%f, %d), SO(%f,%f,%d), SE(%f,%f,%d)\n",
    node.pointNO.x,node.pointNO.y,node.pointNO.coord,
    node.pointNE.x,node.pointNE.y,node.pointNE.coord,
    node.pointSO.x,node.pointSO.y,node.pointSO.coord,
    node.pointSE.x,node.pointSE.y,node.pointSE.coord); 
}

//------------------------------Initialisation------------------------------------
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

    newQuadtree.ptsExt=*ptsExt;

    newQuadtree.enfantNO=NULL;
    newQuadtree.enfantNE=NULL;
    newQuadtree.enfantSO=NULL;
    newQuadtree.enfantSE=NULL;
    
    return newQuadtree;
}
//-------------------------------------------------------------------------------

//ajoute les 4 enfants NO, NE, SO, SE à quadtree
void addChildQuadtree(Quadtree *quadtree, Quadtree * enfantNO,Quadtree * enfantNE,Quadtree * enfantSO,Quadtree * enfantSE)
{
    quadtree->enfantNO=enfantNO;
    quadtree->enfantNE=enfantNE;
    quadtree->enfantSO=enfantSO;
    quadtree->enfantSE=enfantSE;
}

//crée le quadtree d'après le tableau de coordonnées vertex_coord
void buildQuadtree(Quadtree * quadtree,float vertex_coord[],int const w, int l)
{
    int NO=quadtree->ptsExt.pointNO.coord;
    int NE=quadtree->ptsExt.pointNE.coord;
    int SO=quadtree->ptsExt.pointSO.coord;
    int SE=quadtree->ptsExt.pointSE.coord;
    //condition d'arret: si on est sur une feuille ie deux des 4 sommets au moins sont espacé de 1 unité
    if((abs(NO-NE)==1) /*cote à cote*/|| (abs(NO-SO)==w)/*l'un au dessus de l'autre*/)
    {
        return;//on sort
    }
    else
    {
        //création des enfants 
        //on crée d'abord les points des nodes
        Point3D NO_NO=createPointFromCoord(NO);
        Point3D NO_NE=createPointFromCoord((int)((NO+NE)/2));
        Point3D NO_SO=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w));
        Point3D NO_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w) +(int)l/2);
        Point3D NE_NE=createPointFromCoord(NE);
        Point3D NE_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l);
        Point3D SO_SO=createPointFromCoord(SO);
        Point3D SO_SE=createPointFromCoord(SO+(int)(l/2));
        Point3D SE_SE=createPointFromCoord(SE);

        //on crée ensuite les nodes
        Node nodeNO= createNode(NO_NO,
                                NO_NE,
                                NO_SO,
                                NO_SE);
        Quadtree * quadNO = new Quadtree;
        *quadNO = createQuadtree(&nodeNO);

        Node nodeNE=createNode(NO_NE,
                                NE_NE,
                                NO_SE,
                                NE_SE);       
        Quadtree * quadNE = new Quadtree;
        *quadNE = createQuadtree(&nodeNE);

        Node nodeSO=createNode( NO_SO ,
                                NO_SE,
                                SO_SO,
                                SO_SE);
        Quadtree * quadSO = new Quadtree;
        *quadSO = createQuadtree(&nodeSO);

        Node nodeSE =createNode( NO_SE,
                                NE_SE,
                                SO_SE,
                                SE_SE);
        Quadtree * quadSE = new Quadtree;
        *quadSE = createQuadtree(&nodeSE);

        //ajout des enfants au quadtree
        addChildQuadtree(quadtree,quadNO,quadNE,quadSO,quadSE);
        //Récursion;
        buildQuadtree(quadtree->enfantNO, vertex_coord,w, (int)(l/2));  
        buildQuadtree(quadtree->enfantNE, vertex_coord,w, l-(int)(l/2));
        buildQuadtree(quadtree->enfantSO, vertex_coord,w,(int)(l/2));
        buildQuadtree(quadtree->enfantSE, vertex_coord,w,l-(int)(l/2));
    }
}

//fonction qui regarde si un des points du quadtree est dans le triangle de la camera: 1 si oui 0 sinon
int quadAppartientTriangle(Node node)
{
    Point3D NO=node.pointNO;
    Point3D NE=node.pointNE;
    Point3D SO=node.pointSO;
    Point3D SE=node.pointSE;
    
    if(pointAppartientTriangle(NO.x, NO.y)
        ||pointAppartientTriangle(NE.x, NE.y)
        ||pointAppartientTriangle(SO.x, SO.y)
        ||pointAppartientTriangle(SE.x, SE.y))
    {
        return 1;
    }
    return 0;
}

//fonction qui regarde si un des sommets du "triangle de la camera" est dans le quadtree: 1 si oui 0 sinon
int triangleAppartientQuadtree(Node node){

    Point3D cam=createPoint(xCam,yCam,0.,0);
    Point3D direction_regard=createPoint(xRegard2D, yRegard2D,0.,0);
    Vector3D direction = createVectorFromPoints(cam, direction_regard);
    direction = normalize(direction);
    Vector3D R=createVector(direction.y, -direction.x,0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));
    Vector3D BC=multVector(multVector(R, tan(180/M_PI*(fov/2.))*zfar), -2.);

    Point3D B = createPoint(AB.x+cam.x, AB.y +cam.y,0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y,0,0);

    if(pointAppartientQuadtree(node, cam.x, cam.y)
    ||pointAppartientQuadtree(node, B.x, B.y)
    ||pointAppartientQuadtree(node, C.x, C.y))
    {
        return 1;
    }
    return 0;
}


int pointAppartientQuadtree(Node node, float Px, float Py){

    Point3D NO=node.pointNO;
    Point3D NE=node.pointNE;
    Point3D SO=node.pointSO;
    Point3D SE=node.pointSE;


    Point3D P = createPoint(Px, Py, 0,0);

    Vector3D NENO = createVectorFromPoints(NE, NO);
    Vector3D NOSO = createVectorFromPoints(NO, SO);
    Vector3D SOSE = createVectorFromPoints(SO, SE);
    Vector3D SENE = createVectorFromPoints(SE, NE);
    

    Vector3D NEP=createVectorFromPoints(NE,P);
    Vector3D NOP=createVectorFromPoints(NO,P);
    Vector3D SOP=createVectorFromPoints(SO,P);
    Vector3D SEP=createVectorFromPoints(SE,P);

    Vector3D vecteurs[4]={NENO, NOSO, SOSE, SENE};
    Vector3D vecteursP[4]={NEP,NOP,SOP, SEP};
    float determinant =0;

    for(int i=0; i<4; i++){
        determinant = vecteurs[i].x * vecteursP[i].y - vecteurs[i].y * vecteursP[i].x;
        if(determinant<0){
            return 0;
        }
    }
    return 1;
}

//fonction qui regarde si un des vect du triangle de la cam intersect un des vecteurs des contours du quadtree
int camIntersectQuad(Quadtree *quadtree)
{
    Point3D NO=quadtree->ptsExt.pointNO;
    Point3D NE=quadtree->ptsExt.pointNE;
    Point3D SO=quadtree->ptsExt.pointSO;
    Point3D SE=quadtree->ptsExt.pointSE;

    //points exterieurs triangle caméra
    float xRegard2D = sin(longitude)+xCam;
    float yRegard2D = cos(longitude)+yCam;
    Point3D cam= createPoint(xCam,yCam,0.,0);
    Point3D direction_regard = createPoint(xRegard2D,yRegard2D,0.,0);

    Vector3D direction=normalize(createVectorFromPoints(cam,direction_regard));
    Vector3D R=createVector(direction.y, -direction.x,0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));
    Vector3D BC=multVector(multVector(R, tan(180/M_PI*(fov/2.))*zfar), -2.);

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

//parcours le quadtree préalablement crée et rempli le tableau ptsVisibless selon si le Node est dans le champs de la camera ou non
void travelQuadtree(Node ptsVisibles[], Quadtree quadtree, int* ptCount)
{
    float distNO=distanceCam(quadtree.ptsExt.pointNO);
    float distSO=distanceCam(quadtree.ptsExt.pointSO);
    float distSE=distanceCam(quadtree.ptsExt.pointSE);
    float distNE=distanceCam(quadtree.ptsExt.pointNE);
    float distMin = min(min(distNO,distNE),min(distSO,distSE));
    if(distMin > abs((quadtree.ptsExt.pointNO.y - quadtree.ptsExt.pointNE.y))*6)
    {
        ptsVisibles[(*ptCount)]=quadtree.ptsExt;
        (*ptCount)++;
    }
    else{
        if(quadtree.enfantNO)
        {
            if(quadAppartientTriangle(quadtree.enfantNO->ptsExt) || camIntersectQuad(quadtree.enfantNO) || triangleAppartientQuadtree(quadtree.enfantNO->ptsExt))
            {
                travelQuadtree(ptsVisibles, *(quadtree.enfantNO),ptCount);
            }

            if(quadAppartientTriangle(quadtree.enfantNE->ptsExt) || camIntersectQuad(quadtree.enfantNE) || triangleAppartientQuadtree(quadtree.enfantNE->ptsExt))
            {
                travelQuadtree(ptsVisibles, *(quadtree.enfantNE),ptCount);
            }

            if(quadAppartientTriangle(quadtree.enfantSO->ptsExt) || camIntersectQuad(quadtree.enfantSO)||  triangleAppartientQuadtree(quadtree.enfantSO->ptsExt))
            {
                travelQuadtree(ptsVisibles, *(quadtree.enfantSO),ptCount);
            }

            if(quadAppartientTriangle(quadtree.enfantSE->ptsExt) || camIntersectQuad(quadtree.enfantSE) || triangleAppartientQuadtree(quadtree.enfantSE->ptsExt))
            {
                travelQuadtree(ptsVisibles, *(quadtree.enfantSE),ptCount);
            }
        }

        else //si on rentrée là c'est que le quadtree est une feuille alors on met le point dans le tableau
        {
            ptsVisibles[(*ptCount)]=quadtree.ptsExt;
            (*ptCount)++;
        }
    }
}

