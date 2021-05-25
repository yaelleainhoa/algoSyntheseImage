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
float* vertex_texture_1;

int zmin=-4;
int zmax=0;

float l;


void createCoordinates(HeightMap heightMap) {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets constituant les triangles (triangle_index)
	// CUBE
	l=.2;
	int w =heightMap.w;
	int h=heightMap.h;
	vertex_number =(w*h)*3; 
	triangle_number = (w-1)*(h-1)*2/2.;
	triangle_number_1 = (w-1)*(h-1)*2/2.;
	
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
//int text=0;
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
		// if(j%2==0){
		// 	textures_coord[text]=text_coord_i[0][0];
		// 	textures_coord[text+1]=text_coord_i[0][1];

		// 	textures_coord_1[text]=text_coord_i[0][0];
		// 	textures_coord_1[text+1]=text_coord_i[0][1];
		// }
		// else{
		// 	textures_coord[text]=text_coord_i[1][0];
		// 	textures_coord[text+1]=text_coord_i[1][1];

		// 	textures_coord_1[text]=text_coord_i[1][0];
		// 	textures_coord_1[text+1]=text_coord_i[1][1];
		// }
		// text+=2;

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



void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap){
		int k=0;
		int text=0;
		int vertex_tex=0;
		free(triangle_index);
		free(textures_coord_1);
;		triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
		textures_coord_1 = (float*) calloc(sizeof(float),3*triangle_number_1);
		vertex_texture_1=(float*)calloc(sizeof(float),3*3*triangle_number);
		for(int i=0; i<taille;i++){
			    int NO=coordonnees_quadtree[i].pointNO.coord;
				int NE=coordonnees_quadtree[i].pointNE.coord;
				int SO=coordonnees_quadtree[i].pointSO.coord;
				int SE=coordonnees_quadtree[i].pointSE.coord;
			int largeur=heightMap.w*abs(NO-NE);
			int longueur=abs(NO-SO);
			float limite = zmin+0.5*abs(zmax-zmin);
			float moyenneHauteur=(coordonnees_quadtree[i].pointNO.z+coordonnees_quadtree[i].pointNE.z+coordonnees_quadtree[i].pointSO.z+coordonnees_quadtree[i].pointSE.z)/4.;
		// 	if(moyenneHauteur<limite){
		// 	if(longueur!=largeur){
		// 		if(longueur<largeur){
		// 			int midNO_NE=(int)((NO+NE)/2);
		// 			int midSO_SE=(int)((SO+SE)/2);
		// 			triangle_index[k]=NO;
		// 			triangle_index[k+1]=midNO_NE;
		// 			triangle_index[k+2]=SO;
		// 			triangle_index[k+3]=midNO_NE;
		// 			triangle_index[k+4]=midSO_SE;
		// 			triangle_index[k+5]=SO;

		// 			triangle_index[k+6]=midNO_NE;
		// 			triangle_index[k+7]=NE;
		// 			triangle_index[k+8]=midSO_SE;
		// 			triangle_index[k+9]=NE;
		// 			triangle_index[k+10]=SE;
		// 			triangle_index[k+11]=midSO_SE;
		// 			k+=12;
		// 		}
		// 		else{
		// 			int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
		// 			int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
		// 			triangle_index_1[k]=NO;
		// 			triangle_index_1[k+1]=NE;
		// 			triangle_index_1[k+2]=midNO_SO;
		// 			triangle_index_1[k+3]=NE;
		// 			triangle_index_1[k+4]=midNE_SE;
		// 			triangle_index_1[k+5]=midNO_SO;

		// 			triangle_index_1[k+6]=midNO_SO;
		// 			triangle_index_1[k+7]=midNE_SE;
		// 			triangle_index_1[k+8]=SO;
		// 			triangle_index[k+9]=midNE_SE;
		// 			triangle_index[k+10]=SE;
		// 			triangle_index[k+11]=SO;
		// 			k+=12;
		// 		}
		// 	}
		// 	else{
		// 	triangle_index[k]=coordonnees_quadtree[i].pointNO.coord;
		// 	triangle_index[k+1]=coordonnees_quadtree[i].pointNE.coord;
		// 	triangle_index[k+2]=coordonnees_quadtree[i].pointSO.coord;
		// 	triangle_index[k+3]=coordonnees_quadtree[i].pointNE.coord;
		// 	triangle_index[k+4]=coordonnees_quadtree[i].pointSE.coord;
		// 	triangle_index[k+5]=coordonnees_quadtree[i].pointSO.coord;
		// 	k+=6;

			
		// }
		// 	}

		// 	else{
		// 					if(longueur!=largeur){
		// 		if(longueur<largeur){
		// 			// Point3D midNO_NE=createPointFromCoord((int)((NO+NE)/2));
		// 			// Point3D midSO_SE=createPointFromCoord((int)((SO+SE)/2));
		// 			int midNO_NE=(int)((NO+NE)/2);
		// 			int midSO_SE=(int)((SO+SE)/2);

		// 			triangle_index_1[k]=NO;
		// 			triangle_index_1[k+1]=midNO_NE;
		// 			triangle_index_1[k+2]=SO;
		// 			triangle_index_1[k+3]=midNO_NE;
		// 			triangle_index_1[k+4]=midSO_SE;
		// 			triangle_index_1[k+5]=SO;

		// 			triangle_index_1[k+6]=midNO_NE;
		// 			triangle_index_1[k+7]=NE;
		// 			triangle_index_1[k+8]=midSO_SE;
		// 			triangle_index_1[k+9]=NE;
		// 			triangle_index_1[k+10]=SE;
		// 			triangle_index_1[k+11]=midSO_SE;
		// 			k+=12;
		// 		}
		// 		else{
		// 			//Point3D midNO_SO=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w));
		// 			//Point3D midNE_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l);
		// 			int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
		// 			int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
		// 			triangle_index_1[k]=NO;
		// 			triangle_index_1[k+1]=NE;
		// 			triangle_index_1[k+2]=midNO_SO;
		// 			triangle_index_1[k+3]=NE;
		// 			triangle_index_1[k+4]=midNE_SE;
		// 			triangle_index_1[k+5]=midNO_SO;

		// 			triangle_index_1[k+6]=midNO_SO;
		// 			triangle_index_1[k+7]=midNE_SE;
		// 			triangle_index_1[k+8]=SO;
		// 			triangle_index[k+9]=midNE_SE;
		// 			triangle_index[k+10]=SE;
		// 			triangle_index[k+11]=SO;
		// 			k+=12;
		// 		}
		// 	}
		// 	else{
			vertex_texture_1[vertex_tex]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord];
			vertex_texture_1[vertex_tex+1]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord+1];
			vertex_texture_1[vertex_tex+2]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord+2];
			//vertex_tex+=3;

			// textures_coord_1[text]=0.;
			// textures_coord_1[text+1]=0.;
			// text+=2;

			

			vertex_texture_1[vertex_tex+3]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord];
			vertex_texture_1[vertex_tex+4]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord+1];
			vertex_texture_1[vertex_tex+5]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord+2];
			//vertex_tex+=3;

			// textures_coord_1[text]=1.;
			// textures_coord_1[text+1]=0.;
			// text+=2;

			


			vertex_texture_1[vertex_tex+6]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord];
			vertex_texture_1[vertex_tex+7]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord+1];
			vertex_texture_1[vertex_tex+8]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord+2];
			//vertex_tex+=3;

			// textures_coord_1[text]=1.;
			// textures_coord_1[text+1]=1.;
			// text+=2;

			

			vertex_texture_1[vertex_tex+9]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord];
			vertex_texture_1[vertex_tex+10]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord+1];
			vertex_texture_1[vertex_tex+11]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord+2];
			vertex_tex+=12;

			// textures_coord_1[text]=0.;
			// textures_coord_1[text+1]=1.;
			// text+=2;

			


			triangle_index_1[k]=vertex_x;
			triangle_index_1[k+1]=vertex_x+3;
			triangle_index_1[k+2]=vertex_x+6;
			triangle_index_1[k+3]=vertex_x+3;
			triangle_index_1[k+4]=vertex_x+9;
			triangle_index_1[k+5]=vertex_x+6;
			k+=6;
			

			// textures_coord_1[2*coordonnees_quadtree[i].pointNE.coord]=1.;
			// textures_coord_1[2*coordonnees_quadtree[i].pointNE.coord+1]=0.;

			// textures_coord_1[2*coordonnees_quadtree[i].pointSO.coord]=0.;
			// textures_coord_1[2*coordonnees_quadtree[i].pointSO.coord+1]=1.;

			// textures_coord_1[2*coordonnees_quadtree[i].pointNE.coord]=1.;
			// textures_coord_1[2*coordonnees_quadtree[i].pointNE.coord+1]=0.;

			// textures_coord_1[2*coordonnees_quadtree[i].pointSE.coord]=1.;
			// textures_coord_1[2*coordonnees_quadtree[i].pointSE.coord+1]=1.;

			// textures_coord_1[2*coordonnees_quadtree[i].pointSO.coord]=0.;
			// textures_coord_1[2*coordonnees_quadtree[i].pointSO.coord+1]=1.;


		
		// }
		// 	}
 }
}

