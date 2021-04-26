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

void createCoordinates() {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets constituant les triangles (triangle_index)
	// CUBE
	int w=20;
	int h=20;
	float l=0.1;
	vertex_number =(w*h)*3; // A CHANGER
	triangle_number = (w-1)*(h-1)*2*3; // A CHANGER
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
	
	// CONSTRUIRE LES TABLEAUX

srand(5);

float hauteur[h][w];	
for (int i=0;i<h;i++){
	for(int j=0;j<w;j++){
		hauteur[i][j]=0;
	}
}

hauteur[0][0]=0.05;
hauteur[1][0]=0.05;
hauteur[0][3]=0.05;
hauteur[7][0]=0.05;

int p=0;
for (int i=0;i<h;i++){
	for(int j=0;j<w;j++){
		vertex_coord[p]=i*l;
		vertex_coord[1+p]=hauteur[i][j];
		vertex_coord[2+p]=j*l;
		p+=3;
	}
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
