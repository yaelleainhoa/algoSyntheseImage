#include "geometry.h"
#include "light.h"
#include "visu.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//--------------------fonctions sur les couleurs------------------------------

Color3f createColor(float r, float v , float b)//initie une couleur
{
    Color3f *newcolor= new Color3f;
    newcolor->b=b;
    newcolor->r=r;
    newcolor->v=v;

    return *newcolor;
}

Color3f multColorParA(Color3f *color, float a){//multiplie une couleur par un float
    Color3f newcolor=createColor(color->r*a,
                            color->v*a,
                            color->b*a);
    return newcolor;
}

Color3f multColor(Color3f c1, Color3f c2){//multiplie 2 couleurs
    Color3f color=createColor(c2.r*c1.r,
                            c2.v*c1.v,
                            c2.b*c1.b);
    return color;
}

//-----------------------------------------------------------------------------

Light createLight(Point3D position, Color3f color)//initie une lumière
{
    Light *light = new Light;
    light->position=position;
    light->color=color;

    return *light;
}



//------------------calcule des coefficients de Lambert-----------------------

float calculLambertCoef(Light light, Point3D A, Point3D B, Point3D C)//Calcul le coeff de Lambert associé au triangle ABC
{
    float lambert;
    Vector3D *light_vector=new Vector3D;
    Point3D center= centreTriangle(A,B,C);
    *light_vector = createVectorFromPoints( light.position,center );
    Vector3D normal =normalTriangle(A,B,C);
    float cosine = dot(normal,normalize(*light_vector));
    lambert= max(cosine, 0.05);

    float distance= distance2points(light.position, center);
    float luminosity = 1 / (distance * distance); 
    return lambert *luminosity;
}
     
Color3f finalColor(Light light, Point3D A, Point3D B, Point3D  C)//renvoie la couleur final associée au triangle ABC
{
    float lambert_factor= calculLambertCoef(light, A, B, C);
    Color3f final_color = multColorParA(&light.color , lambert_factor );
    return final_color;
}

void rotateSun(Light *light, int width, int angle2)
{
    light->position.x = sin(angle2)*cos(angle1)*(width/2);
    //light->position.y = y;
    light->position.z = cos(angle2)*(width/2);
    light->position.y = sin(angle2)*sin(angle1)*(width/2);
    // if(light->position.z < 0)
    // {angle2-=STEP_ANGLE*2;
    // }
    // else{
    //     angle2-=STEP_ANGLE*0.1;
    // }

    cout << "soleil position (x,y,z) : " << light->position.x << ", " << light->position.y << ", " << light->position.z << endl;
}