// //Pas encore opti
// void tracerTriangles(Node *coordonnees_quadtree, int taille,HeightMap heightMap){
// 		int k=0;
// 		int text=0;
// 		free(triangle_index);
// 		triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
// 		//triangle_index = (unsigned int*) realloc(triangle_index, sizeof(int)*3*2*taille);
// 		//textures_coord = (float*) realloc(textures_coord,sizeof(float)*2*taille);
// 		for(int i=0; i<taille;i++){
// 			triangle_index[k]=coordonnees_quadtree[i].pointNO.coord;
// 			triangle_index[k+1]=coordonnees_quadtree[i].pointNE.coord;
// 			triangle_index[k+2]=coordonnees_quadtree[i].pointSO.coord;
// 			triangle_index[k+3]=coordonnees_quadtree[i].pointNE.coord;
// 			triangle_index[k+4]=coordonnees_quadtree[i].pointSE.coord;
// 			triangle_index[k+5]=coordonnees_quadtree[i].pointSO.coord;
// 			k+=6;
// 		}
// }


void hauteur(float x, float y, HeightMap heightMap, float *zCam){
	int h=heightMap.h;
	int w=heightMap.w;
	int coord=3*(w*(int)(x/l+h/2)+(int)(y/l+w/2));
	*zCam=vertex_coord[coord+2];
}