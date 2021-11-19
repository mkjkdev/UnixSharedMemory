/**
 * @brief shared memory producer
 * 		Places one mark into the shared buffer
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#include "../headers/pv.h"
	
#define BUF_FULL_KEY	0x00b0001	
#define BUF_EMPTY_KEY	0x00b0002
#define READER_END_KEY	0x00b0003

#define SHMKEY	0x00b0001
#define SEED	(unsigned int)299

#define MAXMARKS 100

#include <errno.h>

int main(){
	int reader_end, empty, full; //Semaphore ID's
	int shmid;
	char * buffer; //addr of shared memory for 1 mark

	/* create shared memory object size of char*/
	if((shmid = shmget(SHMKEY, sizeof(char), 0600 | IPC_CREAT)) < 0){
		perror("shmget");
		exit(1);
	}
	//attach shared memory object to this process
	if((buffer = (char *)shmat(shmid, NULL, 0)) < 0){
		perror("smhat");
		exit(1);
	}

	/* create semaphores to manage shared memory */
	empty = getSem(BUF_EMPTY_KEY, 1); ///< sem val of 1 for binary semaphores
	full = getSem(BUF_FULL_KEY, 0);
	reader_end = getSem(READER_END_KEY, 0);

	int count =0;
	int input =1;
	char word[100];
	while(count < MAXMARKS){
		fprintf(stdout, "Please enter a mark, 'end' to exit\n");
		fscanf(stdin, "%s", word);

		char * input = malloc(strlen(word)+1);
		word[strlen(word)] = '\0';
		strcpy(input, word);
		//base case
		if((strcmp(input, "end"))!=0){
			p(empty);
			strcpy(buffer, input);
			//signal that buffer is full for this shared mem key 
			v(full);
			count++;
		}
		else if((strcmp(input, "end"))==0){
			//tell consumer ended
			p(empty);
			strcpy(buffer, input);
			//signal that buffer is full for this shared mem key 
			v(full);
			break;
		}
	}

	//wait for other process to collect
	p0(reader_end);
	//remove shared memory and semaphores
	shmctl(shmid, IPC_RMID, NULL);
	//remove each semaphore ID, creates struct and calls semctl
	rmSem(empty); rmSem(full); rmSem(reader_end);

	return 0;
}