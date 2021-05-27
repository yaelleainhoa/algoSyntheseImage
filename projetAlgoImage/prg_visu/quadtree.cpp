#include "quadtree.h"
#include "geometry.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geometry.h"
#include "create_object.h"
#include <iostream>

using namespace std;



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

void printNode(Node node){
    printf("\n NO(%f,%f, %d), NE(%f,%f, %d), SO(%f,%f,%d), SE(%f,%f,%d)\n",
    node.pointNO.x,node.pointNO.y,node.pointNO.coord,
    node.pointNE.x,node.pointNE.y,node.pointNE.coord,
    node.pointSO.x,node.pointSO.y,node.pointSO.coord,
    node.pointSE.x,node.pointSE.y,node.pointSE.coord); 
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

    newQuadtree.ptsExt=*ptsExt;

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
    int NO=quadtree->ptsExt.pointNO.coord;
    int NE=quadtree->ptsExt.pointNE.coord;
    int SO=quadtree->ptsExt.pointSO.coord;
    int SE=quadtree->ptsExt.pointSE.coord;
//printf(" (abs(NO-SO): %d\n (abs(NO-NE):%d\n", abs(NO-SO),abs(NO-NE));
    if((abs(NO-NE)==1) || (abs(NO-SO)==w))
    {
        //printf("fin\n");
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
        Point3D NE_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l);
        Point3D SO_SO=createPointFromCoord(SO);
        Point3D SO_SE=createPointFromCoord(SO+(int)(l/2));
        Point3D SE_SE=createPointFromCoord(SE);

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

        // printf("nodeNE.NO: %d\n", nodeNE.pointNO.coord);
        // printf("nodeNE.NE: %d\n", nodeNE.pointNE.coord);
        // printf("nodeNE.SE: %d\n", nodeNE.pointSE.coord);
        // printf("nodeNE.SO: %d\n", nodeNE.pointSO.coord);

        // printf("nodeNO.NO: %d\n", nodeNO.pointNO.coord);
        // printf("nodeNO.NE: %d\n", nodeNO.pointNE.coord);
        // printf("nodeNO.SE: %d\n", nodeNO.pointSE.coord);
        // printf("nodeNO.SO: %d\n", nodeNO.pointSO.coord);

        // printf("nodeSE.NO: %d\n", nodeSE.pointNO.coord);
        // printf("nodeSE.NE: %d\n", nodeSE.pointNE.coord);
        // printf("nodeSE.SE: %d\n", nodeSE.pointSE.coord);
        // printf("nodeSE.SO: %d\n", nodeSE.pointSO.coord);

        // printf("nodeSO.NO: %d\n", nodeSO.pointNO.coord);
        // printf("nodeSO.NE: %d\n", nodeSO.pointNE.coord);
        // printf("nodeSO.SE: %d\n", nodeSO.pointSE.coord);
        // printf("nodeSO.SO: %d\n", nodeSO.pointSO.coord);

        //ajout des enfants au quadtree
        addChildQuadtree(quadtree,quadNO,quadNE,quadSO,quadSE);
        //Récursion
        //printf("NO\n");
        buildQuadtree(quadtree->enfantNO, vertex_coord,w, (int)(l/2));  
       // printf("NE\n");  
        buildQuadtree(quadtree->enfantNE, vertex_coord,w, l-(int)(l/2));
        //printf("SO\n");
        buildQuadtree(quadtree->enfantSO, vertex_coord,w,(int)(l/2));
        //printf("SE\n");
        buildQuadtree(quadtree->enfantSE, vertex_coord,w,l-(int)(l/2));
    }

}

