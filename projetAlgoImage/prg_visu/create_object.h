#ifndef __CREATE_OBJECT_H
#define __CREATE_OBJECT_H

#include "valDeGris.h"
#include "quadtree.h"
#include "light.h"
#include "visu.h"



extern unsigned int vertex_number;
extern float* vertex_coord;

extern float* textures_coord_eau;
extern unsigned int triangle_number_eau;
extern unsigned int* triangle_index_eau;
extern float* vertex_texture_eau;
extern float* colour_eau;


extern float* textures_coord_sable;
extern unsigned int triangle_number_sable;
extern unsigned int* triangle_index_sable;
extern float* vertex_texture_sable;
extern float* colour_sable;


extern float* textures_coord_transition;
extern unsigned int triangle_number_transition;
extern unsigned int* triangle_index_transition;
extern float* vertex_texture_transition;
extern float* colour_transition;


extern float* textures_coord_roche;
extern unsigned int triangle_number_roche;
extern unsigned int* triangle_index_roche;
extern float* vertex_texture_roches;
extern float* colour_roche;


extern float l;

//extern int zmin;
//extern int zmax;

void createCoordinates(HeightMap heightMap);
void hauteurCam(float x, float y, HeightMap heightMap, float *zCam);
int hauteur(float x, float y, HeightMap heightMap);
void textureTriangle(unsigned int *triangle_index, float* textures, float* vertex_texture, int* text, int* t, int* vertex, int* k, int NO, int NE, int SO, int SE, Node* node, Light * light, float* colour);
void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap, Light * light);

#endif
