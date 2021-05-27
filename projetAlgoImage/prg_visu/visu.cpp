#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "visu.h"
#include "gldrawing.h"
#include "create_object.h"
#include "valDeGris.h"
#include "quadtree.h"
#include "geometry.h"
#include "light.h"
#include "skybox.h"
#include "objet.h"
#include "parametre.h"


/*-----variables globales pour la gestion de la caméra------*/

float profondeur = 3;
float latitude = M_PI/2.0;
float longitude = -M_PI;
float xLight1=1.;
float yLight1=0.;
int i=0;
const float hauteur_regard=0.5;
float xCam=0;
float yCam=0;
float zCam=0.;
HeightMap heightMap;
float xRegard2D=sin(-180/M_PI*(-M_PI/2.));
float yRegard2D=cos(-180/M_PI*(-M_PI/2.));

//-----variables textures------------------------------------

int const NOMBRE_TEXTURE =9;
GLuint texture[NOMBRE_TEXTURE];
int NOMBRE_OBJET;

float largeur_skybox=10.;

//-------variables pour l'affichage de la map---------------
//ces variables seront initiées plus tard par lecture de params.timac
int fov;
float zfar;
float xsize;
float zmin;
float zmax;

Node ptsVisibles[3000];
int ptCount=0;
Quadtree *quadtree= new Quadtree;

//-----------Variables soleil-----------------------------
float angle1 = M_PI/2.0;
float angle2 = 0;

Point3D soleilpos = createPoint(0.,0.,100.,0.);
Color3f soleilcolor = createColor(200,200,200);
Light soleil=createLight(soleilpos, soleilcolor);

//--------------------------------------------------------

//-------fonction de dessin de la scène à l'écran---------
static void drawFunc(void) { 

	/* reinitialisation des buffers : couleur et ZBuffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* modification de la matrice de la scène */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Debut du dessin de la scène */
	glPushMatrix();
		/* placement de la caméra */
		gluLookAt(xCam, yCam, zCam+hauteur_regard,
				sin(longitude)*sin(latitude)+xCam,cos(longitude)*sin(latitude)+yCam,cos(latitude)+zCam+hauteur_regard,
				0.0,0.0,1.0);	
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor3f(1.0,1.0,1.0);
		glDisable(GL_DEPTH_TEST); 
		glDepthMask(GL_FALSE);

		//------------dessin de la skybox--------------------
		skyBoxZ(-largeur_skybox/2.+xCam, largeur_skybox/2.+yCam, largeur_skybox/2.+zCam,texture[1], largeur_skybox);
		skyBoxZ(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[4], largeur_skybox);
		skyBoxX(largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[0], largeur_skybox);
		skyBoxX(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[0], largeur_skybox);
		skyBoxY(-largeur_skybox/2.+xCam,-largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[0], largeur_skybox);
		skyBoxY(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[0], largeur_skybox);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		glColor3f(1.0,0.0,0.0);
		glDrawRepere(2.0);

		glPushMatrix();
			glColor3f(1.0,1.,1.);

			//dessin des différentes textures
			glDrawObject_eau(texture[2]);
			glDrawObject_roche(texture[4]);
			glDrawObject_sable(texture[3]);
			glDrawObject_transition(texture[5]);

	glScalef(0.05,0.05,0.05);
			glDisable(GL_LIGHTING);
		glPopMatrix();
		glPushMatrix();
			//place aléatoirement des objets sur la map
			float limiteEau = zmin+220/(255.)*abs(zmax-zmin);
			float limiteSable= zmin+230/(255.)*abs(zmax-zmin);
			float limiteRoche= zmin+240/(255.)*abs(zmax-zmin);

			for(int i =0; i<NOMBRE_OBJET; i++)
			{
				srand(i);
				int coord= rand()%(heightMap.h*heightMap.w);
				if(max(max(vertex_coord[3*coord+2],vertex_coord[3*(coord+1)+2]),max(vertex_coord[3*(coord+heightMap.w)+2],vertex_coord[3*(coord+heightMap.w+1)+2])) <= limiteEau)
				{
					arbre(vertex_coord[3*coord],vertex_coord[3*coord+1],vertex_coord[3*coord+2], texture[8]);//bouee
				}
				else{
					if((max(max(vertex_coord[3*coord+2],vertex_coord[3*(coord+1)+2]),max(vertex_coord[3*(coord+heightMap.w)+2],vertex_coord[3*(coord+heightMap.w+1)+2]))>limiteEau)
						&&(max(max(vertex_coord[3*coord+2],vertex_coord[3*(coord+1)+2]),max(vertex_coord[3*(coord+heightMap.w)+2],vertex_coord[3*(coord+heightMap.w+1)+2]))<=limiteRoche))
					{
						int random=rand()%1;
						if(random==0){
							arbre(vertex_coord[3*coord],vertex_coord[3*coord+1],vertex_coord[3*coord+2], texture[6]);//palmier
						}
						else{
							arbre(vertex_coord[3*coord],vertex_coord[3*coord+1],vertex_coord[3*coord+2], texture[7]);//parasol
						}
					}
				}
			}	
		glPopMatrix();
	/* Fin du dessin */
	glPopMatrix();
	/* fin de la définition de la scène */
	glFinish();

	/* changement de buffer d'affichage */
	glutSwapBuffers();

}

