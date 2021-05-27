#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "objet.h"
#include "visu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


void arbre(float x, float y, float z, GLuint texture){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(x,y,z);
		glRotatef(90-longitude*180/M_PI, 0. ,0. ,1. );
		glColor4f(1,1,1,1);
        glScalef(1.,1.,1.);
		glPushMatrix();
			glBegin(GL_POLYGON);
				glTexCoord2f(0.,0.); glVertex3f(0., -0.5, 1.);
				glTexCoord2f(1.,0.); glVertex3f(0., 0.5, 1.);
				glTexCoord2f(1.,1.); glVertex3f(0., 0.5, 0.);
				glTexCoord2f(0.,1.); glVertex3f(0., -0.5, 0.);				
        	glEnd();
		glPopMatrix();
	glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}