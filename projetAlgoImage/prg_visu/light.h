#ifndef LIGHT_H
#define LIGHT_H

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
}light;


Color3f createColor(float r, float v , float b);
Color3f multColorParA(Color3f color, float a);
Color3f multColor(Color3f c1, Color3f c2);

float calculLambertCoef(light light, Point3D p1, Point3D p2, Point3D p3);
Color3f finalColor(light light, Point3D point);

#endif