//--------------------------------------------------------
/* fonction de changement de dimension de la fenetre     */
/* paramètres :                                          */
/* - width : largeur (x) de la zone de visualisation     */
/* - height : hauteur (y) de la zone de visualisation    */
static void reshapeFunc(int width,int height) {
	GLfloat  h = (GLfloat) width / (GLfloat) height ;
	
	/* dimension de l'écran GL */
	glViewport(0, 0, (GLint)width, (GLint)height);
	/* construction de la matrice de projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* définition de la camera */
	gluPerspective( 60.0, h, 0.01, 10.0 );// Angle de vue, rapport largeur/hauteur, near, far

	/* Retour a la pile de matrice Modelview et effacement de celle-ci */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//--------------------------------------------------------
/* fonction associée aux interruptions clavier           */
/* paramètres :                                          */
/* - c : caractère saisi                                 */
/* - x,y : coordonnée du curseur dans la fenêtre         */
static void kbdFunc(unsigned char c, int x, int y) {
	switch(c) {
		case 'Q' :case 'q':
			exit(0);
			break;
		case 'F' : case 'f' : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//passe en mode filaire
			break;
		case 'P' : case 'p' : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);//passe en mode plan
			break;
		//case 'R' : case 'r' : glutIdleFunc(idle);
			break;
		case 'M' : case 'm' : glutIdleFunc(NULL);
			break;
		case 'A' : case 'a' : printf("xpos : %f, ypos : %f \n", xCam, yCam);
			break;
		case 'Z' : case 'z': //avance
			profondeur += STEP_PROF;
			xCam+=STEP_PROF*sin(longitude);
			yCam+=STEP_PROF*cos(longitude);
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);
			hauteurCam(xCam, yCam, heightMap, &zCam);
			break;
		case 'S':case 's': //recule
			if (profondeur>0.1+STEP_PROF) profondeur -= STEP_PROF;
			xCam-=STEP_PROF*sin(longitude);
			yCam-=STEP_PROF*cos(longitude);
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);
			hauteurCam(xCam, yCam, heightMap, &zCam);
			break;	
		// case 'K' : case 'k' : glutIdleFunc(idle);
		// 	break;
		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

//--------------------------------------------------------
/* fonction associée aux interruptions clavier pour les  */
/*          touches spéciales                            */
/* paramètres :                                          */
/* - c : code de la touche saisie                        */
/* - x,y : coordonnée du curseur dans la fenêtre         */
static void kbdSpFunc(int c, int x, int y) {
	/* sortie du programme si utilisation des touches ESC, */
	switch(c) {
		case GLUT_KEY_UP :
			if (latitude>STEP_ANGLE) 
			latitude -= STEP_ANGLE;
			break;
		case GLUT_KEY_DOWN :
			if(latitude<2.6) {
			latitude += STEP_ANGLE;}
			break;
		case GLUT_KEY_LEFT :
			longitude -= STEP_ANGLE;
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);

			break;
		case GLUT_KEY_RIGHT :
			longitude += STEP_ANGLE;
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);

			break;
		default:
			printf("Appui sur une touche spéciale\n");
	}
	glutPostRedisplay();
}

