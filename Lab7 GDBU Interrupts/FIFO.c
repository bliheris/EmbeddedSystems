#include "FIFO.h"

void FIFO_Init (struct FIFO *Fifo){
 	Fifo->head = 0;
 	Fifo->tail = 0;
 	Fifo->size = 0;
}

void FIFO_Empty (struct FIFO *Fifo){
	Fifo->head = Fifo->tail;
	Fifo->size = 0;
}

int FIFO_isEmpty(struct FIFO *Fifo){
	return Fifo->size == 0;
}

int FIFO_isFull(struct FIFO *Fifo){
	return Fifo->size == BUFFERSIZE;
}

int FIFO_Put (struct FIFO *Fifo, char Data){
	if (FIFO_isFull(Fifo)){
		return FIFO_ERROR; 
	};
	
	Fifo->buffer[Fifo->head] = Data;
	Fifo->head = (Fifo->head + 1) % (BUFFERSIZE);
	Fifo->size++;
	return FIFO_OK;
}

int FIFO_Get (struct FIFO *Fifo, char *Data){
	if (FIFO_isEmpty(Fifo)){
		return FIFO_ERROR;
	}

	*Data = Fifo->buffer[Fifo->tail];
	Fifo->tail = (Fifo->tail + 1) % (BUFFERSIZE);
	Fifo->size--;
	return FIFO_OK;
}
