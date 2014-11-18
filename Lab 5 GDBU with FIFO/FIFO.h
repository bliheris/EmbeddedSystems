#define BUFFERSIZE 8
#define FIFO_ERROR -1

typedef struct FIFO {
	char buffer [BUFFERSIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int size; 
};

void FIFO_Init (struct FIFO *Fifo);
void FIFO_Empty (struct FIFO *Fifo);
int FIFO_Put (struct FIFO *Fifo, char Data);
int FIFO_Get (struct FIFO *Fifo, char *Data);


