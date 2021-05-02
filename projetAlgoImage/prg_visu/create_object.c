#include "create_object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;
unsigned int triangle_number;
unsigned int* triangle_index;


void createCoordinates(HeightMap heightMap) {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets constituant les triangles (triangle_index)
	// CUBE
	float l=0.1;
	int w =heightMap.w;
	int h=heightMap.h;
	vertex_number =(w*h)*3; 
	triangle_number = (w-1)*(h-1)*2;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
	
	// CONSTRUIRE LES TABLEAUX

int p=0;
int ligne=0;
int colonne=0;
for (float i=-h/2;i<h/2;i++){
	for(float j=-w/2;j<w/2;j++){
		vertex_coord[p]=i*l;
		vertex_coord[1+p]=heightMap.valeursDeGris[ligne][colonne]/(255.);
		vertex_coord[2+p]=j*l;
		normal_coord[p]=i*l;
		normal_coord[1+p]=heightMap.valeursDeGris[ligne][colonne]/(255.);
		normal_coord[2+p]=j*l;
		p+=3;
		colonne++;
	}
	ligne++;
	colonne=0;
}

int k=0;
for (int i=0;i<h-1;i++){
	for(int j=0;j<w-1;j++){
		triangle_index[k]=w*i+j;
		triangle_index[k+1]=w*i+j+1;
		triangle_index[k+2]=w*(i+1)+j;
		triangle_index[k+3]=w*i+j+1;
		triangle_index[k+4]=w*(i+1)+j;
		triangle_index[k+5]=w*(i+1)+j+1;
		k+=6;
	}
}

}

