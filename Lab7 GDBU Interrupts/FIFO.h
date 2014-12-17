#define BUFFERSIZE 256
#define FIFO_OK 1
#define FIFO_ERROR -1

typedef struct FIFO {
	char buffer [BUFFERSIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int size;
}FIFO;

int FIFO_isEmpty (struct FIFO *Fifo);
void FIFO_Init (struct FIFO *Fifo);
void FIFO_Empty (struct FIFO *Fifo);
int FIFO_Put (struct FIFO *Fifo, char Data);
int FIFO_Get (struct FIFO *Fifo, char *Data);


