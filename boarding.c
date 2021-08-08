//Taha Kashaf
//180020889
//AC21008 - Multi-Paradigm Programming and Data Structures.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boarding.h"

/* Create a new, empty boarding queue, storing a pointer to it in the variable 
   provided (e.g. qPtr) */
int createBoardingQueue(BoardingQueue **qPtr) {

	if(qPtr == NULL)
		return  INVALID_INPUT_PARAMETER;

	if(*qPtr != NULL)
		return INVALID_INPUT_PARAMETER;

	*qPtr = (BoardingQueue*)myMalloc(sizeof(BoardingQueue));

	// check for memory failure
	if(*qPtr == NULL)
	{
			return MEMORY_ALLOCATION_ERROR;
	}

	(*qPtr)->head = NULL;
	(*qPtr)->tail = NULL;

	return SUCCESS;
}


/* Add a new Passenger to the END / tail of the boarding queue using the values provided */
int addPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber) {

	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if(passportNumber < 1 || passportNumber > 88000) {
		return INVALID_INPUT_PARAMETER;
	}

	if(seatNumber < 1 || seatNumber > 150) {
		return INVALID_INPUT_PARAMETER;
	}

	if(name == 0) {
		return INVALID_INPUT_PARAMETER;
	}

	if(strlen(name) < 1 || strlen(name) > 29) {
		return INVALID_INPUT_PARAMETER;
	}


	Passenger *pNewPassenger;
	pNewPassenger = (Passenger*)myMalloc(sizeof(Passenger));

	strcpy(pNewPassenger->name, name);
	pNewPassenger->passportNumber = passportNumber;
	pNewPassenger->seatNumber = seatNumber;

	pNewPassenger->next = NULL;

	if(qPtr->head == NULL && qPtr->tail == NULL) {
		qPtr->head = pNewPassenger;
		qPtr->tail = pNewPassenger; 
	} else {
		qPtr->tail->next = pNewPassenger;
		qPtr->tail = pNewPassenger;
	}

	return SUCCESS;
}


/* Add a new Passenger to the HEAD / front of the boarding queue - they are being added
   to the front of the queue because they are a priority passenger */
int addPriorityPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber) {

	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if(passportNumber < 1 || passportNumber > 88000) {
		return INVALID_INPUT_PARAMETER;
	}

	if(seatNumber < 1 || seatNumber > 150) {
		return INVALID_INPUT_PARAMETER;
	}

	if(strlen(name) < 1 || strlen(name) > 29) {
		return INVALID_INPUT_PARAMETER;
	}

	if(qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	Passenger *pNewPassenger;
	pNewPassenger = (Passenger*)myMalloc(sizeof(Passenger));

	strcpy(pNewPassenger->name, name);
	pNewPassenger->passportNumber = passportNumber;
	pNewPassenger->seatNumber = seatNumber;

	
	if(qPtr->head == NULL && qPtr->tail == NULL) {
		qPtr->head = pNewPassenger;
		qPtr->tail = pNewPassenger; 
	} else {
		pNewPassenger->next = qPtr->head;
		qPtr->head = pNewPassenger;
	}

	return SUCCESS;
}


/* Remove the next passenger from the front of the queue - because they have been processed and can now
   board the plane. This function is equivalent to the 'pop' function that a queue usually
   has, i.e. to remove the item which is currently at the head of the queue. The data for
   the passenger that is being removed should be stored in the variable provided (e.g. 'p') */
int removePassenger(BoardingQueue *qPtr, Passenger *p) {

	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (p == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if(qPtr->head == NULL && qPtr->tail == NULL) {
		return INVALID_QUEUE_OPERATION;
	} else if(qPtr->head == qPtr->tail) {
		Passenger *pTempPassenger = qPtr->head;

		strcpy(p->name, pTempPassenger->name);
		p->passportNumber = pTempPassenger->passportNumber;
		p->seatNumber = pTempPassenger->seatNumber;

		qPtr->head = NULL;
		qPtr->tail = NULL;

		free(pTempPassenger);
	} else {
		Passenger *pTempPassenger = qPtr->head;

		strcpy(p->name, pTempPassenger->name);
		p->passportNumber = pTempPassenger->passportNumber;
		p->seatNumber = pTempPassenger->seatNumber;


		qPtr->head = pTempPassenger->next;

		free(pTempPassenger);		
	}
	
	return SUCCESS;
}


/* Peek at the head of the queue to get the data for the passenger that is next
   to board the plane. The passenger data should be stored in the variable provided (e.g. 'p')  */
int peekAtHeadPassenger(BoardingQueue *qPtr, Passenger *p) {
	
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (p == NULL) {
		return INVALID_INPUT_PARAMETER;
	}
	
	if(qPtr->head == NULL && qPtr->tail == NULL) {
		return INVALID_QUEUE_OPERATION;
	} else {
		Passenger *pTempPassenger = qPtr->head;
		
		strcpy(p->name, pTempPassenger->name);
		p->passportNumber = pTempPassenger->passportNumber;
		p->seatNumber = pTempPassenger->seatNumber;

		free(pTempPassenger);
	}

	return SUCCESS;
}


/* Peek at the tail of the queue to get the data for the passenger that is currently last in
   line to board the plane. The passenger data should be stored in the variable provided (e.g. 'p')  */
int peekAtTailPassenger(BoardingQueue *qPtr, Passenger *p) {

	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (p == NULL) {
		return INVALID_INPUT_PARAMETER;
	}
	
	if(qPtr->head == NULL && qPtr->tail == NULL) {
		return INVALID_QUEUE_OPERATION;
	} else {
		Passenger *pTempPassenger = qPtr->tail;
		
		strcpy(p->name, pTempPassenger->name);
		p->passportNumber = pTempPassenger->passportNumber;
		p->seatNumber = pTempPassenger->seatNumber;

		free(pTempPassenger);
	}

	return SUCCESS;
}


/* Empty the boarding queue, freeing up any memory that it is currently using */
int clearBoardingQueue(BoardingQueue *qPtr) {
	
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if(qPtr->head == NULL && qPtr->tail == NULL) {
		return INVALID_QUEUE_OPERATION;
	}

	while (qPtr->head != NULL && qPtr->tail !=NULL) 
	{
		
		Passenger *currentTopPassenger = qPtr->head;

		qPtr->head = qPtr->head->next;

		free(currentTopPassenger);
	}

	free(qPtr);

	return SUCCESS;
}

/* ADVANCED - EXTRA MARKS!
   Sort the boarding queue so that passengers are arranged based on their seat number, from lowest
   to highest. This is to allow the plane to be boarded based on seat numbers. */
int sortBoardingQueue(BoardingQueue *qPtr) {
	
	if (qPtr == NULL) {
		return INVALID_INPUT_PARAMETER;
	}

	if (qPtr->head == qPtr->tail) {
		return SUCCESS;
	}

	int s = 0;

	Passenger *compare1;
	compare1 = (Passenger*)myMalloc(sizeof(Passenger));
	Passenger *compare2;
	compare2 = (Passenger*)myMalloc(sizeof(Passenger));
	Passenger *temp1 = NULL;
	temp1 = (Passenger*)myMalloc(sizeof(Passenger));
	Passenger *temp2 = NULL;
	temp2 = (Passenger*)myMalloc(sizeof(Passenger));



		do {

			compare1 = qPtr->head;
			compare2 = qPtr->head->next;

			s = 0;
			
			while (compare1->next != NULL) {
				
				if (compare1->seatNumber > compare2->seatNumber) {
				
					strcpy(temp1->name, compare1->name);
					temp1->passportNumber = compare1->passportNumber;
					temp1->seatNumber = compare1->seatNumber;

					strcpy(temp2->name, compare2->name);
					temp2->passportNumber = compare2->passportNumber;
					temp2->seatNumber = compare2->seatNumber;

					strcpy(compare1->name, temp2->name);
					compare1->passportNumber = temp2->passportNumber;
					compare1->seatNumber = temp2->seatNumber;

					strcpy(compare2->name, temp1->name);
					compare2->passportNumber = temp1->passportNumber;
					compare2->seatNumber = temp1->seatNumber;

					compare1 = compare1->next;
					compare2 = compare2->next;

					s = 1;

				} else {
					
					compare1 = compare1->next;
					compare2 = compare2->next;

				}

			}
		
		} while (s == 1);

	free(compare1);
	free(compare2);
	free(temp1);
	free(temp2);	

	return SUCCESS;
}
