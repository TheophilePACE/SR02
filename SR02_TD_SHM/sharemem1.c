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
	key_t cle=IPC_PRIVATE;
	int shmid;
	shmid=shmget(cle,10*sizeof(int),IPC_CREAT|0666);
	int* memoire, *memoiredebut;
	memoire=shmat(shmid, NULL, 0);
	memoiredebut=memoire;
	if(memoire==-1) printf(strerror(errno));
	
	
	pid_t pid =fork();
	switch(pid)
	{
		case(-1): printf("Erreur Fork\n");
		break;
		
		case(0): printf("Processus Fils\n"); //fils
		//impression1
			for(i=0;i<10;i++)
			{
				tab2[i]=2;
				printf("filstab[%d]=%d , ",i,tab2[i]);
			}
			printf("\n");
			sleep(2);
			//impression 2
			for(i=0;i<10;i++)
			{
				*memoire = tab2[i];
				printf("filstab[%d]=%d , ",i,*memoire);
				memoire++;
			}			
			printf("\n");

			sleep(2);
			shmdt(memoiredebut);
			printf("retour fils\n");
			return 0;


			
			
			
		break;
		
		default:  //pere
			sleep(1);
			printf("Processus Pere\n");
			//impression 1
			for(i=0;i<10;i++)
			{
				printf("peretab[%d]=%d , ",i,tab2[i]);
			}
			printf("\n");
			sleep(2);
			//impression2
			for(i=0;i<10;i++)
			{
				printf("peretab[%d]=%d , ",i,*memoire);
				memoire++;
			}
			printf("\n");
			printf(" Attente retour fils\n");
			int status;
			waitpid(pid,&status,0);
			printf("retour du fils attrape\n fermeture du SHM\n");
			shmdt(memoiredebut);
			shmctl(shmid,IPC_RMID,NULL);
			

		
		break;
	}
	
	return 0;
	}
