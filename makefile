#makefile for Unix shared memory project
#Mitchel King
#19/11/2021

all: build/sharedProducer build/sharedConsumer

build/sharedProducer: pv.o sharedMemProd.o
	gcc -Wall pv.o sharedMemProd.o -o build/sharedProducer

build/sharedConsumer: pv.o sharedMemCons.o
	gcc -Wall pv.o sharedMemCons.o -o build/sharedConsumer

pv.o: source/pv.c
	gcc -c source/pv.c

sharedMemProd.o: source/pv.c source/sharedMemProd.c
	gcc -c source/pv.c source/sharedMemProd.c

sharedMemCons.o: source/pv.c source/sharedMemCons.c
	gcc -c source/pv.c source/sharedMemCons.c

clean:
	rm *.o
	rm build/*
