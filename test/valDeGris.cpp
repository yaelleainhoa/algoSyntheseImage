#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int const MAX_PIXELS=1000;

int main() {
string texteChoix;
string valeur1, valeur2;
int w;
int h;
int valeursDeGris[MAX_PIXELS][MAX_PIXELS];
int texte;
cout << "Lire le texte ? (o / n) : ";
cin >> texteChoix;
texte=int(texteChoix[0]);

if (texte==79 or texte==111){ //Première lettre de la réponse qui vaut O ou o
	ifstream lireTexte("../test/valDeGris.txt");
	///ici on ne se contente pas de lire le document texte, on extrait les valeurs (c'est la partie intéressante pour le projet puisqu'on va récupérer ici la nuance de gris)
		if(lireTexte){
			lireTexte >> w >> h;
			for (int i = 0; i < w; i++){
                for(int j=0; j<h; j++){
                    lireTexte >> valeursDeGris[i][j];
                    }
			}
		}
	//On les affiche pour le test
	cout << "Les elements gardés dans le fichier texte sont : "<<endl;
	cout << w<< ' '<<h<<endl;
	for (int i = 0; i < w; i++){
        for(int j=0; j<h; j++){
            cout << valeursDeGris[i][j]<< ' ';
        }
        cout << '\n';
    }
}
}

//pb ptn