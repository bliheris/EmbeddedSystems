#include "GDBU_driver.h"
#include "FIFO.h"

#define ESCAPE_CHAR '\r'

void dbgu_print_ascii(const char *buffer){}
void readDataUsingBuffer();
void printFIFOcontent();

FIFO fifo;

int main(){
  configureDBGU();
  FIFO_Init(&fifo);

  DBGU_sendString((char*)"Welcome to DBGU have fun and good luck!\r\n",-1);
  while(1){
    readDataUsingBuffer();
  }
}

void readDataUsingBuffer(){
  int fifoStatus;
  char c;

  do {
    c = DBGU_readChar();
    if(c == ESCAPE_CHAR){
      break;
    }
    fifoStatus = FIFO_Put(&fifo,c);
  } while (fifoStatus != FIFO_ERROR);

  if(fifoStatus == FIFO_ERROR){
    DBGU_sendString((char*)"Buffer Overflow Error\r\n");
    FIFO_Empty(&fifo);
  }

  printFIFOcontent();
}

void printFIFOcontent(){
  char c;
  while(FIFO_Get(&fifo, &c) != FIFO_ERROR){
    DBGU_sendChar(c);
  }
  DBGU_sendString((char*)"\r\n");
}