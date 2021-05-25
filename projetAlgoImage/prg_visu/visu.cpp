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

using namespace std;

/* variables globales pour la gestion de la caméra */
float profondeur = 3;
float latitude = M_PI/2.0;
float longitude = -M_PI;
float xLight1=1.;
float yLight1=0.;
int i=0;
float largeur_plan=1.;

float obj_rot = 0.0;
GLuint texture[3];
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

//pour tester la fonction tracerTriangles
//int coordonnees_quadtree[]={0,1,7,8,1,2,8,9,4,5,11,12};


void moveLight(void){
	i++;
    xLight1=largeur_plan*cos(3.14/180*i);
	yLight1=largeur_plan*sin(3.14/180*i);
    GLfloat light0Position[] = {xLight1, yLight1, 0.0, 1.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light0Position);
}

void skyBoxZ(float x, float y, float z, GLuint texture){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        //glScalef(largeur_skybox,largeur_skybox,1.);
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

void skyBoxX(float x, float y, float z, GLuint texture){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glScalef(1.,1.,1.);
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x,y,z);
            glTexCoord2f(1.,0.);
            glVertex3f(x,y,z-largeur_skybox);
            glTexCoord2f(1.,1.);
            glVertex3f(x,y-largeur_skybox,z-largeur_skybox);
            glTexCoord2f(0.,1.);
            glVertex3f(x,y-largeur_skybox,z);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void skyBoxY(float x, float y, float z, GLuint texture){
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glScalef(1.,1.,1.);
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x,y,z);
            glTexCoord2f(1.,0.);
            glVertex3f(x+largeur_skybox,y,z);
            glTexCoord2f(1.,1.);
            glVertex3f(x+largeur_skybox,y,z+largeur_skybox);
            glTexCoord2f(0.,1.);
            glVertex3f(x,y,z+largeur_skybox);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


void arbre(float x, float y, float z, GLuint texture){
	//cout << "longitude "<< longitude <<endl; 
	//cout << "latitude "<< latitude <<endl; 
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
		glTranslatef(x/2,0,-z/2);
        //glScalef(1.,1.,1.);
		glRotatef(-obj_rot*180/M_PI, 0. ,0. ,1. );
        glBegin(GL_QUADS);
            glTexCoord2f(0.,0.);
            glVertex3f(x-1.0/2,y,z);
            glTexCoord2f(1.,0.);
            glVertex3f(x+1.0/2/2,y,z);
            glTexCoord2f(1.,1.);
            glVertex3f(x+1.0/2/2,y,0);
            glTexCoord2f(0.,1.);
            glVertex3f(x-1.0/2,y,0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

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


	//tracerTriangles(&coordonnees_quadtree, 12);


	glColor3f(1.0,1.0,1.0);
	glDisable(GL_DEPTH_TEST); 
	glDepthMask(GL_FALSE);
	skyBoxZ(-largeur_skybox/2.+xCam, largeur_skybox/2.+yCam, largeur_skybox/2.+zCam,texture[1]);
	skyBoxZ(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[1]);
	skyBoxX(largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[1]);
	skyBoxX(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,largeur_skybox/2.+zCam,texture[1]);
	skyBoxY(-largeur_skybox/2.+xCam,-largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[1]);
	skyBoxY(-largeur_skybox/2.+xCam,largeur_skybox/2.+yCam,-largeur_skybox/2.+zCam,texture[1]);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glColor3f(1.0,0.0,0.0);
	glDrawRepere(2.0);

	//glScalef(0.1,0.1,0.1);

	//tracerTriangles(ptsVisibles, ptCount);
// 	int h = heightMap.h;
// 	int w=heightMap.w;
// 	for (int i=0;i<h-1;i++){
// 	for(int j=0;j<w-1;j++){
// 		glEnable(GL_TEXTURE_2D);
//         glBindTexture(GL_TEXTURE_2D, texture[0]);
// 		glScalef(1.,1.,1.);
//         glBegin(GL_QUADS);
//             glTexCoord2f(0.,0.);
//             glVertex3f(vertex_coord[3*(h*i+j)],vertex_coord[3*(h*i+j)+1],vertex_coord[3*(h*i+j)+2]);
//             glTexCoord2f(1.,0.);
//             glVertex3f(vertex_coord[3*(h*i+j+1)],vertex_coord[3*(h*i+j+1)+1],vertex_coord[3*(h*i+j+1)+2]);
//             glTexCoord2f(1.,1.);
//             glVertex3f(vertex_coord[3*(h*(i+1)+j)],vertex_coord[3*(h*(i+1)+j)+1],vertex_coord[3*(h*(i+1)+j)+2]);
//             glTexCoord2f(0.,1.);
//             glVertex3f(vertex_coord[3*(h*(i+1)+j)],vertex_coord[3*(h*(i+1)+j)+1],vertex_coord[3*(h*(i+1)+j)+2]);
//         glEnd();
//         glBindTexture(GL_TEXTURE_2D, 0);
//     glDisable(GL_TEXTURE_2D);

// 		glEnable(GL_TEXTURE_2D);
//         glBindTexture(GL_TEXTURE_2D, texture[0]);
// 		glScalef(1.,1.,1.);
//         glBegin(GL_QUADS);
//             glTexCoord2f(0.,0.);
//             glVertex3f(vertex_coord[3*(h*i+j+1)],vertex_coord[3*(h*i+j+1)+1],vertex_coord[3*(h*i+j+1)+2]);
//             glTexCoord2f(1.,0.);
//             glVertex3f(vertex_coord[3*(h*(i+1)+j)],vertex_coord[3*(h*(i+1)+j)+1],vertex_coord[3*(h*(i+1)+j)+2]);
//             glTexCoord2f(1.,1.);
//             glVertex3f(vertex_coord[3*(h*(i+1)+j+1)],vertex_coord[3*(h*(i+1)+j+1)+1],vertex_coord[3*(h*(i+1)+j+1)+2]);
//             glTexCoord2f(0.,1.);
//             glVertex3f(vertex_coord[3*(h*(i+1)+j+1)],vertex_coord[3*(h*(i+1)+j+1)+1],vertex_coord[3*(h*(i+1)+j+1)+2]);
//         glEnd();
//         glBindTexture(GL_TEXTURE_2D, 0);
//     glDisable(GL_TEXTURE_2D);

// 	}
// }

	//trucs du prof/2.
	// float position[4] = {5.,5.,5.,0.};
	// float black[3] = {0.0,0.0,0.0};
	// float intensite[3] = {1000.0,1000.0,1000.0};
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);
	// glLightfv(GL_LIGHT0,GL_POSITION,position);
	// glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
	// glLightfv(GL_LIGHT0,GL_SPECULAR,black);

	float position[4] = {0.,5.,0.,1.};
	float black[4] = {0.9,0.9, 0.9, 1.0};
	float intensite[4] = {0.9, 0.9, 0.9, 1.0};
	GLfloat ambient[]={0.2, 0.2, 0.2, 1.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
	glLightfv(GL_LIGHT0,GL_SPECULAR,black);

		//GL_LIGHT1 sera la lumière qui bouge, avec la fonction moveLight, là GL_LIGHT1 n'est pas initiée
		// GLfloat light0Position[] = {xLight1, yLight1, 0.0, 1.0}; // Position
		// glLightfv(GL_LIGHT1, GL_POSITION, light0Position);
		// GLfloat ambient0[]={0.2, 0.2, 0.2, 1.0}; // Farbdefinitionen
		// GLfloat diffuse0[]={0.9, 0.9, 0.9, 1.0};
		// GLfloat specular0[]={1.0,1.0, 1.0, 1.0};
		// glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
		// glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse0);
		// glLightfv(GL_LIGHT1, GL_SPECULAR, specular0);
		// glEnable(GL_LIGHTING);
		// glEnable(GL_LIGHT1);


	//glLightf(GL_LIGHT0,GL_,black);
	//glLightf(GL_LIGHT0,GL_SPECULAR,black);

	glPushMatrix();
	//glRotatef(obj_rot,0.0,1.0,0.0);
	glColor3f(1.0,1.,1.);
	glDrawObject(texture[2]);
	glDrawObject_1(texture[1]);

	glDisable(GL_LIGHTING);

	glPopMatrix();
	glPushMatrix();
	////arbre(0.5,0.5,1., texture[0]);
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
		case 'S' : case 's' : glutIdleFunc(NULL);
			break;
		case 'A' : case 'a' : printf("xpos : %f, ypos : %f \n", xCam, yCam);
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
			//if (latitude>STEP_ANGLE) 
			latitude -= STEP_ANGLE;
			break;
		case GLUT_KEY_DOWN :
			//if(latitude<M_PI-STEP_ANGLE) 
			latitude += STEP_ANGLE;
			break;
		case GLUT_KEY_LEFT :
			longitude -= STEP_ANGLE;
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap);

			break;
		case GLUT_KEY_RIGHT :
			longitude += STEP_ANGLE;
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap);

			break;
		case GLUT_KEY_F2 :
			profondeur += STEP_PROF;
			xCam+=STEP_PROF*sin(longitude);
			yCam+=STEP_PROF*cos(longitude);
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap);
			hauteur(xCam, yCam, heightMap, &zCam);
			break;
		case GLUT_KEY_F1 :
			if (profondeur>0.1+STEP_PROF) profondeur -= STEP_PROF;
			xCam-=STEP_PROF*sin(longitude);
			yCam-=STEP_PROF*cos(longitude);
			xRegard2D=sin(longitude)+xCam;
			yRegard2D=cos(longitude)+yCam;
			ptCount=0;
			travelQuadtree(ptsVisibles, *quadtree, &ptCount);
			tracerTriangles(ptsVisibles, ptCount, heightMap);
			hauteur(xCam, yCam, heightMap, &zCam);
			break;
		// case GLUT_KEY_F3 :
		// 	moveLight();
		// 	break;
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


	char const * sources[3]={"images/doggy.jpg","images/sky.jpg","images/sol.jpg"};
    for(int i=0; i<3; i++){
		glEnable(GL_TEXTURE_2D);
        SDL_Surface* image=IMG_Load(sources[i]);
        glGenTextures(1, &texture[i]);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
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
	cout << vertex_coord[150498]<<endl<<endl;
	cout << "ptCount : "<<ptCount<<endl<<endl<<endl;
	printf("rempli ou pas ??? %d",ptsVisibles[0].pointNO.coord);
	cout << "test division float 180/M_PI = "<<180/M_PI<<endl;

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
