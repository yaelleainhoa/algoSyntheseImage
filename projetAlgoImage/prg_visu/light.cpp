#include <math.h>
#include "light.h"
#include "visu.h"
#include <stdio.h>
#include "geometry.h"
#include"create_object.h"

#include <iostream>

using namespace std;

Color3f createColor(float r, float v , float b)
{
    Color3f *newcolor= new Color3f;
    newcolor->b=b;
    newcolor->r=r;
    newcolor->v=v;

    return *newcolor;
}

Color3f multColorParA(Color3f *color, float a){
    Color3f newcolor=createColor(color->r*a,
                            color->v*a,
                            color->b*a);
    return newcolor;
}

Color3f multColor(Color3f c1, Color3f c2)
{
    Color3f color=createColor(c2.r*c1.r,
                            c2.v*c1.v,
                            c2.b*c1.b);
    return color;
}

Light createLight(Point3D position, Color3f color)
{
    Light *newLight = new Light;
    newLight->color=color;
    newLight->position=position;

    return *newLight;
}

//first step

//calculer les coefficients de Lambert



float calculLambertCoef(Light light, Point3D a, Point3D b, Point3D c)//abc le triangle
{
    float lambert;
    Vector3D *light_vector=new Vector3D;
    Point3D center= centreTriangle(a,b,c);
    *light_vector = createVectorFromPoints( light.position,center );
    Vector3D normal =normalTriangle(a, b, c);
    float cosine = dot(normal,normalize(*light_vector));
    lambert= max(cosine, 0.);

    float distance= distance2points(light.position, center);
    float luminosity = 1 / (distance * distance); 
    return lambert *luminosity;
}

  

