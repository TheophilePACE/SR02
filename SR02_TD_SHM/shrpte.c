#include "sharemem.h"

int main() {

	//creation des tableaux
	int tab1[10], tab2[10];
	int i;
	for(i=0;i<10;i++)
	{
		tab1[i]=1;
		tab2[i]=1;
	}

	//creation de la shared memory
 	key_t cle=ftok("sharemem.h",0);
 	printf("\n Cle : %d\n",cle);
	int shmid;
	shmid=shmget(cle,10*sizeof(int),IPC_CREAT|0666);
	int* memoire, *memoiredebut;
	memoire=shmat(shmid, NULL, 0);
	printf("\nAdresse memoire : %d\n",memoire);
	memoiredebut=memoire;
	if(memoire==-1) printf(strerror(errno));

	// CETTE PARTIE LÀ NE MARCHE PAS VOIR QUESTION 3
	//Création et initialisation du tab de vecteur
	printf("\n\n Tableau de 5 pointeurs sur vecteurs tridimensionnels  : \n");
	int **tab=memoire;
	for(i=0;i<5;i++)
			{
				tab[i]=malloc(3*(sizeof(int))); //allocation du vecteur i

				printf("\n Adresse Vecteur numero %d=%d \n ",i,tab[i]);
				for(int j=0;j<3;j++)
 					{
						//initialisation du vecteur i
						*(tab[i]+j)=i*100 + j;
						printf("V%d [%d]=%d\n",i,j,*(tab[i]+j));
 					}
			}

	//envoie dans la shm

	for(i=0;i<5;i++)
	{
		*(memoire+i) = tab[i]; //copie des Adresses dans le shm
	}

	// VERSION CORRIGÉE
	int tailleTAB = 5*sizeof(int*);
	int tailleVect = 3*sizeof(int);
	int ptrvect = 0;
	for(i=0;i<5;i++)
			{
				ptrvect= tailleTAB+ i*tailleVect;//décalage depuis la case zero jusqu'au vecteur i
				*(memoire +i) = ptrvect ; //On stocke  dans la case i le décalage depuis la case zero jusqu'au vecteur i
				printf("\n Adresse Vect numero%d= %d ",i,*(memoire+i));

				for(int j = 0;j<3;j++)
				{
					*(memoire+ptrvect+j) = i*100+j; // on stocke à la case memoire j du vect i (case &, 2 et 3) la formule i*100 + j
					printf("V%d [%d]=%d\n",i,j,*(memoire+ptrvect+j));



				}

			}


	//attente et fermeture de la shm
		printf("debut attente\n");
	sleep(40);
	printf("fin attente\n");
	shmdt(memoiredebut);
	shmctl(shmid,IPC_RMID,NULL);

	return 0;

	}
