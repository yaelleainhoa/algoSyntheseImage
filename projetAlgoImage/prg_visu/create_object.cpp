#include "create_object.h"
#include "light.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

unsigned int vertex_number;
float* vertex_coord;

float* textures_coord_eau;
unsigned int triangle_number_eau;
unsigned int* triangle_index_eau;
float* vertex_texture_eau;
float* colour;

float* textures_coord_sable;
unsigned int triangle_number_sable;
unsigned int* triangle_index_sable;
float* vertex_texture_sable;

float* textures_coord_transition;
unsigned int triangle_number_transition;
unsigned int* triangle_index_transition;
float* vertex_texture_transition;

float* textures_coord_roche;
unsigned int triangle_number_roche;
unsigned int* triangle_index_roche;
float* vertex_texture_roches;

int zmin=0;
int zmax=5;

float l;


void createCoordinates(HeightMap heightMap) {

	l=.1;
	int w =heightMap.w;
	int h=heightMap.h;
	vertex_number =(w*h)*3; 
	triangle_number_eau = (w-1)*(h-1)*2/2.;
	triangle_number_sable = (w-1)*(h-1)*2/2.;
	triangle_number_transition = (w-1)*(h-1)*2/2.;
	triangle_number_roche = (w-1)*(h-1)*2/2.;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	//textures_coord = (float*) calloc(sizeof(float),3*triangle_number);
	//triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);

	//vertex_coord_1 = (float*) calloc(sizeof(float),3*vertex_number);
	//textures_coord_1 = (float*) calloc(sizeof(float),3*triangle_number_1);
	//triangle_index_1 = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_1);
	
int p=0;
   
for (int i=0;i<h;i++){
	for(int j=0;j<w;j++){
		vertex_coord[p]=(i-h/2)*l ;
		vertex_coord[2+p]=zmin+heightMap.valeursDeGris[i][j]/(255.)*abs(zmax-zmin);
		vertex_coord[1+p]=(j-w/2)*l;
		p+=3;

	}
}

}


/*

void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap){
		int k=0;
		int text=0;
		int vertex_tex=0;
		int t=0;
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
			float limite = zmin+0.1*abs(zmax-zmin);
			float moyenneHauteur=(coordonnees_quadtree[i].pointNO.z+coordonnees_quadtree[i].pointNE.z+coordonnees_quadtree[i].pointSO.z+coordonnees_quadtree[i].pointSE.z)/4.;
		 	if(moyenneHauteur<limite){
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
		 	}

		 	else{
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

			textureTriangle(triangle_index_1, textures_coord_1, vertex_texture_1, &text, &t, &vertex_tex, &k, NO, NE, SO, SE);

			// vertex_texture_1[vertex_tex]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord];
			// vertex_texture_1[vertex_tex+1]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord+1];
			// vertex_texture_1[vertex_tex+2]=vertex_coord[3*coordonnees_quadtree[i].pointNO.coord+2];
			// vertex_tex+=3;
			// t++;

			// textures_coord_1[text]=0.;
			// textures_coord_1[text+1]=0.;
			// text+=2;


			// vertex_texture_1[vertex_tex]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord];
			// vertex_texture_1[vertex_tex+1]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord+1];
			// vertex_texture_1[vertex_tex+2]=vertex_coord[3*coordonnees_quadtree[i].pointNE.coord+2];
			// vertex_tex+=3;
			// t++;

			// textures_coord_1[text]=1.;
			// textures_coord_1[text+1]=0.;
			// text+=2;


			// vertex_texture_1[vertex_tex]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord];
			// vertex_texture_1[vertex_tex+1]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord+1];
			// vertex_texture_1[vertex_tex+2]=vertex_coord[3*coordonnees_quadtree[i].pointSO.coord+2];
			// vertex_tex+=3;
			// t++;

			// textures_coord_1[text]=0.;
			// textures_coord_1[text+1]=1.;
			// text+=2;

			// vertex_texture_1[vertex_tex]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord];
			// vertex_texture_1[vertex_tex+1]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord+1];
			// vertex_texture_1[vertex_tex+2]=vertex_coord[3*coordonnees_quadtree[i].pointSE.coord+2];
			// vertex_tex+=3;
			// t++;

			// textures_coord_1[text]=1.;
			// textures_coord_1[text+1]=1.;
			// text+=2;

			// triangle_index_1[k]=t;
			// triangle_index_1[k+1]=t+1;
			// triangle_index_1[k+2]=t+2;
			// triangle_index_1[k+3]=t+1;
			// triangle_index_1[k+4]=t+3;
			// triangle_index_1[k+5]=t+2;
			// k+=6;
			

		// }
		 	}
 }
}*/

