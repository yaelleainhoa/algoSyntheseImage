#include "valDeGris.h"
#include <iostream>
#include <fstream>


#ifdef __cplusplus

extern "C"{

void defineHeight(HeightMap * heightMap, string map) {
	ifstream lireTexte(map);
		if(lireTexte){
			lireTexte >> heightMap->w>> heightMap->h;
			for (int i = 0; i < heightMap->h; i++){
                for(int j=0; j<heightMap->w; j++){
                    lireTexte >> heightMap->valeursDeGris[i][j];
                }
			}
		}
	}
}

#endif