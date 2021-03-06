#include <math.h>
#include "geometry.h"
#include "quadtree.h"
#include "visu.h"
#include "create_object.h"
#include <stdio.h>

#include <iostream>

using namespace std;

//--------------------------Point ----------------------------------------------------------------
Point3D createPoint(float x, float y, float z, int coord){
    Point3D newPoint;
    newPoint.x=x;
    newPoint.y=y;
    newPoint.z=z;
    newPoint.coord=coord;
    return newPoint;
}


Point3D createPointFromCoord(int coord) 
{
    return createPoint(vertex_coord[3*coord], vertex_coord[3*coord+1],vertex_coord[3*coord+2] , coord);
}

Point3D addPoint(Point3D p1, Point3D p2)
{
    Point3D sum = createPoint(p1.x+p2.x, p1.y+p2.y, p1.z+p2.z, 0);
    return sum;
}
//------------------------------------------------------------------------------------------------

//--------------------------Vector----------------------------------------------------------------

Vector3D createVector(float x, float y, float z, int coord){
    Vector3D newVect;
    newVect.x=x;
    newVect.y=y;
    newVect.z=z;
    newVect.coord=coord;
    return newVect;
}

Vector3D createVectorFromPoints(Point3D p1, Point3D p2){
    p1.x=p2.x-p1.x;
    p1.y=p2.y-p1.y;
    p1.z=p2.z-p1.z;
    return p1;
}

Point3D pointPlusVector(Point3D p, Vector3D v){
    p.x=p.x+v.x;
    p.y=p.y+v.y;
    p.z=p.z+v.z;
    return p;
}

Vector3D addVectors(Vector3D v1, Vector3D v2){
    v1.x=v1.x+v2.x;
    v1.y=v1.y+v2.y;
    v1.z=v1.z+v2.z;
    return v1;
}

Vector3D subVectors(Vector3D v1, Vector3D v2){
    v1.x=v1.x-v2.x;
    v1.y=v1.y-v2.y;
    v1.z=v1.z-v2.z;
    return v1;
}

Vector3D multVector(Vector3D v, float a){
    v.x=v.x*a;
    v.y=v.y*a;
    v.z=v.z*a;
    return v;
}

Vector3D divVector(Vector3D v, float a){
    v.x=v.x/a;
    v.y=v.y/a;
    v.z=v.z/a;
    return v;
}

float norm(Vector3D v){
    return sqrt(dot(v,v));
}

Vector3D normalize(Vector3D v){
    return divVector(v, norm(v));
}

//------------------------------------------------------------------

//produit scalaire
float dot(Vector3D a, Vector3D b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

//produit vectoriel
Vector3D crossProduct(Vector3D a, Vector3D b)
{
    float x= a.y*b.z - a.z*b.y;
    float y= b.x*a.z - b.z*a.x;
    float z= a.x*b.y - a.y*b.x;

    Vector3D prod =createVector(x,y,z,0.);
    return prod;
}

//---------------fonctions d'affichages pour les tests-------------------------
void printPoint3D(Point3D p){
    printf("Point : (%f,%f,%f)\n", p.x, p.y, p.z);
}

void printVector3D(Vector3D p){
    printf("Vecteur : (%f,%f,%f)\n", p.x, p.y, p.z);
}
//------------------------------------------------------------------------------

//----------------fonctions pour les quadtree----------------------------------

int pointAppartientTriangle(float x, float y){//regarde si un point est ?? l'interieur du triangle form?? par la cam??ra    
    Point3D A=createPoint(xCam,yCam,0.,0);
    Point3D P=createPoint(x,y,0.,0);
    Vector3D AP=createVectorFromPoints(A,P);
    Point3D direction_regard=createPoint(xRegard2D, yRegard2D,0.,0);
    Vector3D direction = createVectorFromPoints(A, direction_regard);
    direction = normalize(direction);
    Vector3D R=createVector(direction.y, -direction.x,0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));
    Vector3D BC=multVector(multVector(R, tan(180/M_PI*(fov/2.))*zfar), -2.);
    Vector3D CA=addVectors(multVector(direction, -zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));

    Point3D B = createPoint(AB.x+A.x, AB.y +A.y,0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y,0,0);

    Vector3D BP=createVectorFromPoints(B,P);
    Vector3D CP=createVectorFromPoints(C,P);

    Vector3D vecteurs[3]={AB, BC, CA};
    Vector3D vecteursP[3]={AP,BP,CP};
    float determinant =0;
    for(int i=0; i<3; i++){
        determinant = vecteurs[i].x * vecteursP[i].y - vecteurs[i].y * vecteursP[i].x;

        if (determinant<0){
            return 0;
        }
    }
    return 1;
}

