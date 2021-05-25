#ifndef __CREATE_OBJECT_H
#define __CREATE_OBJECT_H

#include "valDeGris.h"
#include "quadtree.h"



extern unsigned int vertex_number;

extern float* vertex_coord;
extern float* normal_coord;
extern float* textures_coord;
extern unsigned int triangle_number;
extern unsigned int* triangle_index;
extern float* vertex_texture;

//extern float* vertex_coord_1;
//extern float* normal_coord_1;
extern float* textures_coord_1;
extern unsigned int triangle_number_1;
extern unsigned int* triangle_index_1;
extern float* vertex_texture_1;

extern float l;

extern int zmin;
extern int zmax;

void createCoordinates(HeightMap heightMap);
void hauteurCam(float x, float y, HeightMap heightMap, float *zCam);
int hauteur(float x, float y, HeightMap heightMap);
void textureTriangle(unsigned int *triangle_index, float* texture_coord, float* vertex_texture, int* text, int* t, int* vertex, int* k, int NO, int NE, int SO, int SE);
void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap);

#endif
