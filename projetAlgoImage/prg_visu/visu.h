#ifndef __VISU_CM_H
#define __VISU_CM_H

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	M_PI/90.
/* variables globales pour la gestion de la caméra */
#include "light.h"

extern float profondeur;
extern float latitude;
extern float longitude;

extern float xCam;
extern float yCam;
extern float zCam;

extern float xRegard2D;
extern float yRegard2D;

extern const int fov;
extern float zfar;

extern Light soleil;

/* variables globales pour la gestion de l'objet */
extern float obj_rot;

/* Déclaration des fonctions */
void idle(void);


#endif
