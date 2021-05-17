#ifndef __CREATE_OBJECT_H
#define __CREATE_OBJECT_H

#include "valDeGris.h"

extern unsigned int vertex_number;
extern float* vertex_coord;
extern float* normal_coord;
extern float* textures_coord;
extern unsigned int triangle_number;
extern unsigned int* triangle_index;
extern float l;

void createCoordinates(HeightMap heightMap);
void posToVertex(float xPos, float yPos, HeightMap heightMap, float *zCam);


#endif
