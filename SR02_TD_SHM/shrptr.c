#include "sharemem.h"

int main() {
  //

	//acces a la shared memory
 	key_t cle=ftok("sharemem.h",0);
 	printf("Cle : %d \n",cle);
	int shmid;
	shmid=shmget(cle,10*sizeof(int),IPC_CREAT|0666);
	int* memoire, *memoiredebut;
	memoire=shmat(shmid, NULL, 0);
	memoiredebut=memoire;
	printf("\n\nAdresse memoire : %d\n",memoire);
	if(memoire==-1) printf(strerror(errno));
  //second shm pour voir la différence
  /*
  key_t cle2=ftok("shrptr.c",0); //creer uniquement pour ce programme, non partagé
 	printf("Cle2 : %d \n",cle2);
	int shmid2;
	shmid2=shmget(cle2,10*sizeof(int),IPC_CREAT|0666);
	int* memoire2;
	memoire2=shmat(shmid2, NULL, 0);
	printf("Adresse memoire2 : %d\n",memoire2);
	if(memoire2==-1) printf(strerror(errno));
*/
  //lecture
	int i;

	for(i=0;i<5;i++)
			{
				printf("Adresse vect %d =%d  ",i,*(memoire+i));
				printf("\n");
			}
      for(i=0;i<5;i++)
        {
          printf(" vect %d = ",i);
          for(int j=0;j<3;j++)
          {
            int * adm = *(memoire + i);
              //échec, segmentation fault QUAND on veut lire l'adresse désigné par les pointeurs

            printf("V(%d) = %d", j,*(adm));
          }
          printf("\n");
        }


	printf("Fin de lecture\n");
	shmdt(memoiredebut);
	return 0;
	}
