//LENNY MORICONI

//BUT : Programme qui fait jouer l'ordinateur contre un joueur au jeu des allumettes. A chaque tour, le joueur actif choisit de retirer de 1 à 3 allumettes du tas. Le premier à retirer la dernière des 21 allumettes a perdu. Le joueur qui laisse un nombre d'allumettes égal à un multiple de 4 +1 gagne.
//ENTREE : Un entier compris entre 1 et 3 est saisi par le joueur actif.
//SORTIE : Le nombre d'allumettes restantes, si un joueur retire la dernière allumette, un message "Victoire !" s'affiche, sinon "Vous avez perdu...".

#include <stdio.h>
#include <stdlib.h>

//CONSTANTES
#define TAILLE 30	//taille maximale d'un nom de joueur
#define TAS 21		//nombre total d'allumettes
#define MIN 1		//nombre minimum d'allumettes qu'un joueur peut retirer
#define MAX 3		//nombre maximum d'allumettes qu'un joueur peut retirer
#define MENU 5		//nombre d'options dans le menu principal

//PROTOTYPES
void tourJoueurActif(char username[TAILLE], int reste, int *pSaisie);
void tourOrdiEasy(int reste, int *pSaisie);
void tourOrdiHard(int reste, int *pSaisie);
void jeu(char username[TAILLE], int choix);
void reglesDuJeu();
void saisieNom(char username[TAILLE], int choix);

//PROGRAMME PRINCIPAL
int main()
{
	//initialisation des variables

	int choix = 100;
	char username[TAILLE] = "";

	//initialisation des nombres aléatoires

	srand(time(NULL));	//modification de la graine de "srand" pour avoir une valeur différente entre chaque appel

	//saisie du nom du joueur 1

	saisieNom(username,choix);

	do{
		do{
			system("cls");
			printf("**** JEU DES ALLUMETTES - MENU PRINCIPAL ****\n\n");
			printf("%s, que voulez-vous faire ?\n\n",username);
			printf("1 = Mode facile (1 joueur)\n");	//ordi joue au hasard
			printf("2 = Mode difficile (1 joueur)\n");	//ordi connait la stratégie gagnante
			printf("3 = Mode versus (2 joueurs)\n");	//fait s'affronter 2 joueurs
			printf("4 = Regles du jeu\n");	//affiche à l'écran les règles du jeu
			printf("5 = Modifier nom\n");	//relance la procedure saisieNom afin de changer le nom du joueur 1
			printf("0 = Quitter\n\n");
			printf("Votre choix : ");
			scanf("%d",&choix);
			fflush(stdin);
			switch(choix){
				case 1 :	//même instruction pour choix 1, 2 et 3
				case 2 :
				case 3 :
					jeu(username,choix);
					break;
				case 4 :
					reglesDuJeu();
					break;
				case 5 :
					saisieNom(username,choix);
					break;
				case 0 :
					break;
	            default :   //si choix n'est pas compris entre 0 et 5
	                system("cls");
					printf("Vous devez choisir un nombre compris entre 0 et %d. Veuillez recommencer.",MENU);
			        getc(stdin);
			        fflush(stdin);
			        break;
			}

		} while(choix<0 && choix>MENU);
	} while(choix!=0);

	system("cls");
	printf("Au revoir !");
    getc(stdin);

    return 0;
}

//DEFINITIONS PROCEDURES

void tourJoueurActif(char username[TAILLE], int reste, int *pSaisie){
//BUT : Procédure qui affiche le reste d'allumettes du tas et propose au joueur actif de retirer de 1 à 3 allumettes
//ENTREE : Un entier compris entre 1 et 3 saisi par le joueur actif
//SORTIE : Message d'erreur si le nombre n'est pas compris entre 1 et 3, sinon reste - nombre saisi par le joueur
	int saisieJoueur = 0;
	while(saisieJoueur<MIN || saisieJoueur>MAX){
		system("cls");
		printf("%s, c'est a vous !\n",username);
		printf("Il vous reste %d allumette(s).\n",reste);
		printf("Voulez-vous retirer 1, 2, 3 allumette(s) ?\n");
		scanf("%d",&saisieJoueur);
		fflush(stdin);
		if(saisieJoueur<MIN || saisieJoueur>MAX){
			system("cls");
			printf("Le nombre saisi doit etre compris entre %d et %d. Veuillez recommencer.",MIN,MAX);
		    getc(stdin);
		    fflush(stdin);
		}
	}
	*pSaisie = saisieJoueur;	//on modifie la valeur de saisie en mémoire
}

void tourOrdiEasy(int reste, int *pSaisie){
//BUT : Procédure qui fait jouer l'ordi de façon aléatoire
//ENTREE : NEANT
//SORTIE : Le nombre d'allumettes retirées par l'ordi
	system("cls");
	printf("C'est au tour de CPU !\n");

	if(reste<3){
		*pSaisie = rand() % reste +1;	//l'ordinateur retire un nombre aléatoire compris entre 1 et le nombre d'allumettes restant
	}
	else{
		*pSaisie = rand() % 3 +1;	//l'ordinateur retire un nombre aléatoire d'allumettes compris entre 1 et 3 (nombre aléatoire compris entre 0 et n-1, donc on ajoute 1 au nombre généré)
	}

	printf("CPU retire %d allumette(s).",*pSaisie);
    getc(stdin);
    fflush(stdin);
}