//regarde si deux segments se croisent : renvoie 1 si oui 0, si non
int intersectionDeuxSegments(float xA, float yA,float xB, float yB, float xC, float yC, float xD, float yD){
    Point3D A = createPoint(xA,yA,0.,0);
    Point3D B = createPoint(xB,yB,0.,0);
    Point3D C = createPoint(xC,yC,0.,0);
    Point3D D = createPoint(xD,yD,0.,0);

    Vector3D AB=createVectorFromPoints(A,B);
    Vector3D CD=createVectorFromPoints(C,D);

    //On v??rifie que A et B sont de part et d'autre de [CD]
    Vector3D CA=createVectorFromPoints(C,A);
    Vector3D CB=createVectorFromPoints(C,B);

    float det1=CD.x*CA.y-CD.y*CA.x;
    float det2=CD.x*CB.y-CD.y*CB.x;

    if(det1*det2>0){ //Si le produit est sup??rieur, les d??terminants sont de m??me signe et donc les points sont du m??me c??t??
        return 0;
    }

    //On v??rifie que C et D sont de part et d'autre de [AB]
    Vector3D AC=createVectorFromPoints(A,C);
    Vector3D AD=createVectorFromPoints(A,D);
    det1=AB.x*AC.y-AB.y*AC.x;
    det2=AB.x*AD.y-AB.y*AD.x;

    if(det1*det2>0){
        return 0;
    }
    return 1;
}
//--------------------------------------------------------------

//-------------fonctions g??n??rales------------------------------
float distanceCam(Point3D pt) //distance d'un point ?? la cam??ra
{
    float distance = sqrt((xCam-pt.x)*(xCam-pt.x) 
                        + (yCam-pt.y)*(yCam-pt.y) 
                        + (zCam-pt.z)*(zCam-pt.z));
    return distance;
}

float distance2points(Point3D p1, Point3D p2)//distance entre 2 points
{
    float distance = sqrt((p2.x-p1.x)*(p2.x-p1.x) 
                        + (p2.y-p1.y)*(p2.y-p1.y) 
                        + (p2.z-p1.z)*(p2.z-p1.z));
    return distance;
}

float min(float d1, float d2)
{   if(d1<d2)
        {return d1;}
    else
        {return d2;}
}

float max(float d1, float d2)
{
    if(d1<d2)
        {return d2;}
    else
        {return d1;}
}
//-----------------------------------------------------------------------------------------------

//---------------------fonctions pour calculer Lambert--------------------------------------------
Vector3D normalTriangle(Point3D A, Point3D B, Point3D C)//calcul le vecteur normal au triangle ABC
{
    Vector3D AC = createVectorFromPoints(A, C);
    Vector3D AB = createVectorFromPoints(A, B);
    Vector3D normal = crossProduct(AB, AC);
    normal=normalize(normal);
    return normal;
}

Point3D centreTriangle(Point3D a, Point3D b, Point3D c)//calcul le point au centre du triangle ABC
{
    Point3D sum= addPoint(addPoint(a, b), c);
    Point3D center = multVector(sum, 1/3.0);
    return center;
}
//-------------------------------------------------------------------------------------------------
