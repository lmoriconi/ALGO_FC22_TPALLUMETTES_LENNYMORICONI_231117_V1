//LENNY MORICONI

//BUT : Programme qui fait jouer l'ordinateur contre un joueur au jeu des allumettes. A chaque tour, le joueur actif choisit de retirer de 1 à 3 allumettes du tas. Le premier à retirer la dernière des 21 allumettes a perdu. Le joueur qui laisse un nombre d'allumettes égal à un multiple de 4 +1 gagne.
//ENTREE : Un entier compris entre 1 et 3 est saisi par le joueur actif.
//SORTIE : Le nombre d'allumettes restantes, si un joueur retire la dernière allumette, un message "Victoire !" s'affiche, sinon "Vous avez perdu...".

#include <stdio.h>
#include <stdlib.h>

//CONSTANTES
#define TAILLE 30	//taille maximale d'un nom de joueur
#define MAX 3		//nombre maximum d'allumettes qu'un joueur peut retirer
#define LIGNE 4     //nombre de lignes du tableau
#define COLONNE 7   //nombre de colonnes du tableau
#define MENU 3		//nombre d'options dans le menu principal

//PROTOTYPES
void verifLigne(int t[LIGNE][COLONNE], int numLigne, int *pLigneVide);
void verifCase(int t[LIGNE][COLONNE], int x, int y, int *pVide);
void affichTab(int t[LIGNE][COLONNE]);
void tourJoueurActifAlt(char username[TAILLE], int t[LIGNE][COLONNE], int premierCoup, int *pNumLigne);
void tourOrdiAlt(int t[LIGNE][COLONNE], int premierCoup, int *pLigneVide);
void verifTab(int t[LIGNE][COLONNE], int *pReste);
void initTab(int t[LIGNE][COLONNE]);
void jeuAlt(char username[TAILLE]);
void reglesDuJeu();
void saisieNom(char username[TAILLE]);

//PROGRAMME PRINCIPAL

int main()
{
	//initialisation variables

	int choix = 100;
	char username[TAILLE] = "";

	//initialisation des nombres aléatoires

	srand(time(NULL));	//modification de la graine de "srand" pour avoir une valeur différente entre chaque appel

	//saisie du nom du joueur 1

	saisieNom(username);

    do{
	    do{
	    	system("cls");
			printf("**** JEU DES ALLUMETTES - VARIANTE - MENU PRINCIPAL ****\n\n");
	    	printf("%s, que voulez-vous faire ?\n\n",username);
	    	printf("1 = Mode alternatif (1 joueur)\n");//	lancer la procédure qui permet de jouer à la version alternative du jeu de nim
	    	printf("2 = Regles du jeu\n");	//affiche à l'écran les règles du jeu
			printf("3 = Modifier nom\n");	//relance la procedure saisieNom afin de changer le nom du joueur 1
	    	printf("0 = Quitter\n");
	    	scanf("%d",&choix);
			fflush(stdin);
		    switch(choix){
				case 1 :
					jeuAlt(username);
					break;
				case 2 :
					reglesDuJeu();
					break;
				case 3 :
					saisieNom(username);
					break;
				case 0 :
					break;
	            default :   //si choix n'est pas compris entre 0 et 3
	                system("cls");
                        printf("Vous devez choisir un nombre compris entre 0 et %d. Veuillez recommencer.",MENU);
			        getc(stdin);
			        fflush(stdin);
			        break;
			}
		}while(choix<0 && choix>MENU);
	}while(choix!=0);

	system("cls");
	printf("Au revoir !");
    getc(stdin);

    return 0;
}

//DEFINITIONS PROCEDURES

void verifLigne(int t[LIGNE][COLONNE], int numLigne, int *pLigneVide){
//BUT : Procédure qui vérifie que la ligne sur laquelle un joueur retire actuellement des allumettes est vide ou non
//ENTREE : Tableau t et index de la ligne actuelle
//SORTIE : FAUX s'il reste des allumettes sur la ligne, sinon VRAI

	int j=0;
	*pLigneVide=1;		//on part du principe que la ligne est vide

	for(j=0;j<COLONNE;j++){
		if(t[numLigne][j]==1){
			*pLigneVide=0;	//si on trouve une seule allumette dans la ligne alors ligneVide = FAUX
		}
	}
}

