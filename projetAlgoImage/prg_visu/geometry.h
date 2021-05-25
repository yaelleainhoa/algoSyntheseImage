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

// Construit le point qui correspond à la coordonnées coord dans le tableau de vertex
Point3D createPointFromCoord(int coord, float coord_vert[]);

// ajoute des points
Point3D addPoint(Point3D p1, Point3D p2);

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

// Produit scalaire des vecteurs a et b
float dot(Vector3D a, Vector3D b);

//Produit Vectoriel des vecteurs a et b
Vector3D crossProduct(Vector3D a, Vector3D b);

// Norme d'un vecteur V
float norm(Vector3D v);

// Construit le vecteur normalisé du vecteur V
Vector3D normalize(Vector3D v);


void printPoint3D(Point3D p);
void printVector3D(Vector3D v);

int pointAppartientTriangle(float x, float y);//, float xCam, float yCam, float xRegard, float yRegard, float longitude, float zFar, float fov);
int intersectionDeuxSegments(float xA, float yA,float xB, float yB, float xC, float yC, float xD, float yD);
float distanceCam(Point3D pt);
float distance2points(Point3D p1, Point3D p2);
float min(float d1, float d2);
float max(float d1, float d2);

int pointAppartientQuadtree(float Px, float Py);
Vector3D normalTriangle(Point3D p1, Point3D p2, Point3D p3);
Point3D centreTriangle(Point3D a, Point3D b, Point3D c);

#endif