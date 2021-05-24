#include "create_object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

unsigned int vertex_number;
float* vertex_coord;
float* normal_coord;
float* textures_coord;
unsigned int triangle_number;
unsigned int* triangle_index;

float* vertex_coord_1;
float* normal_coord_1;
float* textures_coord_1;
unsigned int triangle_number_1;
unsigned int* triangle_index_1;

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
	triangle_number = (w-1)*(h-1)*2/2.;
	triangle_number_1 = (w-1)*(h-1)*2/2.;
	int zmin=-3;
	int zmax=0;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	textures_coord = (float*) calloc(sizeof(float),3*triangle_number);
	//triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);

	vertex_coord_1 = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord_1 = (float*) calloc(sizeof(float),3*vertex_number);
	textures_coord_1 = (float*) calloc(sizeof(float),3*triangle_number_1);
	triangle_index_1 = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_1);
	
	// CONSTRUIRE LES TABLEAUX

int p=0;
int text=0;
float text_coord[4][2]={{0.,0.},{1.,0.},{0.,1.},{1.,1.}};
float text_coord_i[2][2];//={0.,0.};
   
for (int i=0;i<h;i++){
	if (i%2==0){
		text_coord_i[0][0]=text_coord[0][0];
		text_coord_i[0][1]=text_coord[0][1];
		text_coord_i[1][0]=text_coord[1][0];
		text_coord_i[1][1]=text_coord[1][1];
	}
	else{
		text_coord_i[0][0]=text_coord[2][0];
		text_coord_i[0][1]=text_coord[2][1];
		text_coord_i[1][0]=text_coord[3][0];
		text_coord_i[1][1]=text_coord[3][1];
	}
	for(int j=0;j<w;j++){
		vertex_coord[p]=(i-h/2)*l ;
		vertex_coord[2+p]=zmin+heightMap.valeursDeGris[i][j]/(255.)*abs(zmax-zmin);
		vertex_coord[1+p]=(j-w/2)*l;
		normal_coord[p]=(i-h/2)*l ;
		normal_coord[2+p]=zmin+heightMap.valeursDeGris[i][j]/(255.)*abs(zmax-zmin);
		normal_coord[1+p]=(j-w/2)*l ;

		vertex_coord_1[p]=(i-h/2)*l ;
		vertex_coord_1[2+p]=zmin+heightMap.valeursDeGris[i][j]/(255.)*abs(zmax-zmin);
		vertex_coord_1[1+p]=(j-w/2)*l;
		normal_coord_1[p]=(i-h/2)*l ;
		normal_coord_1[2+p]=zmin+heightMap.valeursDeGris[i][j]/(255.)*abs(zmax-zmin);
		normal_coord_1[1+p]=(j-w/2)*l ;
		p+=3;
		if(j%2==0){
			textures_coord[text]=text_coord_i[0][0];
			textures_coord[text+1]=text_coord_i[0][1];

			textures_coord_1[text]=text_coord_i[0][0];
			textures_coord_1[text+1]=text_coord_i[0][1];
		}
		else{
			textures_coord[text]=text_coord_i[1][0];
			textures_coord[text+1]=text_coord_i[1][1];

			textures_coord_1[text]=text_coord_i[1][0];
			textures_coord_1[text+1]=text_coord_i[1][1];
		}
		text+=2;

	}
}


// int k=0;
// int k_1=0;
// for(int i=0;i<h-1;i++){
// 	for(int j=0;j<w-1;j++){
// 		if(j%2==0){
// 			triangle_index[k]=w*i+j;
// 			triangle_index[k+1]=w*i+j+1;
// 			triangle_index[k+2]=w*(i+1)+j;
// 			triangle_index[k+3]=w*i+j+1;
// 			triangle_index[k+4]=w*(i+1)+j;
// 			triangle_index[k+5]=w*(i+1)+j+1;
// 			k+=6;
// 		}
// 		else{
// 			triangle_index_1[k_1]=w*i+j;
// 			triangle_index_1[k_1+1]=w*i+j+1;
// 			triangle_index_1[k_1+2]=w*(i+1)+j;
// 			triangle_index_1[k_1+3]=w*i+j+1;
// 			triangle_index_1[k_1+4]=w*(i+1)+j;
// 			triangle_index_1[k_1+5]=w*(i+1)+j+1;
//  		k_1+=6;
// 		}

// }
// }
}



//Permet de retrouver la hauteur en fonction de x et y (bcp de tests pour vérifier, tout n'est pas utile)
// float x=2.;
// float y=3.2;
// printf("on rentre x=%f et y=%f \n", x,y);
// int newi=(int)(x/l+h/2); ///ICI on a i en fonction de x
// int newj=(int)(y/l+w/2); ///ICI on a j en fonction de y
// printf("ces x et y correspondent à i=%d, et j=%d \n", newi,newj);
// int coord = 3*(w*(int)(x/l+h/2)+(int)(y/l+w/2));
// float newx=vertex_coord[coord];
// float newy=vertex_coord[coord+1];
// printf("on retombe bien sur x=%f et y=%f\n", newx, newy);
// float zvalue=vertex_coord[coord+2];
// printf("ce qui donne z = %f", zvalue);



