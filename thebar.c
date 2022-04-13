/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char **argv)
{
	if(argc!=2){
		printf("Usage: [num customer threads] \n");
		return 0;
	}

	num_threads = atoi(argv[1]);
	printBanner();
	init(); // initialize semaphores
	int i;
	pthread_t threads[num_threads+1];
	int args[num_threads+1];
	for(i=0; i<num_threads+1;i++){
		args[i]=i;
	}

	// TODO - fire off customer thread

	for(i=0;i<num_threads;i++){
		pthread_create(&threads[i],NULL,customer,&args[i]);
	}
	
	// TODO - fire off bartender thread

	pthread_create(&threads[num_threads],NULL,bartender,NULL);

	// TODO - wait for all threads to finish

	for (i = 0; i < num_threads+1; i++){
    	pthread_join(threads[i], NULL);
  	}


	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	sem_unlink("/cust_arrive");
	sem_unlink("/cust_order");
	sem_unlink("/cust_art");
	sem_unlink("/cust_payed");
	sem_unlink("/cust_left");
	sem_unlink("/bar_ready");
	sem_unlink("/drink_done");
	sem_unlink("/pay_rec");

	cust_arrive = sem_open("/cust_arrive",O_CREAT,0600,0);
	cust_order = sem_open("/cust_order",O_CREAT,0600,0);
	cust_art = sem_open("/cust_art",O_CREAT,0600,0);
	cust_payed = sem_open("/cust_payed",O_CREAT,0600,0);
	cust_left = sem_open("/cust_left",O_CREAT,0600,0);
	bar_ready = sem_open("/bar_ready",O_CREAT,0600,0);
	drink_done = sem_open("/drink_done",O_CREAT,0600,0);
	pay_rec = sem_open("/pay_rec",O_CREAT,0600,0);

	// TODO - create semaphores
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	sem_close(cust_arrive);
	sem_close(cust_order);
	sem_close(cust_art);
	sem_close(cust_payed);
	sem_close(cust_left);
	sem_close(bar_ready);
	sem_close(drink_done);
	sem_close(pay_rec);

	sem_unlink("/cust_arrive");
	sem_unlink("/cust_order");
	sem_unlink("/cust_art");
	sem_unlink("/cust_payed");
	sem_unlink("/cust_left");
	sem_unlink("/bar_ready");
	sem_unlink("/drink_done");
	sem_unlink("/pay_rec");
}
