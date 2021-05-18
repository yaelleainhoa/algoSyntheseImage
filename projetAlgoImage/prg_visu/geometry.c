#include <math.h>
#include "geometry.h"
#include <stdio.h>

Point3D createPoint(float x, float y, float z){
    Point3D newPoint;
    newPoint.x=x;
    newPoint.y=y;
    newPoint.z=z;
    return newPoint;
}

Vector3D createVector(float x, float y, float z){
    Vector3D newVect;
    newVect.x=x;
    newVect.y=y;
    newVect.z=z;
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

int pointAppartientTriangle(float x, float y, float xCam, float yCam, float xRegard, float yRegard, float teta, float zFar, float fov){
    Point3D A=createPoint(xCam,yCam,0.);
    Point3D P=createPoint(x,y,0.);
    Vector3D AP=createVectorFromPoints(A,P);
    Point3D direction_regard=createPoint(xRegard, yRegard,0.);
    Vector3D direction = createVectorFromPoints(A, direction_regard);
    direction = normalize(direction);
    Vector3D L=createVector(cos((M_PI/180)*teta+M_PI/2), sin((M_PI/180)*teta+M_PI/2),0.);
    Vector3D R=createVector(cos((M_PI/180)*teta-M_PI/2), sin((M_PI/180)*teta-M_PI/2),0.);

    Vector3D AB=addVectors(multVector(direction, zFar), multVector(R, tan((M_PI/180)*fov/2.)*zFar));
    Vector3D BC=multVector(multVector(R, tan((M_PI/180)*fov/2.)*zFar), -2.);
    Vector3D CA=addVectors(multVector(direction, -zFar), multVector(R, tan((M_PI/180)*fov/2.)*zFar));

    Point3D B = createPoint(AB.x+A.x, AB.y +A.y,0.);
    Point3D C=createPoint(BC.x+B.x, BC.y+B.y,0);

    Vector3D BP=createVectorFromPoints(B,P);
    Vector3D CP=createVectorFromPoints(C,P);

    Vector3D vecteurs[3]={AB, BC, CA};
    Vector3D vecteursP[3]={AP,BP,CP};
    float determinant =0;

    for(int i=0; i<3; i++){
        determinant = vecteurs[i].x * vecteursP[i].y - vecteurs[i].y * vecteursP[i].x;
        printf("vec.x : %f , vec.y :%f, AP.x:%f, AP.y:%f \n",vecteurs[i].x,vecteurs[i].y, vecteursP[i].x, vecteursP[i].y);
        if (determinant<0){
            printf("det : %f \n", determinant);
            return 0;
        }
    }
    return 1;

}