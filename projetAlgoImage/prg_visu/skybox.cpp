#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "skybox.h"
#include <iostream>
#include <fstream>
#include <string>

void skyBoxZ(float x, float y, float z, GLuint texture, float largeur_skybox){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
		glScalef(1.,1.,1.);
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x,y,z);
            glTexCoord2f(1.,0.);
            glVertex3f(x+largeur_skybox,y,z);
            glTexCoord2f(1.,1.);
            glVertex3f(x+largeur_skybox,y-largeur_skybox,z);
            glTexCoord2f(0.,1.);
            glVertex3f(x,y-largeur_skybox,z);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void skyBoxX(float x, float y, float z, GLuint texture, float largeur_skybox){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glScalef(1.,1.,1.);
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x,y-largeur_skybox,z);
            glTexCoord2f(1.,0.);
            glVertex3f(x,y,z);
            glTexCoord2f(1.,1.);
            glVertex3f(x,y,z-largeur_skybox);
            glTexCoord2f(0.,1.);
            glVertex3f(x,y-largeur_skybox,z-largeur_skybox);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void skyBoxY(float x, float y, float z, GLuint texture, float largeur_skybox){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glScalef(1.,1.,1.);
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x,y,z+largeur_skybox);
            glTexCoord2f(1.,0.);
            glVertex3f(x+largeur_skybox,y,z+largeur_skybox);
            glTexCoord2f(1.,1.);
            glVertex3f(x+largeur_skybox,y,z);
            glTexCoord2f(0.,1.);
            glVertex3f(x,y,z);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
