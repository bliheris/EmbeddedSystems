#include "FIFO.h"

void FIFO_Init (struct FIFO *Fifo){
 	Fifo->head=0;
 	Fifo->tail=0;
}

void FIFO_Empty (struct FIFO *Fifo){
	Fifo->head = Fifo->tail;
}

int FIFO_isEmpty(void){
	return (Fifo->head == Fifo->tail);
}

int FIFO_isFull(void){
	return ((Fifo->tail - Fifo->head) == 1) || ((Fifo->tail - Fifo->head) == BUFFERSIZE);
}

int FIFO_Put (struct FIFO *Fifo, char Data){
	if (FIFO_isFull()){
		return FIFO_ERROR; 
	};
	
	Fifo->buffer[Fifo->head] = Data;
	Fifo->head = (Fifo->head + 1) % (BUFFERSIZE);
	return 1;
}

int FIFO_Get (struct FIFO *Fifo, char *Data){
	if (FIFO_isEmpty()){
		return FIFO_ERROR;
	}

	*Data = Fifo->buffer[Fifo->tail];
	Fifo->tail = (Fifo->tail + 1) % (BUFFERSIZE);
	return 1;
}
