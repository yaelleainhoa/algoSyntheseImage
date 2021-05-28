#ifndef __VISU_CM_H
#define __VISU_CM_H

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	M_PI/90.

#include <string>
using namespace std;

/* variables globales pour la gestion de la caméra */
#include "light.h"

extern float profondeur;
extern float latitude;
extern float longitude;

extern float angle1;
extern float angle2;

extern float xCam;
extern float yCam;
extern float zCam;

extern float xRegard2D;
extern float yRegard2D;

extern int fov;
extern float zfar;

extern float xsize;
extern float zmin;
extern float zmax;
extern int NOMBRE_OBJET;
extern string map;

extern Light soleil;


/* variables globales pour la gestion de l'objet */
extern float obj_rot;

/* Déclaration des fonctions */
void idle(void);

void idleAngle(void);
#endif
