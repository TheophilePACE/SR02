#include "sharemem.h"

int main() {


	//acces a la shared memory
 	key_t cle=ftok("sharemem.h",0);
 	printf("Cle : %d \n",cle);
	int shmid;
	shmid=shmget(cle,10*sizeof(int),IPC_CREAT|0666);
	int* memoire, *memoiredebut;
	memoire=shmat(shmid, NULL, 0);
	memoiredebut=memoire;
	printf("Adresse memoire : %d\n",memoire);
	if(memoire==-1) printf(strerror(errno));
	int i;

	for(i=0;i<10;i++)
			{
				printf("filstab[%d]=%d  ",i,*memoire);
				memoire++;
				printf("\n");
			}

	printf("Fin de lecture\n");
	shmdt(memoiredebut);
	return 0;
	}