//fonction qui regarde si un des points du quadtree est dans le triangle de la camera: 1 si oui 0 sinon
int quadAppartientTriangle(Node node/*, float xCam, float yCam, float xRegard, float yRegard, float zfar, float fov*/ )
{
    //cout<<"quad\n";
    //cout <<"on entre dans la fonction \n";
    Point3D NO=node.pointNO;
    Point3D NE=node.pointNE;
    Point3D SO=node.pointSO;
    Point3D SE=node.pointSE;
    
    if(pointAppartientTriangle(NO.x, NO.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(NE.x, NE.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(SO.x, SO.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov*/)
    ||pointAppartientTriangle(SE.x, SE.y/*,xCam, yCam,xRegard,yRegard,longitude, zfar, fov)*/))
    {
        //cout << "QUAD APPARTIENT TRIANGLE\n";
        return 1;
    }
    return 0;
}

//fonction qui regarde si un des sommets du triangle de la camera est dans le quadtree: 1 si oui 0 sinon
//a faire

int triangleAppartientQuadtree(Node node){
    //cout<<"triangle\n";

    Point3D cam=createPoint(xCam,yCam,0.,0);//j'ai mis des NULL pour les coordonnées dans vertex_coord à voir si ça marche ou si on doit revoir la struct
    Point3D direction_regard=createPoint(xRegard2D, yRegard2D,0.,0);
    Vector3D direction = createVectorFromPoints(cam, direction_regard);
    direction = normalize(direction);
    Vector3D R=createVector(direction.y, -direction.x,0.,0);


    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));
    Vector3D BC=multVector(multVector(R, tan(180/M_PI*(fov/2.))*zfar), -2.);

    Point3D B = createPoint(AB.x+cam.x, AB.y +cam.y,0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y,0,0);


   // printf("A(%f,%f), B(%f,%f), C(%f,%f)\n", cam.x,cam.y,B.x,B.y,C.x,C.y);

//  printf("pointAppartientQuadtree(quadtree, cam.x, cam.y) :%d\n", pointAppartientQuadtree(node, cam.x, cam.y));
//  printf("pointAppartientQuadtree(quadtree, B.x, B.y) :%d\n", pointAppartientQuadtree(node, B.x, B.y));
//  printf("pointAppartientQuadtree(quadtree, C.x, C.y) :%d\n", pointAppartientQuadtree(node, C.x, C.y));

    if(pointAppartientQuadtree(node, cam.x, cam.y)
    ||pointAppartientQuadtree(node, B.x, B.y)
    ||pointAppartientQuadtree(node, C.x, C.y))
    {
        //cout << "TRIANGLE APPARTIENT QUAD \n";
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
    //cout << "NE.x : %f, NO.x : %f, NE.y : %f, NO.y : %f, NENO.x : %f , NENO.y :%f, NEP.x:%f, NEP.y:%f \n" << NE.x << NO.x << NE.y<< NO.y<< NENO.x<<NENO.y<<NEP.x<< NEP.y<<endl;
   // cout << "NO.x : %f, SO.x : %f, NOSO.x : %f , NOSO.y :%f, NOP.x:%f, NOP.y:%f \n" << NO.x << SO.x << NOSO.x<<NOSO.y<< NOP.x<< NOP.y<<endl;
    //cout << "SO.x : %f, SE.x : %f, SO.y : %f, SE.y : %f, SOSE.x : %f , SOSE.y :%f, SOP.x:%f, SOP.y:%f \n" << SO.x << SE.x << SO.y<< SE.y<< SOSE.x<<SOSE.y<< SOP.x<< SOP.y<<endl;
    //cout << "SE.x : %f, NE.x : %f, SENE.x : %f , SENE.y :%f, SEP.x:%f, SEP.y:%f \n" << SE.x << NE.x << SENE.x<<SENE.y<< SEP.x<< SEP.y<<endl;

    Vector3D vecteurs[4]={NENO, NOSO, SOSE, SENE};
    Vector3D vecteursP[4]={NEP,NOP,SOP, SEP};
    float determinant =0;

    for(int i=0; i<4; i++){
        determinant = vecteurs[i].x * vecteursP[i].y - vecteurs[i].y * vecteursP[i].x;
        //printf("vec.x : %f , vec.y :%f, AP.x:%f, AP.y:%f \n",vecteurs[i].x,vecteurs[i].y, vecteursP[i].x, vecteursP[i].y);
        //printf("det : %f \n", determinant);
        if (determinant<0){
            return 0;
        }
    }
    return 1;
}

//fonction qui regarde si un des vect du triangle de la cam intersect un des vecteurs des contours du quadtree
int camIntersectQuad(Quadtree *quadtree)
{
    //cout<<"cam\n";
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
    //Vector3D CA=addVectors(multVector(direction, -zfar), multVector(R, tan(fov/2.)*zfar));

    Point3D B=createPoint(AB.x+cam.x, AB.y+cam.y, 0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y, 0.,0);

    //test  
        // vecteur AB  du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
        //printf("B.x : %f B.y :%f NE.x: %f NE.y :%f NO.x :%f NO.y :%f",B.x, B.y, NE.x, NE.y, NO.x, NO.y);
        //printf("AB 1 \n");
        return 1; 
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
      //  printf("AB 2\n");
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
      //  printf("AB 3\n");
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,B.x, B.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
       // printf("AB 4\n");
        return 1;
    }

        // vecteur BC du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
       // printf("BC 1\n");
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
       // printf("BC 2\n");
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
       // printf("BC 3\n");
        return 1;
    }
    if(intersectionDeuxSegments(B.x, B.y, C.x, C.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
      //  printf("BC 4\n");
        return 1;
    }

        // vecteur AC du triangle intersection avec le quadtree ?
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, NE.x, NE.y, NO.x, NO.y)== 1 ){
       // printf("AC 1\n");
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, NO.x, NO.y, SO.x, SO.y)== 1 ){
       // printf("AC 2\n");
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, SO.x, SO.y, SE.x, SE.y)== 1 ){
       // printf("AC 3\n");
        return 1;
    }
    if(intersectionDeuxSegments(xCam,yCam,C.x, C.y, SE.x, SE.y, NE.x, NE.y)== 1 ){
        return 1;
       // printf("AC 4\n");
    }

    return 0;
}

void travelQuadtree(Node ptsVisibles[], Quadtree quadtree, int* ptCount)
{
    float distNO=distanceCam(quadtree.ptsExt.pointNO);
    float distSO=distanceCam(quadtree.ptsExt.pointSO);
    float distSE=distanceCam(quadtree.ptsExt.pointSE);
    float distNE=distanceCam(quadtree.ptsExt.pointNE);
    float distMin = min(min(distNO,distNE),min(distSO,distSE));
    if(distMin > abs((quadtree.ptsExt.pointNO.y - quadtree.ptsExt.pointNE.y))*7)//(abs((quadtree.ptsExt.pointNO.y - quadtree.ptsExt.pointNE.y)/700)) || distMin>0.15){
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

    else //si on rentre la c'est que le quadtree est une feuille
    {
        ptsVisibles[(*ptCount)]=quadtree.ptsExt;
        (*ptCount)++;
    }

    }

}



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
