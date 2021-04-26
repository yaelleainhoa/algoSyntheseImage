#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main() {
string texteChoix;
string valeur1, valeur2;
int v1=0;
int v2=0;
int valeursDeGris[4][2];
int texte;
cout << "Lire le texte ? (oui / non) : ";
cin >> texteChoix;
texte=int(texteChoix[0]);

if (texte==79 or texte==111){ //Première lettre de la réponse qui vaut O ou o
	ifstream lireTexte("../test/test.txt");
	///ici on ne se contente pas de lire le document texte, on extrait les valeurs (c'est la partie intéressante pour le projet puisqu'on va récupérer ici la nuance de gris)
		if(lireTexte){
			lireTexte >> valeur1 >> v1;
			lireTexte >> valeur2 >> v2;
			for (int i = 0; i < 4; i++){
				int x,y;
				lireTexte >> x >> y;
				valeursDeGris[i][0]=x;
				valeursDeGris[i][1]=y;

			}
		}

	//On les affiche pour le test
	cout << "Les elements gardés dans le fichier texte sont : "<<endl;
	cout << valeur1<<v1<<endl;
	cout << valeur2<<v2<<endl;
	for (int i = 0; i < 4; i++){
		cout << valeursDeGris[i][0]<<", "<<valeursDeGris[i][1] << endl;
	}
}

//Si on veut remplacer les valeurs du texte
int changerTexte=0;
string changerTexteChoix;
 cout << "Changer le fichier texte ? (oui / non) : " ;
	cin >> changerTexteChoix;
	changerTexte=int(changerTexteChoix[0]);

	if (changerTexte==111 or changerTexte == 79){
		std::remove("test.txt");  //d'abord on le vide
		ofstream ecrireTexte("../test/test.txt");
		if(ecrireTexte){
			cout << "Entrez le nom de la première valeur (ex : 'Valeur1:) :";
			cin >> valeur1;
			cout << "Entrez la valeur 1 : ";
			cin >> v1;
			cout << "Entrez le nom de la deuxième valeur :";
			cin >> valeur2;
			cout << "Entrez la valeur 2 : ";
			cin >> v2;
			ecrireTexte << valeur1 << " " <<v1 <<endl; //On entre les valeurs dans le texte
			ecrireTexte << valeur2 << " " << v2 <<endl;
			for (int i = 0; i < 4; i++){
				int x,y;
				cout << "(ligne "<<i+3<<") Entrez x :";
				cin >> x;
				cout << "(ligne "<<i+3<<") Entrez y :";
				cin >> y;
				ecrireTexte << x << " " << y << endl; //On entre les valeurs dans le texte
			}
	}


		

}
}