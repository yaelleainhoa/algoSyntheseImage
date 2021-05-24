#include <math.h>
#include "geometry.h"
#include "quadtree.h"
#include "visu.h"
#include <stdio.h>

#include <iostream>

using namespace std;


Point3D createPoint(float x, float y, float z, int coord){
    Point3D newPoint;
    newPoint.x=x;
    newPoint.y=y;
    newPoint.z=z;
    newPoint.coord=coord;
    return newPoint;
}

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

float dot(Vector3D a, Vector3D b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

float norm(Vector3D v){
    return sqrt(dot(v,v));
}

Vector3D normalize(Vector3D v){
    return divVector(v, norm(v));
}

void printPoint3D(Point3D p){
    printf("Point : (%f,%f,%f)\n", p.x, p.y, p.z);
}

void printVector3D(Vector3D p){
    printf("Vecteur : (%f,%f,%f)\n", p.x, p.y, p.z);
}

//regarde si un point est à l'interieur du triangle formé par la caméra
int pointAppartientTriangle(float x, float y){//, float xCam, float yCam, float xRegard, float yRegard, float longitude, float zFar, float fov){
//normalement zfar longitude et fov sont en variables globales on devrait pouvoir ne pas les mettre en parametres
    //cout << "\n P(%f, %f) \n"<< x<<y<<endl;
    
    Point3D A=createPoint(xCam,yCam,0.,0);//j'ai mis des NULL pour les coordonnées dans vertex_coord à voir si ça marche ou si on doit revoir la struct
    Point3D P=createPoint(x,y,0.,0);
    Vector3D AP=createVectorFromPoints(A,P);
    Point3D direction_regard=createPoint(xRegard2D, yRegard2D,0.,0);
    Vector3D direction = createVectorFromPoints(A, direction_regard);
    direction = normalize(direction);
    //Vector3D L=createVector(cos(longitude+M_PI/2), sin(longitude+M_PI/2),0.,0);
    Vector3D R=createVector(direction.y, -direction.x,0.,0);

    Vector3D AB=addVectors(multVector(direction, zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));
    Vector3D BC=multVector(multVector(R, tan(180/M_PI*(fov/2.))*zfar), -2.);
    Vector3D CA=addVectors(multVector(direction, -zfar), multVector(R, tan(180/M_PI*(fov/2.))*zfar));

    Point3D B = createPoint(AB.x+A.x, AB.y +A.y,0.,0);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y,0,0);

    Vector3D BP=createVectorFromPoints(B,P);
    Vector3D CP=createVectorFromPoints(C,P);

   // cout << "les coord sont : A(%f,%f), B(%f,%f), C(%f,%f)\n"<<  A.x<<A.y<<B.x<<B.y<<C.x<<C.y<<endl;

    Vector3D vecteurs[3]={AB, BC, CA};
    Vector3D vecteursP[3]={AP,BP,CP};
    float determinant =0;
    for(int i=0; i<3; i++){
        determinant = vecteurs[i].x * vecteursP[i].y - vecteurs[i].y * vecteursP[i].x;
        //cout << "vec.x : %f , vec.y :%f, AP.x:%f, AP.y:%f \n"<< vecteurs[i].x,vecteurs[i].y, vecteursP[i].x, vecteursP[i].y<<endl;
        //cout << "det : %f \n"<<  determinant<<endl;

        if (determinant<0){
            //cout << "det : %f \n"<<  determinant<<endl;
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

    //On vérifie que A et B sont de part et d'autre de [CD]
    Vector3D CA=createVectorFromPoints(C,A);
    Vector3D CB=createVectorFromPoints(C,B);

    float det1=CD.x*CA.y-CD.y*CA.x;
    float det2=CD.x*CB.y-CD.y*CB.x;

    if(det1*det2>0){ //Si le produit est supérieur, les déterminants sont de même signe et donc les points sont du même côté
        return 0;
    }

    //On vérifie que C et D sont de part et d'autre de [AB]
    Vector3D AC=createVectorFromPoints(A,C);
    Vector3D AD=createVectorFromPoints(A,D);
    det1=AB.x*AC.y-AB.y*AC.x;
    det2=AB.x*AD.y-AB.y*AD.x;

    if(det1*det2>0){
        return 0;
    }

    return 1;

}

float distance(Point3D pt)
{
    float distance = sqrt((xCam-pt.x)*(xCam-pt.x) 
                        + (yCam-pt.y)*(yCam-pt.y) 
                        + (zCam-pt.z)*(zCam-pt.z));
    return distance;
}


float min(float d1, float d2)
{   if(d1<d2)
        {return d1;}
    else
        {return d2;}
}