void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap){
	int k_eau=0;
	int text_eau=0;
	int vertex_tex_eau=0;
	int t_eau=0;

	int k_sable=0;
	int text_sable=0;
	int vertex_tex_sable=0;
	int t_sable=0;

	int k_transition=0;
	int text_transition=0;
	int vertex_tex_transition=0;
	int t_transition=0;

	int k_roche=0;
	int text_roche=0;
	int vertex_tex_roche=0;
	int t_roche=0;
	free(triangle_index_eau);
	free(triangle_index_sable);
	free(triangle_index_transition);
	free(triangle_index_roche);

	free(textures_coord_eau);
	free(textures_coord_sable);
	free(textures_coord_transition);
	free(textures_coord_roche);

	free(vertex_texture_eau);
	free(vertex_texture_sable);
	free(vertex_texture_transition);
	free(vertex_texture_roches);

	triangle_index_eau = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_eau);		
	triangle_index_sable = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_sable);
	triangle_index_transition = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_transition);		
	triangle_index_roche = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number_roche);

	textures_coord_eau = (float*) calloc(sizeof(float),3*triangle_number_eau);
	textures_coord_sable = (float*) calloc(sizeof(float),3*triangle_number_sable);
	textures_coord_transition = (float*) calloc(sizeof(float),3*triangle_number_transition);
	textures_coord_roche = (float*) calloc(sizeof(float),3*triangle_number_roche);

	vertex_texture_eau=(float*)calloc(sizeof(float),3*3*triangle_number_eau);
	vertex_texture_sable=(float*)calloc(sizeof(float),3*3*triangle_number_sable);
	vertex_texture_transition=(float*)calloc(sizeof(float),3*3*triangle_number_transition);
	vertex_texture_roches=(float*)calloc(sizeof(float),3*3*triangle_number_roche);
	for(int i=0; i<taille;i++){
			int NO=coordonnees_quadtree[i].pointNO.coord;
			int NE=coordonnees_quadtree[i].pointNE.coord;
			int SO=coordonnees_quadtree[i].pointSO.coord;
			int SE=coordonnees_quadtree[i].pointSE.coord;
		int largeur=heightMap.w*abs(NO-NE);
		int longueur=abs(NO-SO);
		float limiteEau = zmin+150/(255.)*abs(zmax-zmin);
		float limiteSable= zmin+200/(255.)*abs(zmax-zmin);
		float limiteRoche= zmin+210/(255.)*abs(zmax-zmin);
		float moyenneHauteur=(coordonnees_quadtree[i].pointNO.z+coordonnees_quadtree[i].pointNE.z+coordonnees_quadtree[i].pointSO.z+coordonnees_quadtree[i].pointSE.z)/4.;

		if(moyenneHauteur<limiteEau){
			if(longueur!=largeur){
				if(longueur<largeur){
					int midNO_NE=(int)((NO+NE)/2);
					int midSO_SE=(int)((SO+SE)/2);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, midNO_NE, SO, midSO_SE);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, midNO_NE, NE, midSO_SE, SE);
				}
				else{
					int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
					int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, NE, midNO_SO, midNE_SE);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, midNO_SO, midNE_SE, SO, SE);
				}
			}
			else{
				textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, NE, SO, SE);		
			}
		}

		else{
			if(moyenneHauteur>limiteEau && moyenneHauteur<limiteSable){
				if(longueur!=largeur){
					if(longueur<largeur){
						int midNO_NE=(int)((NO+NE)/2);
						int midSO_SE=(int)((SO+SE)/2);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, midNO_NE, SO, midSO_SE);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, midNO_NE, NE, midSO_SE, SE);
					}
					else{
						int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
						int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, NE, midNO_SO, midNE_SE);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, midNO_SO, midNE_SE, SO, SE);
					}
				}
				else{
					textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, NE, SO, SE);
				}
			}
			else{
				if(moyenneHauteur>limiteSable && moyenneHauteur<limiteRoche){
					if(longueur!=largeur){
						if(longueur<largeur){
							int midNO_NE=(int)((NO+NE)/2);
							int midSO_SE=(int)((SO+SE)/2);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, NO, midNO_NE, SO, midSO_SE);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, midNO_NE, NE, midSO_SE, SE);
						}
						else{
							int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
							int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition,NO, NE, midNO_SO, midNE_SE);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition,midNO_SO, midNE_SE, SO, SE);
						}
					}
					else{
						textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, NO, NE, SO, SE);
					}
				}
				else{
					if(longueur!=largeur){
						if(longueur<largeur){
							// Point3D midNO_NE=createPointFromCoord((int)((NO+NE)/2));
							// Point3D midSO_SE=createPointFromCoord((int)((SO+SE)/2));
							int midNO_NE=(int)((NO+NE)/2);
							int midSO_SE=(int)((SO+SE)/2);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, midNO_NE, SO, midSO_SE);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, midNO_NE, NE, midSO_SE, SE);
						}
						else{
							//Point3D midNO_SO=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w));
							//Point3D midNE_SE=createPointFromCoord((int)(((int)(NO/w)+(int)(SO/w))/2)*w + (NO-(int)(NO/w)*w)+(int)l);
							int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
							int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, NE, midNO_SO, midNE_SE);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, midNO_SO, midNE_SE, SO, SE);
						}
					}
					else{
						textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, NE, SO, SE);
					}
				}
			}

			textureTriangle(triangle_index_1, textures_coord_1, vertex_texture_1, &text_1, &t_1, &vertex_tex_1, &k_1, NO, NE, SO, SE);

		
		}
	}
}
void textureTriangle(unsigned int *triangle_index, float* textures, float* vertex_texture, int* text, int* t, int* vertex, int* nb_triangle, int NO, int NE, int SO, int SE, Node* node, Light * light)
{


void textureTriangle(unsigned int *triangle_index, float* textures, float* vertex_texture, 
														int* text, int* t, int* vertex, int* nb_triangle, int NO, int NE, int SO, int SE){
		Color3f couleurtriangle = finalColor(*light, node->pointNO, node->pointNE, node->pointSO);
		Color3f couleurtriangle2 = finalColor(*light, node->pointNE, node->pointSE, node->pointSO);
		vertex_texture[*vertex]=vertex_coord[3*NO];
		vertex_texture[*vertex+1]=vertex_coord[3*NO+1];
		vertex_texture[*vertex+2]=vertex_coord[3*NO+2];
		colour[*vertex]=couleurtriangle.r;
		colour[*vertex+1]=couleurtriangle.v;
		colour[*vertex+2]=couleurtriangle.b;
		(*vertex)+=3;
		textures[*text]=0.;
		textures[*text+1]=0.;
		(*text)+=2;


		vertex_texture[*vertex]=vertex_coord[3*NE];
		vertex_texture[*vertex+1]=vertex_coord[3*NE+1];
		vertex_texture[*vertex+2]=vertex_coord[3*NE+2];
		colour[*vertex]=(couleurtriangle.r+couleurtriangle2.r)/2.0;
		colour[*vertex+1]=(couleurtriangle.v+couleurtriangle2.v)/2.0;
		colour[*vertex+2]=(couleurtriangle.b+couleurtriangle2.b)/2.0;
		(*vertex)+=3;

		textures[*text]=1.;
		textures[*text+1]=0.;
		(*text)+=2;


		vertex_texture[*vertex]=vertex_coord[3*SO];
		vertex_texture[*vertex+1]=vertex_coord[3*SO+1];
		vertex_texture[*vertex+2]=vertex_coord[3*SO+2];
		colour[*vertex]=(couleurtriangle.r+couleurtriangle2.r)/2.0;
		colour[*vertex+1]=(couleurtriangle.v+couleurtriangle2.v)/2.0;
		colour[*vertex+2]=(couleurtriangle.b+couleurtriangle2.b)/2.0;
		(*vertex)+=3;

		textures[*text]=0.;
		textures[*text+1]=1.;
		(*text)+=2;

		vertex_texture[*vertex]=vertex_coord[3*SE];
		vertex_texture[*vertex+1]=vertex_coord[3*SE+1];
		vertex_texture[*vertex+2]=vertex_coord[3*SE+2];
		colour[*vertex]=couleurtriangle2.r;
		colour[*vertex+1]=couleurtriangle2.v;
		colour[*vertex+2]=couleurtriangle2.b;
		(*vertex)+=3;

		textures[*text]=1.;
		textures[*text+1]=1.;
		(*text)+=2;

		triangle_index[*nb_triangle]=*t;
		triangle_index[*nb_triangle+1]=*t+1;
		triangle_index[*nb_triangle+2]=*t+2;
		triangle_index[*nb_triangle+3]=*t+1;
		triangle_index[*nb_triangle+4]=*t+3;
		triangle_index[*nb_triangle+5]=*t+2;
		(*nb_triangle)+=6;
		(*t)+=4;
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


void hauteurCam(float x, float y, HeightMap heightMap, float *zCam){
	int h=heightMap.h;
	int w=heightMap.w;
	int coord=3*(w*(int)(x/l+h/2)+(int)(y/l+w/2));
	*zCam=vertex_coord[coord+2];
}

int hauteur(float x, float y, HeightMap heightMap){
	int h=heightMap.h;
	int w=heightMap.w;
	int coord=3*(w*(int)(x/l+h/2)+(int)(y/l+w/2));
	return vertex_coord[coord+2];
}