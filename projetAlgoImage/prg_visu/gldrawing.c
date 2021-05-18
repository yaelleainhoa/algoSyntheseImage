#include "gldrawing.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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

void glDrawObject() {
	float white[3] = {1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	char * sources={"images/sol.jpg"};
	GLuint textureSol;
		glEnable(GL_TEXTURE_2D);
        SDL_Surface* image=IMG_Load(sources);
        glGenTextures(1, &textureSol);
        glBindTexture(GL_TEXTURE_2D, textureSol);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, textureSol);

	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
	glNormalPointer(GL_FLOAT,0,normal_coord);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(3, GL_FLOAT, 0, textures_coord);
	glDrawElements(GL_TRIANGLES,3*triangle_number,GL_UNSIGNED_INT,triangle_index);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