void verifCase(int t[LIGNE][COLONNE], int x, int y, int *pVide){
//BUT : Procédure qui sert à vérifier que t[x,y] est vide ou non
//ENTREE : Tableau t et coordonnées x et y saisie par le joueur
//SORTIE : FAUX si la case contient une allumette, sinon VRAI

	if(t[x][y]==1){
		*pVide=0;
	}
	else{
		*pVide=1;
	}
}

void affichTab(int t[LIGNE][COLONNE]){
//BUT : Procédure qui affiche le tableau des allumettes restantes
//ENTREE : Tableau t
//SORTIE : Affichage du tableau

	int i=0,j=0;

	printf("  ");

	//afin que le joueur ait les coordonnées sous les yeux
	for(j=0;j<COLONNE;j++){
		printf(" %d",j);
	}
	printf("\n\n");
	for(i=0;i<LIGNE;i++){
		printf("%d  ",i);	//idem
		//on affiche le tableau
		for(j=0;j<COLONNE;j++){
			if(t[i][j]==1){
				printf("%d ",t[i][j]);
			}
			else{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void tourJoueurActifAlt(char username[TAILLE], int t[LIGNE][COLONNE], int premierCoup, int *pNumLigne){
//BUT : Procédure qui propose au joueur actif de retirer 1 allumette dans la case de son choix
//ENTREE : Les coordonnées [x,y] d'une case du tableau saisies par le joueur actif
//SORTIE : Message d'erreur si une des saisies est incorrecte ou avertissement si une case est déjà vide, sinon modifie le tableau en retirant l'allumette souhaitée

	int saisie=0,x=0,y=0;
	int vide=1;				//booléen, vérifie qu'une case est vide ou non lorsque le joueur veut retirer une allumette

	x=*pNumLigne;	//on récupère la valeur de x, qu'elle ait été déjà saisie par le joueur ou non

	//répéter tant que la case sélectionneé n'est pas vide

	do{

		//répéter jusqu'à ce que le joueur confirme son coup (saisie=1)

		do{
			system("cls");
			printf("%s, c'est a vous !\n\n",username);
			printf("Allumettes restantes :\n\n");
			affichTab(t);

			//saisie x si c'est le premier coup du joueur

			if(premierCoup==1){
				do{
					printf("\nQuelle ligne ?\n");
					scanf("%d",&x);
					fflush(stdin);
					if(x<0 || x>=LIGNE){
						system("cls");
						printf("Le nombre saisi doit etre compris entre 0 et %d. Veuillez recommencer.",LIGNE-1);
						getc(stdin);
			    		fflush(stdin);
			    		affichTab(t);
					}
				}while(x<0 || x>=LIGNE);
			}

			//on renvoie dans la procédure "jeuAlt" la valeur de la ligne sélectionnée par le joueur afin d'attribuer par après le nombre de coups maximum

			*pNumLigne=x;

			//saisie y

			do{
				printf("\nQuelle colonne ?\n");
				scanf("%d",&y);
				fflush(stdin);
				if(y<0 || y>=COLONNE){
					system("cls");
					printf("Le nombre saisi doit etre compris entre 0 et %d. Veuillez recommencer.",COLONNE-1);
					getc(stdin);
		    		fflush(stdin);
		    		affichTab(t);
				}
			}while(y<0 || y>=COLONNE);

			//confirmation

			do{
				printf("\nCase [%d,%d]... Confirmer ?\n",x,y);
				printf("1 = Oui\n");
				printf("0 = Non\n");
				scanf("%d",&saisie);
				fflush(stdin);
				if(saisie<0 || saisie>1){
					system("cls");
					printf("Le nombre saisi doit etre compris entre 0 et 1. Veuillez recommencer.");
					getc(stdin);
		    		fflush(stdin);
		    		affichTab(t);
				}
			}while(saisie<0 || saisie>1);
		}while(saisie==0);

		//on vérifie que la case confirmée est vide ou non

		verifCase(t,x,y,&vide);

		if(vide==1){
			system("cls");
			printf("La case selectionnee est deja vide. Veuillez en choisir une autre.");
			getc(stdin);
		    fflush(stdin);
		}
		else{
            t[x][y]=0;
        }
	}while(vide==1);
}

void tourOrdiAlt(int t[LIGNE][COLONNE], int premierCoup, int *pNumLigne){
//BUT : Procédure qui fait jouer l'ordi de façon aléatoire
//ENTREE : Tableau t
//SORTIE : Tableau t modifié

	int x=0,y=0;
	int vide=1;	//booléen afin de savoir si une case est vide ou non

	//on génère des coordonnées aléatoires, puis on vérifie que la case correspondante est vide

	do{
		if(premierCoup==1){
			x=rand() % LIGNE;
			*pNumLigne=x;
		}
		else{
			x=*pNumLigne;
		}
		y=rand() % COLONNE;
		verifCase(t,x,y,&vide);
	}while(vide==1);

	//on modifie ensuite le tableau en conséquence

	t[x][y]=0;
}

void verifTab(int t[LIGNE][COLONNE], int *pReste){
//BUT : Procédure qui vérifie que le tableau contient encore des valeurs 1 afin de déterminer s'il y a encore des allumettes en jeu
//ENTREE : Tableau t
//SORTIE : 1 s'il reste encore des allumettes, sinon 0

	int i=0,j=0;
	int trouve=0;	//booléen, sert à savoir si on a trouvé une valeur 1 dans le tableau afin de stopper les boucles

	do{
		do{
			if(t[i][j]==1){
				trouve=1;
			}
			else{
				j++;
			}
		}while(j<COLONNE && trouve==0);
		if(trouve==0){
			i++;
			j=0;
		}
	}while(i<LIGNE && trouve==0);
	if(trouve==1){
		*pReste=1;	//si on a trouve une allumette, c'est qu'il en reste
	}
	else{
		*pReste=0;
	}
}

void initTab(int t[LIGNE][COLONNE]){
//BUT : Procédure qui permet d'initialiser un tableau de booléens et de placer les allumettes (= 1) selon un modèle pyramidal
//ENTREE : Tableau t
//SORTIE : Tableau t rempli de VRAI (= allumettes) et FAUX selon modèle pyamidal

	int i=0,j=0;
	int milieu=(COLONNE-1)/2;	//=3 (milieu de la pyramide)

	for(i=0;i<LIGNE;i++){	//de 0 à 3
		t[i][milieu]=1;		//on place une allumette au milieu de chaque ligne
		//puis on ajoute deux colonnes d'allumettes supplémentaires à chaque ligne
		for(j=0;j<i;j++){
			t[i][milieu-(j+1)]=1;
			t[i][milieu+(j+1)]=1;
		}
		//on remplit le reste de la ligne avec des 0
		for(j=0;j<(milieu-i);j++){
			t[i][j]=0;
			t[i][COLONNE-1-j]=0;
		}
	}
}

void jeuAlt(char username[TAILLE]){
//BUT : Procédure qui annonce le tour du joueur actif et appelle les procédures qui permettent au joueur actif de jouer
//ENTREE : Le nom du joueur
//SORTIE : Message de victoire si l'ordi a retiré la dernière allumette, sinon message de défaite

	int t[LIGNE][COLONNE];	//tableau d'allumettes
	int saisie=100;			//saisie utilisateur
	int nbCoupsMax=MAX;		//nombre de coups maximum du joueur actif
	int numLigne=0;			//numéro de la ligne sur laquelle le joueur actif retire acutellement des allumettes
	int cptCoupsOrdi;		//sert à compter le nombre de coups joués par l'ordi lors d'un tour
	int ligneVide=0;		//booléen, sert à vérifier que la ligne sur laquelle le joueur actif retire actuellement des allumettes est vide ou non
	int joueurActif=0;		//booléen, 0=FAUX, ce n'est pas encore au tour du joueur 1
	int reste=1;			//booléen, 1=VRAI, il reste encore des allumettes
	int premierCoup=0;		//booléen, sert à vérifier qu'il s'agit du premier coup du joueur afin de ne lui demander qu'une seule fois de sélectionner une ligne du tableau

	//initialisation du tableau d'allumettes

	initTab(t);

	//tant qu'il reste des allumettes

	do{

		//on réinitialise les variables

		saisie=100;
		nbCoupsMax=MAX;
		ligneVide=0;

		//c'est au tour de joueur 1

		joueurActif=1;

		//il s'agit de son premier coup

		premierCoup=1;	//VRAI

		//répéter tant qu'il reste des allumettes, des coups au joueur, qu'il n'a pas décidé d'arrêter ou qu'il reste encore des allumettes sur la ligne

		do{

			//le tableau est modifié

			tourJoueurActifAlt(username,t,premierCoup,&numLigne);

			//on décrémente ensuite le nombre de coups restant

			nbCoupsMax--;

			//on vérifie qu'il reste encore des allumettes

			verifTab(t,&reste);

			if(reste==1){
				verifLigne(t,numLigne,&ligneVide);	//s'il reste des allumettes dans le tableau, on vérifie s'il reste des allumettes sur la ligne actuelle
			}

			//s'il reste encore des coups au joueur ainsi que des allumettes et que sa ligne n'est pas vide, on lui propose de retirer une autre allumette

			if(nbCoupsMax>0 && reste==1 && ligneVide==0){
				system("cls");
				printf("Voulez-vous retirer une autre allumette ? Il vous reste %d coup(s).\n",nbCoupsMax);
				printf("1 = Oui\n");
				printf("0 = Non\n");
				scanf("%d",&saisie);
				fflush(stdin);
				if(saisie<0 || saisie>1){
					system("cls");
					printf("Le nombre saisi doit être compris entre 0 et 1. Veuillez recommencer.");
					getc(stdin);
    				fflush(stdin);
				}
			}
			else if(ligneVide==1 && nbCoupsMax>0){
				system("cls");
				printf("Il n'y a plus d'allumette dans la ligne. Fin du tour.");
				getc(stdin);
				fflush(stdin);
			}
			premierCoup=0;	//FAUX ce n'est plus le premier coup
		}while(reste==1 && nbCoupsMax>0 && saisie!=0 && ligneVide==0);

		//dans le cas où le joueur 1 retire la dernière allumette, on vérifie qu'il reste encore des allumettes en jeu avant de faire jouer l'ordinateur

		if(reste==1){

			//c'est au tour de l'ordinateur

			joueurActif=0;

			//c'est son premier coup

			premierCoup=1;

			//on réinitialise les variables

			ligneVide=0;
			cptCoupsOrdi=0;

			//l'ordinateur retire un nombre aléatoire d'allumettes compris entre 1 et 3 (nombre aléatoire compris entre 0 et n-1, donc on ajoute 1 au nombre généré)

			nbCoupsMax=rand() % MAX +1;

			while(reste==1 && nbCoupsMax>0 && ligneVide==0){
				tourOrdiAlt(t,premierCoup,&numLigne);

				verifTab(t,&reste);

				if(reste==1){
					verifLigne(t,numLigne,&ligneVide);	//s'il reste des allumettes dans le tableau, on vérifie s'il reste des allumettes sur la ligne actuelle
					switch(ligneVide){
						case 0 :
							nbCoupsMax--;
							break;
						case 1 :
							nbCoupsMax=0;
							break;
					}
				}
				cptCoupsOrdi++;
				premierCoup=0;
			}
			system("cls");
			printf("C'est au tour de CPU.\n");
			printf("CPU retire %d allumette(s)\n",cptCoupsOrdi);
			getc(stdin);
    		fflush(stdin);
		}
	}while(reste==1);

	//on vérifie qui est le joueur actif pour afficher le message de victoire ou de défaite

	system("cls");
	if(joueurActif==0){
		printf("Victoire !");
	}
	else{
		printf("Vous avez perdu...");
	}
	getc(stdin);
    fflush(stdin);
}

void reglesDuJeu(){
//BUT : Procédure qui affiche les règles du jeu des allumettes ainsi que de sa variante
	system("cls");
	printf("**** JEU DES ALLUMETTES - VARIANTE - REGLES DU JEU ****\n\n");
	printf("Mode alternatif :\n\n");
	printf("Le joueur et l'ordinateur se partagent un tas de 16 allumettes reparties sur 4 lignes.\n");
	printf("A tour de role, ils peuvent retirer 1, 2 ou 3 allumettes du tas.\n");
	printf("Ils ne peuvent retirer des allumettes que dans une seule ligne a chaque tour.\n");
	printf("Celui qui retire la derniere allumette a perdu.\n\n");
	printf("Entree = Menu principal");
    getc(stdin);
    fflush(stdin);
}

void saisieNom(char username[TAILLE]){
//BUT : Procédure qui permet à un joueur d'entrer son nom
//ENTREE : L'utilisateur saisit son nom
//SORTIE : Le nom saisi est affiché sur les différentes interfaces
	system("cls");
	printf("**** JEU DES ALLUMETTES - CHOIX DU NOM ****\n\n");
	printf("Joueur 1, veuillez saisir votre nom : ");
	scanf("%s",username);
    fflush(stdin);
}
