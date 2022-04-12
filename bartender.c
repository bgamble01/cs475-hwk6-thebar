/*
 * bartender.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void *bartender(void *args)
{
	int i;
	for (i = 0; i < num_threads; i++)
	{
		waitForCustomer();
		//now_serving=i;
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	// TODO - synchronize
	sem_wait(cust_arrive);
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
	sem_post(bar_ready);
}

/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	sem_wait(cust_order);
	srand(time(NULL));
	int random = ((rand()%995)+5);
	usleep(random);
	sem_post(drink_done);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
}

/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	sem_wait(cust_art);
	// TODO - synchronize
	// at the register waiting for customer to pay
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");
	sem_wait(cust_payed);
	// got paid by the customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	sem_post(pay_rec);
	sem_wait(cust_left);
}