// void tracerTriangles(Node (*coordonnees_quadtree)[], int taille){
// 		int k=0;
// 		int text=0;
// 		triangle_index = (unsigned int*) realloc(triangle_index, sizeof(unsigned int)*3*2*taille);
// 		textures_coord = (float*) realloc(textures_coord,sizeof(float)*2*taille);
// 		for(int i=0; i<taille;i++){
// 			    int NO=(*coordonnees_quadtree[i])->pointNO.coord;
// 				int NE=(*coordonnees_quadtree[i])->pointNE.coord;
// 				int SO=(*coordonnees_quadtree[i])->pointSO.coord;
// 				int SE=(*coordonnees_quadtree[i])->pointSE.coord;
// 			int largeur=abs(NO-NE);
// 			int longueur=abs(NO-SO);
// 			if(longueur!=largeur){
// 				if(longueur<largeur){
// 					Point3D midNO_NE=createPointFromCoord();
// 					Point3D midSO_SE=createPointFromCoord();
// 					triangle_index[k]=NO;
// 					triangle_index[k+1]=midNO_NE;
// 					triangle_index[k+2]=SO;
// 					triangle_index[k+3]=midNO_NE;
// 					triangle_index[k+4]=SO;
// 					triangle_index[k+5]=midSO_SE;

// 					triangle_index[k+6]=midNO_NE;
// 					triangle_index[k+7]=NE;
// 					triangle_index[k+8]=midSO_SE;
// 					triangle_index[k+9]=NE;
// 					triangle_index[k+10]=midSO_SE;
// 					triangle_index[k+11]=SE;
// 					k+=12;
// 				}
// 				else{
// 					Point3D midNO_SO=createPointFromCoord();
// 					Point3D midNE_SE=createPointFromCoord();
// 					triangle_index[k]=NO;
// 					triangle_index[k+1]=midNO_NE;
// 					triangle_index[k+2]=SO;
// 					triangle_index[k+3]=midNO_NE;
// 					triangle_index[k+4]=SO;
// 					triangle_index[k+5]=midSO_SE;

// 					triangle_index[k+6]=midNO_NE;
// 					triangle_index[k+7]=NE;
// 					triangle_index[k+8]=midSO_SE;
// 					triangle_index[k+9]=NE;
// 					triangle_index[k+10]=midSO_SE;
// 					triangle_index[k+11]=SE;
// 					k+=12;
// 				}
// 			}
// 			triangle_index[k]=(*coordonnees_quadtree)[i];
// 			triangle_index[k+1]=(*coordonnees_quadtree)[i+1];
// 			triangle_index[k+2]=(*coordonnees_quadtree)[i+2];
// 			triangle_index[k+3]=(*coordonnees_quadtree)[i+1];
// 			triangle_index[k+4]=(*coordonnees_quadtree)[i+2];
// 			triangle_index[k+5]=(*coordonnees_quadtree)[i+3];
// 			k+=6;

// 			//marche pas, demander au prof
// 			// textures_coord[text]=0.0;
// 			// textures_coord[text+1]=0.0;

// 			// textures_coord[text+2]=1.0;
// 			// textures_coord[text+3]=0.0;

// 			// textures_coord[text+4]=1.0;
// 			// textures_coord[text+5]=1.0;

// 			// textures_coord[text+6]=0.0;
// 			// textures_coord[text+7]=1.0;
// 			// text+=8;
// 		}

// 		//SI jamais on fait plutôt un tableau de node, on aurait plutôt
// 		// for(int i=0; i<taille;i++){
// 		// 	triangle_index[k]=(*coordonnees_quadtree)[i].pointNO;
// 		// 	triangle_index[k+1]=(*coordonnees_quadtree)[i].pointNE;
// 		// 	triangle_index[k+2]=(*coordonnees_quadtree)[i].pointSO;
// 		// 	triangle_index[k+3]=(*coordonnees_quadtree)[i].pointNE;
// 		// 	triangle_index[k+4]=(*coordonnees_quadtree)[i].pointSE;
// 		// 	triangle_index[k+5]=(*coordonnees_quadtree)[i].pointSO;
// 		// 	k+=6;
// 		// }

// }

//Pas encore opti
void tracerTriangles(Node *coordonnees_quadtree, int taille){
		int k=0;
		int text=0;
		free(triangle_index);
		triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
		//triangle_index = (unsigned int*) realloc(triangle_index, sizeof(int)*3*2*taille);
		//textures_coord = (float*) realloc(textures_coord,sizeof(float)*2*taille);
		for(int i=0; i<taille;i++){
			triangle_index[k]=coordonnees_quadtree[i].pointNO.coord;
			triangle_index[k+1]=coordonnees_quadtree[i].pointNE.coord;
			triangle_index[k+2]=coordonnees_quadtree[i].pointSO.coord;
			triangle_index[k+3]=coordonnees_quadtree[i].pointNE.coord;
			triangle_index[k+4]=coordonnees_quadtree[i].pointSE.coord;
			triangle_index[k+5]=coordonnees_quadtree[i].pointSO.coord;
			k+=6;
		}
}


void hauteur(float x, float y, HeightMap heightMap, float *zCam){
	int h=heightMap.h;
	int w=heightMap.w;
	int coord=3*(w*(int)(x/l+h/2)+(int)(y/l+w/2));
	*zCam=vertex_coord[coord+2];
}