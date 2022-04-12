/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
unsigned int now_serving;	// customer's ID who is being served

//TODO - declare some semaphores

sem_t* cust_arrive;
sem_t* cust_order;
sem_t* cust_art;
sem_t* cust_payed;
sem_t* cust_left;
sem_t* bar_ready;
sem_t* drink_done;
sem_t* pay_rec;



#endif /* GLOBALS_H_ */
