#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

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
#include "skybox.h"
#include "objet.h"



using namespace std;

/* variables globales pour la gestion de la caméra */
float profondeur = 3;
float latitude = M_PI/2.0;
float longitude = -M_PI;
float xLight1=1.;
float yLight1=0.;
int i=0;
float largeur_plan=1.;
int const NOMBRE_TEXTURE =9;
int const NOMBRE_OBJET=500;
//int const NOMBRE_PALMIERS= 100;
//int const NOMBRE_PARASOLS =50;

float obj_rot = 0.0;
GLuint texture[NOMBRE_TEXTURE];
float largeur_skybox=10.;

const float hauteur_regard=0.5;
float xCam=0;
float yCam=0;
float zCam=0.;
HeightMap heightMap;
float zfar=15;
const int fov=95;
float xRegard2D=sin(-180/M_PI*(-M_PI/2.));
float yRegard2D=cos(-180/M_PI*(-M_PI/2.));

Node ptsVisibles[3000];
int ptCount=0;
Quadtree *quadtree= new Quadtree;

float teta = 0;


Point3D soleilpos = createPoint(0.,0.,5.,0.);
Color3f soleilcolor = createColor(100,100,100);
Light soleil=createLight(soleilpos, soleilcolor);


/*********************************************************/
/* fonction de dessin de la scène à l'écran              */
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

	//tracerTriangles(&coordonnees_quadtree, 12);


	glColor3f(1.0,1.0,1.0);
	glDisable(GL_DEPTH_TEST); 
	glDepthMask(GL_FALSE);
	skyBoxZ(-largeur_skybox/2.+xCam, largeur_skybox/2.+yCam, largeur_skybox/2.+zCam,texture[1], largeur_skybox);
	skyBoxZ(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[1], largeur_skybox);
	skyBoxX(largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[0], largeur_skybox);
	skyBoxX(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[0], largeur_skybox);
	skyBoxY(-largeur_skybox/2.+xCam,-largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[0], largeur_skybox);
	skyBoxY(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[0], largeur_skybox);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glColor3f(1.0,0.0,0.0);
	glDrawRepere(2.0);

	//glScalef(0.05,0.05,0.05);


	glPushMatrix();
	//glRotatef(obj_rot,0.0,1.0,0.0);
	glColor3f(1.0,1.,1.);

	glDrawObject_eau(texture[2]);
	glDrawObject_roche(texture[4]);
	glDrawObject_sable(texture[3]);
	glDrawObject_transition(texture[5]);

	glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);

	glPopMatrix();
	glPushMatrix();
	//place aléatoirement des objets sur la map
		float limiteEau = zmin+210/(255.)*abs(zmax-zmin);
		float limiteSable= zmin+220/(255.)*abs(zmax-zmin);
		float limiteRoche= zmin+240/(255.)*abs(zmax-zmin);

		for(int i =0; i<NOMBRE_OBJET; i++)
	{
		srand(i);
		int coord= rand()%(heightMap.h*heightMap.w);
		if((vertex_coord[3*coord+2]+vertex_coord[3*(coord+1)+2]+vertex_coord[3*(coord+heightMap.w)+2]+vertex_coord[3*(coord+heightMap.w+1)+2])/4.0<=limiteEau){
			coord= rand()%(heightMap.h*heightMap.w);
			arbre(vertex_coord[3*coord],vertex_coord[3*coord+1],vertex_coord[3*coord+2], texture[8]);//bouee
		}
		else{if((vertex_coord[3*coord+2]+vertex_coord[3*(coord+1)+2]+vertex_coord[3*(coord+heightMap.w)+2]+vertex_coord[3*(coord+heightMap.w+1)+2])/4.0>limiteEau
				&& (vertex_coord[3*coord+2]+vertex_coord[3*(coord+1)+2]+vertex_coord[3*(coord+heightMap.w)+2]+vertex_coord[3*(coord+heightMap.w+1)+2])/4.0<=limiteRoche)
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

/*********************************************************/
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
	gluPerspective( 60.0, h, 0.01, 10.0 );			// Angle de vue, rapport largeur/hauteur, near, far

	/* Retour a la pile de matrice Modelview
			et effacement de celle-ci */
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*********************************************************/
/* fonction associée aux interruptions clavier           */
/* paramètres :                                          */
/* - c : caractère saisi                                 */
/* - x,y : coordonnée du curseur dans la fenêtre         */
static void kbdFunc(unsigned char c, int x, int y) {
	/* sortie du programme si utilisation des touches ESC, */
	/* 'q' ou 'Q'*/
	switch(c) {
		case 27 :
			exit(0);
			break;
		case 'F' : case 'f' : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			break;
		case 'P' : case 'p' : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			break;
		case 'R' : case 'r' : glutIdleFunc(idle);
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
		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

/*********************************************************/
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


/*********************************************************/
/* fonction associée au clique de la souris              */
/* paramètres :                                          */
/* - button : nom du bouton pressé GLUT_LEFT_BUTTON,     */
/*   GLUT_MIDDLE_BUTTON ou GLUT_RIGHT_BUTTON             */
/* - state : état du bouton button GLUT_DOWN ou GLUT_UP  */
/* - x,y : coordonnées du curseur dans la fenêtre        */
static void mouseFunc(int button, int state, int x, int y) { 
}

/*********************************************************/
/* fonction associée au déplacement de la souris bouton  */
/* enfoncé.                                              */
/* paramètres :                                          */
/* - x,y : coordonnées du curseur dans la fenêtre        */
static void motionFunc(int x, int y) { 
}

/*********************************************************/
/* fonction d'initialisation des paramètres de rendu et  */
/* des objets de la scènes.                              */
static void init(HeightMap heightMap) {
	//latitude = M_PI/2.;
	//longitude = -M_PI;

	obj_rot = 0.0;

	/* INITIALISATION DES PARAMETRES GL */
	/* couleur du fond (gris sombre) */
	glClearColor(0.3,0.3,0.3,0.0);
	/* activation du ZBuffer */
	glClearDepth(1.0f);
	glEnable( GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* lissage des couleurs sur les facettes */
	glShadeModel(GL_SMOOTH);

	/* INITIALISATION DE LA SCENE */
	createCoordinates(heightMap);


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

void idle(void) {
	obj_rot+=0.1;;
	glutPostRedisplay();
}

int main(int argc, char** argv) {

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


	//printf("Les segments AB et CD se croisent ? : %d\n",intersectionDeuxSegments(-4, 2,-2, -2.1, -2,-2.1, -1.6, 2.5));
	//printf("tan(45) = %f\n", tan((M_PI/180)*45));
	//printf("B(%f,%f)\n", cos(-19.4+13.3)*2.4/cos(19.4)+2.1,sin(-19.4+13.3)*2.4/cos(19.4)-3.1);
	//printf(" le point apparitent ou pas : %d \n",pointAppartientTriangle(2.93, -0.7, 2.1, -3.1, 2.84, -2.43, 13.3, 2.4, 2*19.4));
	//int pointAppartientTriangle(float x, float y, float xCam, float yCam, float xRegard, float yRegard, float teta, float zFar, float fov);
	init(heightMap);
	//test 

	// Point3D NO=createPointFromCoord(0);
	// Point3D NE=createPointFromCoord(1000);
	// Point3D SO=createPointFromCoord(1000*heightMap.w);
	// Point3D SE=createPointFromCoord(1000*heightMap.w+1000);
	Point3D NO=createPointFromCoord(0);
	Point3D NE=createPointFromCoord(heightMap.w-1);
	Point3D SO=createPointFromCoord((heightMap.h-1)*heightMap.w);
	Point3D SE=createPointFromCoord((heightMap.h-1)*heightMap.w+heightMap.w-1);
	Node node=createNode(NO,NE,SO,SE);
	// Quadtree *quadtree= new Quadtree;
	*quadtree=createQuadtree(&node);
	buildQuadtree(quadtree, vertex_coord,heightMap.w,heightMap.w-1);

// 	int t=camIntersectQuad(&SEq);
// 	cout << "quadAppartientTriangle(quadtree->enfantSE) : \n"<<t<<endl;
// 	t=camIntersectQuad(&NOq);
// 	cout << "quadAppartientTriangle(quadtree->enfantNO) : \n"<<t<<endl;
// 	t=camIntersectQuad(&NEq);
// 	cout << "quadAppartientTriangle(quadtree->enfantNE) : \n"<<t<<endl;
// 	t=camIntersectQuad(&SOq);
// 	cout << "quadAppartientTriangle(quadtree->enfantSO) : \n"<<t<<endl;

// 	t=quadAppartientTriangle(SEq.ptsExt);
//     cout << "quadAppartientTriangle(quadtree->enfantSE) : \n"<<t<<endl;
// 	t=quadAppartientTriangle(NOq.ptsExt);
//     cout << "quadAppartientTriangle(quadtree->enfantNO) : \n"<<t<<endl;
// 	t=quadAppartientTriangle(NEq.ptsExt);
//     cout << "quadAppartientTriangle(quadtree->enfantNE) : \n"<<t<<endl;
// 	t=quadAppartientTriangle(SOq.ptsExt);
//     cout << "quadAppartientTriangle(quadtree->enfantSO) : \n"<<t<<endl;

// t=triangleAppartientQuadtree(SEq.ptsExt);
// cout << "quadAppartientTriangle(quadtree->enfantSE) : \n"<<t<<endl;
// t=triangleAppartientQuadtree(NOq.ptsExt);
// cout << "quadAppartientTriangle(quadtree->enfantNO) : \n"<<t<<endl;
// t=triangleAppartientQuadtree(NEq.ptsExt);
// cout << "quadAppartientTriangle(quadtree->enfantNE) : \n"<<t<<endl;
// t=triangleAppartientQuadtree(SOq.ptsExt);
// cout << "quadAppartientTriangle(quadtree->enfantSO) : \n"<<t<<endl;
	travelQuadtree(ptsVisibles, *quadtree, &ptCount);
	tracerTriangles(ptsVisibles, ptCount, heightMap, &soleil);

	//Node tab_node[50];
	//inorderTravel(&quadtree, tab_node,&count);
	// for(int i=0; i<10 ; i++)
	// {
	// 	printf("NO: %d ,NE:%d, SO:%d,SE:%d, \n" ,
	// 	tab_node[i]->pointNO,
	// 	tab_node[i]->pointNE,
	// 	tab_node[i]->pointSO,
	// 	tab_node[i]->pointSE);
	// }


	/* association de la fonction callback de redimensionnement */
	glutReshapeFunc(reshapeFunc);
	/* association de la fonction callback d'affichage */
	glutDisplayFunc(drawFunc);
	/* association de la fonction callback d'événement du clavier */
	glutKeyboardFunc(kbdFunc);
	/* association de la fonction callback d'événement du clavier (touches spéciales) */
	glutSpecialFunc(kbdSpFunc);
	/* association de la fonction callback d'événement souris */
	glutMouseFunc(mouseFunc);
	/* association de la fonction callback de DRAG de la souris */
	glutMotionFunc(motionFunc);

	glutIdleFunc(idle);

	/* boucle principale de gestion des événements */
	glutMainLoop();
	/* Cette partie du code n'est jamais atteinte */
	return 0;
}
