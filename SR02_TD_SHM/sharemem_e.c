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
	//ecriture
	printf("\n\n10 premieres valeurs de X3 dans N : \n");
	for(i=0;i<10;i++)
			{
				*memoire = i*i*i;
				printf("\n filstab[%d]=%d ",i,*memoire);
				memoire++;
			}

	//attente et fermeture de la shm
		printf("debut attente\n");
	sleep(30);
	printf("fin attente\n");
	shmdt(memoiredebut);
	shmctl(shmid,IPC_RMID,NULL);

	return 0;

	}
