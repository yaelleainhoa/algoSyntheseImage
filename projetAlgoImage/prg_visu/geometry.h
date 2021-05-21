#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct Vec3f{
    float x;
    float y;
    float z;

    int coord;//coordonné de x dans vertex_coord
}Point3D, Vector3D;

// Construit le point (x, y, z)
Point3D createPoint(float x, float y, float z, int coord);

// Construit le vecteur (x, y, z)
Vector3D createVector(float x, float y, float z, int coord);

// Construit le vecteur reliant les points P1 et P2
Vector3D createVectorFromPoints(Point3D p1, Point3D p2);

// Construit le point P + V (i.e. translation de P par V)
Point3D pointPlusVector(Point3D p, Vector3D v);

// Addition et soustraction des vecteurs V1 et V2
Vector3D addVectors(Vector3D v1, Vector3D v2);
Vector3D subVectors(Vector3D v1, Vector3D v2);

// Multiplication et division d'un vecteur V par un scalaire a
Vector3D multVector(Vector3D v, float a);
Vector3D divVector(Vector3D v, float a);

// Produit scalaire des vecteurs V1 et V2
float dot(Vector3D a, Vector3D b);

// Norme d'un vecteur V
float norm(Vector3D v);

// Construit le vecteur normalisé du vecteur V
Vector3D normalize(Vector3D v);


void printPoint3D(Point3D p);
void printVector3D(Vector3D v);

int pointAppartientTriangle(float x, float y);//, float xCam, float yCam, float xRegard, float yRegard, float longitude, float zFar, float fov);
int intersectionDeuxSegments(float xA, float yA,float xB, float yB, float xC, float yC, float xD, float yD);

float distance(Point3D pt);
#endif