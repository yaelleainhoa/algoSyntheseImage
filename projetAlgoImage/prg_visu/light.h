#ifndef LIGHT_H
#define LIGHT_H

typedef struct Color3f
{
    float r;
    float v;
    float b;
};

typedef struct light
{
    Point3D position;
    Color3f color;
};
Color3f createColor(float r, float v , float b);
Color3f multColorParA(Color3f color, float a);
Color3f multColor(Color3f c1, Color3f c2);

int calculLambertCoef(light light, Point3D point);
float luminosity(light light, Point3D point);
Color3f finalColor(light light, Point3D point);

#endif