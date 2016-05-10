//implémentation des fonctions de la librairie lsempv

#include "semaph.h" //en-tete spéciale sempahore
//static int semid;
#include "sem_pv.h"



int init_semaphore(void){ //creation de sémaphore.
  int semid;
  semid=semget(IPC_PRIVATE, N_SEM, IPC_CREAT|IPC_EXCL);
  if(semid==-1)
  {
    if(errno==EEXIST) //déjà appelé
      return -1;
    return -2;//échec autre
  }
  union semun initialisateur ;
  initialisateur.val= 0;
  semctl(semid, N_SEM,SETALL,&initialisateur );
  return 0; //réussite
}

int detruire_semaphore(void)
{
  int semid;
  semid=semget(IPC_PRIVATE, N_SEM, IPC_CREAT|IPC_EXCL);
  int rslt = semctl(semid, N_SEM,IPC_RMID); //renvoie -1 en cas d'échec
  return rslt;

}

int val_sem(int sem, int val)
{
  int semid;
  semid=semget(IPC_PRIVATE, N_SEM, 0);
  if(semid==-1)
  {
    if(errno==ENOENT)
      return -1; //pas de groupe de sémaphore
    else //ou if(sem>=N_SEM||sem<0)
        return -2;//sem incorrect
  }
  union semun valeur ;
  valeur.val= val;
  int success = semctl(semid,sem,SETVAL,valeur);
  return success; //succès; reotur de semctl;
}

int P(int sem)
{
  int semid;
  semid=semget(IPC_PRIVATE, N_SEM, 0);
  if(semid==-1)
  {
    if(errno==ENOENT)
      return -1; //pas de groupe de sémaphore
    else //ou if(sem>=N_SEM||sem<0)
        return -2;//sem incorrect
  }
  int success ;
  struct sembuf operation;
    operation.sem_num=sem; //numero du semaphore visé
    operation.sem_op=-1; //ajouter cette valeur à semval
  //operation.sem_flag= ???
  success=semop(semid,&operation, 1);
  return success; //succès; reotur de semop;
}

int V(int sem)
{
  int semid;
  semid=semget(IPC_PRIVATE, N_SEM, 0);
  if(semid==-1)
  {
    if(errno==ENOENT)
      return -1; //pas de groupe de sémaphore
    else //ou if(sem>=N_SEM||sem<0)
        return -2;//sem incorrect
  }
  int success ;
  struct sembuf operation;
    operation.sem_num=sem; //numero du semaphore visé
    operation.sem_op=1; //ajouter cette valeur à semval
  //operation.sem_flag= ???
  success=semop(semid,&operation, 1);
  return success; //succès; reotur de semop;
}
