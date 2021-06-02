#ifndef __LIGHT_H
#define __LIGHT_H

#include "geometry.h"
#include "valDeGris.h"

//----------------Struct----------------------------
typedef struct 
{
    float r;
    float v;
    float b;
}Color3f;

typedef struct 
{
    Point3D position;
    Color3f color;
}Light;
//---------------------------------------------------

//----------fonctions sur la lumiere-----------------

Color3f createColor(float r, float v , float b);
Color3f multColorParA(Color3f color, float a);
Color3f multColor(Color3f c1, Color3f c2);
//---------------------------------------------------

Light createLight(Point3D position, Color3f color);

//---------Coefficient de Lambert--------------------

float calculLambertCoef(Light light, Point3D A, Point3D B, Point3D C);
Color3f finalColor(Light light, Point3D A, Point3D B, Point3D  C);

#endif