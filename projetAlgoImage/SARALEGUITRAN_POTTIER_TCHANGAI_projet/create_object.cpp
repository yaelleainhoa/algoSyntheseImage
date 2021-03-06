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
float* colour_eau;

float* textures_coord_sable;
unsigned int triangle_number_sable;
unsigned int* triangle_index_sable;
float* vertex_texture_sable;
float* colour_sable;

float* textures_coord_transition;
unsigned int triangle_number_transition;
unsigned int* triangle_index_transition;
float* vertex_texture_transition;
float* colour_transition;

float* textures_coord_roche;
unsigned int triangle_number_roche;
unsigned int* triangle_index_roche;
float* vertex_texture_roches;
float* colour_roche;

float l;

void createCoordinates(HeightMap heightMap) {

	l=xsize/heightMap.w;
	int w =heightMap.w;
	int h=heightMap.h;
	vertex_number =(w*h)*3; 
	triangle_number_eau = (w-1)*(h-1)*2/2.;
	triangle_number_sable = (w-1)*(h-1)*2/2.;
	triangle_number_transition = (w-1)*(h-1)*2/2.;
	triangle_number_roche = (w-1)*(h-1)*2/2.;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
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

void tracerTriangles(Node *coordonnees_quadtree, int taille, HeightMap heightMap, Light *light){
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

	colour_eau=(float*)calloc(sizeof(float),3*3*triangle_number_eau);
	colour_sable=(float*)calloc(sizeof(float),3*3*triangle_number_sable);
	colour_transition=(float*)calloc(sizeof(float),3*3*triangle_number_transition);
	colour_roche=(float*)calloc(sizeof(float),3*3*triangle_number_roche);

	for(int i=0; i<taille;i++){
			int NO=coordonnees_quadtree[i].pointNO.coord;
			int NE=coordonnees_quadtree[i].pointNE.coord;
			int SO=coordonnees_quadtree[i].pointSO.coord;
			int SE=coordonnees_quadtree[i].pointSE.coord;
		int largeur=heightMap.w*abs(NO-NE);
		int longueur=abs(NO-SO);
		float limiteEau = zmin+80/(255.)*abs(zmax-zmin);
		float limiteSable= zmin+130/(255.)*abs(zmax-zmin);
		float limiteRoche= zmin+160/(255.)*abs(zmax-zmin);

		//on applique une texture differente selon la hauteur max du quadtree
		float maxHauteur=max(max(coordonnees_quadtree[i].pointNO.z,coordonnees_quadtree[i].pointNE.z),max(coordonnees_quadtree[i].pointSO.z,coordonnees_quadtree[i].pointSE.z));
		if(maxHauteur<=limiteEau){
			if(longueur!=largeur){
				if(longueur<largeur){
					int midNO_NE=(int)((NO+NE)/2);
					int midSO_SE=(int)((SO+SE)/2);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, midNO_NE, SO, midSO_SE, &coordonnees_quadtree[i], light, colour_eau);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, midNO_NE, NE, midSO_SE, SE, &coordonnees_quadtree[i], light, colour_eau);
				}
				else{
					int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
					int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, NE, midNO_SO, midNE_SE, &coordonnees_quadtree[i], light, colour_eau);
					textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, midNO_SO, midNE_SE, SO, SE, &coordonnees_quadtree[i], light, colour_eau);
				}
			}
			else{
				textureTriangle(triangle_index_eau, textures_coord_eau, vertex_texture_eau, &text_eau, &t_eau, &vertex_tex_eau, &k_eau, NO, NE, SO, SE, &coordonnees_quadtree[i], light, colour_eau);		
			}
		}

		else{
			if(maxHauteur>limiteEau && maxHauteur<=limiteSable){
				if(longueur!=largeur){
					if(longueur<largeur){
						int midNO_NE=(int)((NO+NE)/2);
						int midSO_SE=(int)((SO+SE)/2);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, midNO_NE, SO, midSO_SE, &coordonnees_quadtree[i], light, colour_sable);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, midNO_NE, NE, midSO_SE, SE, &coordonnees_quadtree[i], light, colour_sable);
					}
					else{
						int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
						int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, NE, midNO_SO, midNE_SE, &coordonnees_quadtree[i], light, colour_sable);
						textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, midNO_SO, midNE_SE, SO, SE, &coordonnees_quadtree[i], light, colour_sable);
					}
				}
				else{
					textureTriangle(triangle_index_sable, textures_coord_sable, vertex_texture_sable, &text_sable, &t_sable, &vertex_tex_sable, &k_sable, NO, NE, SO, SE, &coordonnees_quadtree[i], light, colour_sable);
				}
			}
			else{
				if(maxHauteur>limiteSable && maxHauteur<=limiteRoche){
					if(longueur!=largeur){
						if(longueur<largeur){
							int midNO_NE=(int)((NO+NE)/2);
							int midSO_SE=(int)((SO+SE)/2);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, NO, midNO_NE, SO, midSO_SE, &coordonnees_quadtree[i], light, colour_transition);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, midNO_NE, NE, midSO_SE, SE, &coordonnees_quadtree[i], light, colour_transition);
						}
						else{
							int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
							int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition,NO, NE, midNO_SO, midNE_SE, &coordonnees_quadtree[i], light, colour_transition);
							textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition,midNO_SO, midNE_SE, SO, SE, &coordonnees_quadtree[i], light, colour_transition);
						}
					}
					else{
						textureTriangle(triangle_index_transition, textures_coord_transition, vertex_texture_transition, &text_transition, &t_transition, &vertex_tex_transition, &k_transition, NO, NE, SO, SE, &coordonnees_quadtree[i], light, colour_transition);
					}
				}
				else{
					if(longueur!=largeur){
						if(longueur<largeur){
							int midNO_NE=(int)((NO+NE)/2);
							int midSO_SE=(int)((SO+SE)/2);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, midNO_NE, SO, midSO_SE, &coordonnees_quadtree[i], light, colour_roche);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, midNO_NE, NE, midSO_SE, SE, &coordonnees_quadtree[i], light, colour_roche);
						}
						else{
							int midNO_SO=(int)(((int)(NO/heightMap.w)+(int)(SO/heightMap.w))/2)*heightMap.w + (NO-(int)(NO/heightMap.w)*heightMap.w);
							int midNE_SE=(int)(((int)(NE/heightMap.w)+(int)(SE/heightMap.w))/2)*heightMap.w + (NE-(int)(NE/heightMap.w)*heightMap.w);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, NE, midNO_SO, midNE_SE, &coordonnees_quadtree[i], light, colour_roche);
							textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, midNO_SO, midNE_SE, SO, SE, &coordonnees_quadtree[i], light, colour_roche);
						}
					}
					else{
						textureTriangle(triangle_index_roche, textures_coord_roche, vertex_texture_roches, &text_roche, &t_roche, &vertex_tex_roche, &k_roche, NO, NE, SO, SE, &coordonnees_quadtree[i], light, colour_roche);
					}	
				}
			}
		}
	}
}


void textureTriangle(unsigned int *triangle_index, float* textures, float* vertex_texture, int* text, int* t, int* vertex, int* nb_triangle, int NO, int NE, int SO, int SE, Node* node, Light * light, float* colour){
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















