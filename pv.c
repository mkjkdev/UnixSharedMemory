#include "pv.h"

#include <stdio.h> ///< perror
#include <errno.h> ///< errno
#include <sys/sem.h> ///< semget, semctl, semop
#include <stdlib.h> ///< exit

/* Create, initialize return semID */
int getSem(int key, int semVal){
	int semId;

	/* union to to set default val=semVal, call semctl */
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int * array;
	} arg;
	//create semaphore with key
	//return id if already exists for key
	semId = semget((key_t)key, 1, 0666 | IPC_CREAT | IPC_EXCL);
	if(semId < 0){
		if(errno ==EEXIST){
			//key exists, return semaphore ID
			if((semId = semget((key_t)key, 1, 0666)) != -1){
				return semId;
			}
			perror("semget");
			exit(1);
		}
	}

	/* Set semaphore value */
	arg.val = semVal;
	if(semctl(semId, 0, SETVAL, arg) < 0){
		perror("Cannot initialize semaphore value");
		exit(2);
	}
	return semId;
}

/* Remove semaphore at semId */
void rmSem(int semId){
	//union for semctl
	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short int * array;
	} arg;
	//remove
	if(semctl(semId, 0, IPC_RMID, arg) < 0){
		perror("semctl IPC_RMD");
		exit(1);
	}
}

/* SEM_UNDO version */
void p(int semId){
	//struct for semop
	struct sembuf sb;
	//set values, SEM_UNDO
	sb = (struct sembuf){.sem_num = 0,.sem_op = -1,.sem_flg = SEM_UNDO};
	//semop for atomic operations
	if(semop(semId, &sb, 1) < 0){
		perror("semop at p");
		exit(1);
	}
}

/* SEM_UNDO version */
void v(int semId){
	struct sembuf sb;
	sb = (struct sembuf){.sem_num = 0,.sem_op = 1,.sem_flg = SEM_UNDO};
	if(semop(semId, &sb, 1) < 0){
		perror("semop at v");
		exit(1);
	}
}

/* No SEM_UNDO version */
void p0(int semId){
	struct sembuf sb;
	//set values of struct, NO SEM_UNDO
	sb = (struct sembuf){.sem_num = 0,.sem_op = -1,.sem_flg = 0};
	if(semop(semId, &sb, 1) < 0){
		perror("semop at p");
		exit(1);
	}
}

/* No SEM_UNDO version */
void v0(int semId){
	struct sembuf sb;
	sb = (struct sembuf){.sem_num = 0,.sem_op = 1,.sem_flg = 0};
	if(semop(semId, &sb, 1) < 0){
		perror("semop at v");
		exit(1);
	}
}