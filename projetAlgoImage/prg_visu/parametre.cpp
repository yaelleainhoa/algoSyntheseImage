#include "parametre.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void defineParam(float* xsize, float* zmin, float* zmax, float* zfar, int* fov, int* nb_obj) {
	ifstream lireTexte("../prg_visu/parametre.timac");
    string inutile;
		if(lireTexte){
			lireTexte >> inutile;
			lireTexte >> *xsize;
            lireTexte >> inutile;
			lireTexte >> *zmin;
            lireTexte >> inutile;
			lireTexte >> *zmax;
            lireTexte >> inutile;
			lireTexte >> *zfar;
            lireTexte >> inutile;
			lireTexte >> *fov;
            lireTexte >> inutile;
			lireTexte >> *nb_obj;
			}
		}
//dans la string "inutile" comporte les noms des différents paramètre
//elle ne servira pas mais rend le remplissage des parametres plus facile pour l'utilisateur