void tourOrdiHard(int reste, int *pSaisie){
//BUT : Procédure qui fait jouer l'ordi selon la stratégie gagnante
//ENTREE : Le nombre d'allumettes restantes, l'ordi va jouer selon ce nombre
//SORTIE : Le nombre d'allumettes retirées par l'ordi
	system("cls");
	printf("C'est au tour de CPU !\n");

	//l'ordinateur retire un nombre d'allumettes, de sorte que le reste soit un multiple de 4 +1

	switch(reste%4){
		//cas où reste est un multiple de 4
		case 0 :
			*pSaisie=3;	//pour avoir un reste égal à un multiple de 4 +1
			break;
		//cas où le reste est déjà un multiple de 4 +1
		case 1 :
			*pSaisie=1;	//si joueur est en train de gagner car il joue au hasard, alors gagner du temps en retirant une allumette en espérant qu'il commette une erreur
			break;
		//autres cas
		default :
			*pSaisie=(reste % 4)-1;	//pour avoir un reste égal à 1, et donc avoir un multiple de 4 +1
			break;
	}
	printf("CPU retire %d allumette(s).",*pSaisie);
    getc(stdin);
    fflush(stdin);
}

void jeu(char username[TAILLE], int choix){
//BUT : Procédure qui annonce le tour du joueur actif et appelle les procédures qui permettent au joueur actif (qu'il soit l'ordi ou humain) de jouer
//ENTREE : Le nom du joueur ainsi que le choix du mode de jeu saisis dans le programme principal
//SORTIE : Message de victoire si l'ordi a retiré la dernière allumettes, sinon message de défaite

	//initialisation des variables

	int saisie = 0;
	int reste = TAS;
	int joueurActif = 0;	//booleen, sert à vérifier qui est le joueur actif (joueur 1 = 1, joueur 2 ou ordi = 0) lorsque la dernière allumette est retirée
	char username2[TAILLE] = "";

	//si jeu en mode versus, alors saisie du nom du joueur 2

	if(choix==3){
		saisieNom(username2,choix);
	}

	while(reste>0){
		joueurActif=1;	//c'est au tour de joueur 1
		tourJoueurActif(username,reste,&saisie);
		reste = reste-saisie;

		//dans le cas où le joueur 1 retire la dernière allumette, on vérifie qu'il reste encore des allumettes en jeu avant de faire jouer l'ordinateur ou le joueur 2

		if(reste>0){
			joueurActif=0;	//c'est au tour de l'ordinateur ou du joueur 2

		//selon le choix de l'utilisateur dans le programme principal, c'est au tour du joueur 2 (choix 3), ou de l'ordinateur qui jouera selon la stratégie gagnante (choix 2), ou non (choix 1)

			switch(choix){
				case 1 :
					tourOrdiEasy(reste,&saisie);
					break;
				case 2 :
					tourOrdiHard(reste,&saisie);
					break;
				case 3 :
					tourJoueurActif(username2,reste,&saisie);
			}
			reste = reste-saisie;
		}
	}
	system("cls");

	//on vérifie le mode de jeu et qui est le joueur actif pour afficher le message de victoire ou de défaite
	switch(choix){
		case 1 :
		case 2 :
			if(joueurActif==1){
				printf("Vous avez perdu...");
			}
			else{
				printf("Victoire !");
			}
			break;
		case 3 :
			if(joueurActif==1){
				printf("%s remporte la victoire !",username2);	//victoire de joueur 2
			}
			else{
				printf("%s remporte la victoire !",username);		//victoire de joueur 1
			}

	}

	getc(stdin);
    fflush(stdin);
}

void reglesDuJeu(){
//BUT : Procédure qui affiche les règles du jeu des allumettes ainsi que de sa variante
	system("cls");
	printf("**** JEU DES ALLUMETTES - REGLES DU JEU ****\n\n");
	printf("Mode classique (facile, difficile, versus) :\n\n");
	printf("Le jeu des allumettes se joue a deux.\n");
	printf("Les deux joueurs se partagent un tas de 21 allumettes.\n");
	printf("A tour de role, ils peuvent retirer 1, 2 ou 3 allumettes du tas.\n");
	printf("Le joueur qui retire la derniere allumette a perdu.\n\n");
    printf("Entree = Menu principal");
    getc(stdin);
    fflush(stdin);
}

void saisieNom(char username[TAILLE],int choix){
//BUT : Procédure qui permet à un joueur d'entrer son nom
//ENTREE : L'utilisateur saisit son nom
//SORTIE : Le nom saisi est affiché sur les différentes interfaces
	system("cls");
	//si jeu en mode versus, saisie du nom du joueur 2
	if(choix==3){
		printf("**** JEU DES ALLUMETTES - MODE VERSUS ****\n\n");
		printf("Joueur 2, veuillez saisir votre nom : ");
	}
	//affichage par défaut
	else{
		printf("**** JEU DES ALLUMETTES - CHOIX DU NOM ****\n\n");
		printf("Joueur 1, veuillez saisir votre nom : ");
	}
	scanf("%s",username);
    fflush(stdin);
}
