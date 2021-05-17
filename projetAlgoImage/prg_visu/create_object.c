#include "create_object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;
float* textures_coord;
unsigned int triangle_number;
unsigned int* triangle_index;
float l;


void createCoordinates(HeightMap heightMap) {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets constituant les triangles (triangle_index)
	// CUBE
	l=.1;
	int w =heightMap.w;
	int h=heightMap.h;
	vertex_number =(w*h)*3; 
	triangle_number = (w-1)*(h-1)*2;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	textures_coord = (float*) calloc(sizeof(float),2*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
	
	// CONSTRUIRE LES TABLEAUX

int p=0;
   
for (int i=0;i<h;i++){
	for(int j=0;j<w;j++){
		vertex_coord[p]=(i-h/2)*l ;
		vertex_coord[2+p]=-2+heightMap.valeursDeGris[i][j]/(255.);
		vertex_coord[1+p]=(j-w/2)*l;
		normal_coord[p]=(i-h/2)*l ;
		normal_coord[2+p]=-2+heightMap.valeursDeGris[i][j]/(255.);
		normal_coord[1+p]=(j-w/2)*l ;
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


for(int c=0; c<vertex_number; c+=6){
		textures_coord[c]=0.0;
		textures_coord[c+1]=1.0;

		textures_coord[c+2]=1.0;
		textures_coord[c+3]=1.0;

		textures_coord[c+4]=0.0;
		textures_coord[c+5]=0.0;
}

}
