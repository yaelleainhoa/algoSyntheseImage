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

//first step

//calculer les coefficients de Lambert

int calculLambertCoef(light light, Point3D point)//point = point visé
{
    int lambert;
    Vector3D *light_vector=new Vector3D;
    *light_vector = createVectorFromPoints( light.position, point);
    Point3D normal_point=createPoint(normal_coord[point.coord], normal_coord[point.coord+1],normal_coord[point.coord+2]);
    Vector3D normal= createVectorFromPoints(point, normal_point);
    int cosine = dot(normal,normalize(*light_vector));
    if(cosine<=0)
    {  
         lambert =0;
    }
    else{
        lambert = cosine;
    }
    return lambert;
}

float luminosity(light light, Point3D point)
{
    float distance= distance2points(light.position, point);
    float luminosity = 1 / (distance * distance); 
}

Color3f finalColor(light light, Point3D point)
{
    Color3f pointColor= createColor(1.,0.,0.);//trouver la couleur d'un point avec une texture
    int lambert_factor= calculLambertCoef(light, point);
    float  lum= luminosity(light, point);
    Color3f final_color = multColor(pointColor , multColorParA(light.color , lambert_factor* lum));//point color avec les texture a trouver pour le moment
}


