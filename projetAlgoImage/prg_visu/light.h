#ifndef __LIGHT_H
#define __LIGHT_H

#include "geometry.h"

#include "geometry.h"
#include "valDeGris.h"

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


Color3f createColor(float r, float v , float b);
Color3f multColorParA(Color3f color, float a);
Color3f multColor(Color3f c1, Color3f c2);

Light createLight(Point3D position, Color3f color);

float calculLambertCoef(Light light, Point3D p1, Point3D p2, Point3D p3);
Color3f finalColor(Light light, Point3D a, Point3D b, Point3D  c);

void rotateSun(light *light, float x, float y, float z, int width);

#endif