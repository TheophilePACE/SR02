#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>

/*union semun
{
  int val; //pour SET_VAL
  struct semid_ds *buf;
  ushort * array; //pr getALL setALL
};
*/
