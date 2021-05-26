#ifndef __GL_DRAWING_H
#define __GL_DRAWING_H

#include <GL/gl.h>
#include "create_object.h"

// Fonction de dessin d'un repere. L'axe x est rouge, l'axe y vert et l'axe z bleu.
void glDrawRepere(float length);

void glDrawObject_eau(GLuint textureSol);
void glDrawObject_sable(GLuint textureSol);
void glDrawObject_transition(GLuint textureSol);
void glDrawObject_roche(GLuint textureSol);

#endif