/*-------------------------------------------------------*/
/* fonction d'initialisation des paramètres de rendu et  */
/* des objets de la scènes.                              */
static void init(HeightMap heightMap) {
	angle2 = 0.0;
	angle1 = M_PI/2.;

	/* INITIALISATION DES PARAMETRES GL */
	/* couleur du fond (gris sombre) */
	glClearColor(0.3,0.3,0.3,0.0);
	/* activation du ZBuffer */
	glClearDepth(1.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* lissage des couleurs sur les facettes */
	glShadeModel(GL_SMOOTH);

	/*initialisation de  */
	createCoordinates(heightMap);

	/*chargement des textures*/
	char const * sources[NOMBRE_TEXTURE]={"images/sky.jpg","images/sky_top.png","images/sol_eau.png","images/sol_sable.png","images/sol_roche.png","images/sol_transition.png","images/palmier.png","images/parasol.png","images/bouee.png"};
    for(int i=0; i<NOMBRE_TEXTURE; i++){
		glEnable(GL_TEXTURE_2D);
        SDL_Surface* image=IMG_Load(sources[i]);
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		GLenum format;
		switch(image->format->BytesPerPixel) {
			case 1:
				format = GL_RED;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			default:
				fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", sources[i]);
				return;
    	}

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0,format, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
		SDL_FreeSurface(image);
    }
}

// void idle(void) {
// 	obj_rot+=0.1;
// 	glutPostRedisplay();
// }

// Loop rotation du soleil
void idle(void) {
	cout << "k" << endl;
	//obj_rot+=0.1;

    
	if(soleil.position.z < 0){
		angle2 += STEP_ANGLE*2;
	}else{
		angle2+=STEP_ANGLE*0.1;
	}
	//cout << "angle : " << angle2 << endl;
	//rotateSun(&soleil, heightMap.w, angle2);
	//soleil.position.z = sin(angle2)*(heightMap.h);
	soleil.position.z = sin(angle2)*(heightMap.w/2);
    //soleil.position.x = sin(angle2)*(heightMap.h);
    //soleil.position.y = soleilpos.y + cos(angle2)*(heightMap.h/2);
	soleil.position.x = cos(angle2)*(heightMap.w/2);
	cout << " soleil.position.z : " <<  soleil.position.z << endl;
	if(soleil.position.z < 1 && soleil.position.z > -2 ){
		cout << " soleil.position.x : " <<  soleil.position.x << endl;
		cout << "heightMap.w : " << heightMap.w/2 << endl;
	}
	
	tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	defineParam(&xsize, &zmin, &zmax, &zfar, &fov, &NOMBRE_OBJET);
	defineHeight(&heightMap);
	/* traitement des paramètres du programme propres à GL */
	glutInit(&argc, argv);
	/* initialisation du mode d'affichage :                */
	/* RVB + ZBuffer + Double buffer.                      */
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
	/* placement et dimentions originales de la fenêtre */
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	/* ouverture de la fenêtre */
	if (glutCreateWindow("visuTerImac") == GL_FALSE) {
		return 1;
	}

	init(heightMap);
	Point3D NO=createPointFromCoord(0);
	Point3D NE=createPointFromCoord(heightMap.w-1);
	Point3D SO=createPointFromCoord((heightMap.h-1)*heightMap.w);
	Point3D SE=createPointFromCoord((heightMap.h-1)*heightMap.w+heightMap.w-1);
	Node node=createNode(NO,NE,SO,SE);
	*quadtree=createQuadtree(&node);
	buildQuadtree(quadtree, vertex_coord,heightMap.w,heightMap.w-1);
	travelQuadtree(ptsVisibles, *quadtree, &ptCount);
	tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);

	/* association de la fonction callback de redimensionnement */
	glutReshapeFunc(reshapeFunc);
	/* association de la fonction callback d'affichage */
	glutDisplayFunc(drawFunc);
	/* association de la fonction callback d'événement du clavier */
	glutKeyboardFunc(kbdFunc);
	/* association de la fonction callback d'événement du clavier (touches spéciales) */
	glutSpecialFunc(kbdSpFunc);
	/* association de la fonction callback d'événement souris */

	//glutIdleFunc(idle);
	glutIdleFunc(NULL);
	/* boucle principale de gestion des événements */
	glutMainLoop();
	/* Cette partie du code n'est jamais atteinte */
	return 0;
}
