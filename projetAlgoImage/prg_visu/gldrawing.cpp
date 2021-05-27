#include "gldrawing.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "create_object.h"

#include <stdio.h>

void glDrawRepere(float length) {
	// dessin du repère
	glBegin(GL_LINES);
		//Red - x
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
		//Green - y
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
		//Blue - z
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

void glDrawObject_eau(GLuint textureSol) {//eau 
	float white[3] = {1.0,1.0,1.0}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white); 
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0); 
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, textureSol);
	glVertexPointer(3,GL_FLOAT,0,vertex_texture_eau); 
	glColorPointer(3,GL_FLOAT,0,colour_eau); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
    glTexCoordPointer(2, GL_FLOAT, 0, textures_coord_eau); 
	glDrawElements(GL_TRIANGLES,3*triangle_number_eau,GL_UNSIGNED_INT,triangle_index_eau); 
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
} 
 
 
void glDrawObject_sable(GLuint textureSol) {//sable 
	float white[3] = {1.0,1.0,1.0}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white); 
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0); 
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, textureSol); 
	glVertexPointer(3,GL_FLOAT,0,vertex_texture_sable); 
	glColorPointer(3,GL_FLOAT,0,colour_sable); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
    glTexCoordPointer(2, GL_FLOAT, 0, textures_coord_sable); 
	glDrawElements(GL_TRIANGLES,3*triangle_number_sable,GL_UNSIGNED_INT,triangle_index_sable); 
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
} 
 

 void glDrawObject_transition(GLuint textureSol) {//transition 
	float white[3] = {1.0,1.0,1.0}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white); 
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0); 
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, textureSol); 
	glVertexPointer(3,GL_FLOAT,0,vertex_texture_transition); 
	glColorPointer(3,GL_FLOAT,0,colour_transition); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
	glTexCoordPointer(2, GL_FLOAT, 0, textures_coord_transition); 
	glDrawElements(GL_TRIANGLES,3*triangle_number_transition,GL_UNSIGNED_INT,triangle_index_transition); 
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
} 

void glDrawObject_roche(GLuint textureSol) {//roche 
	float white[3] = {1.0,1.0,1.0}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white); 
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0); 
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, textureSol); 
	glVertexPointer(3,GL_FLOAT,0,vertex_texture_roches); 
	glColorPointer(3,GL_FLOAT,0,colour_roche); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); 
    glTexCoordPointer(2, GL_FLOAT, 0, textures_coord_roche); 
	glDrawElements(GL_TRIANGLES,3*triangle_number_roche,GL_UNSIGNED_INT,triangle_index_roche); 
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
} 