/**
 * @brief shared memory consumer
 * 		Collects marks from shared memory assoaciated with SHMKEY
 * 
 * @author Mitchel King
 * @date 17/11/2021
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#include "pv.h"
	
#define BUF_FULL_KEY	0x00b0001	
#define BUF_EMPTY_KEY	0x00b0002
#define READER_END_KEY	0x00b0003

#define SHMKEY	0x00b0001
#define SEED	(unsigned int)299

#define MAXMARKS 100

int main(){
	//semaphores
	int reader_end, empty, full;
	int shmid;
	char * buffer; //addr of shared memory for 1 mark

	//create shared memoryy
	if((shmid = shmget(SHMKEY, sizeof(char), 0600 | IPC_CREAT ))< 0){
		perror("shmget");
		exit(1);
	}
	//attach to this process
	if((buffer = shmat(shmid, NULL, 0)) <0){
		perror("shmat");
		exit(1);
	}

	//create and get semaphore ID's
	empty = getSem(BUF_EMPTY_KEY, 1);
	full = getSem(BUF_FULL_KEY, 0);
	reader_end = getSem(READER_END_KEY, 0);

	int results[MAXMARKS];
	int count =0;
	char word[100];
	while(1){
		//base case
		if(strcmp(word, "end")==0){
			break;
		}
		//wait until buffer full
		p(full);
		strcpy(word, buffer);
		results[count] = atoi(word);
		v(empty);
		fprintf(stdout, "The item is: %s\n", word);
		count++;
	}

	//display average mark on the screen
	if(count > 0){
		double average;
		double total;
		for(int i=0;i<=count;i++){
			total += results[i];
		}
		average = (total / count);
		fprintf(stdout, "average mark: %f\n", average);
	}
	else{
		fprintf(stdout, "No marks received\n");
	}
	//Tell producer we have ended
	v0(reader_end);
	return 0;
}