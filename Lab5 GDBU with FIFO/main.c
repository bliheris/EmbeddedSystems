#include "GDBU_driver.h"
#include "FIFO.h"

#define ESCAPE_CHAR '\r'

void dbgu_print_ascii(const char *buffer){}
void sendStringUsingFIFO(char* string);
void readDataUsingFIFO();
void printFIFOcontent();

FIFO fifo;
int fifoStatus = FIFO_OK;

int main(){
  configureDBGU();
  FIFO_Init(&fifo);

  DBGU_sendString((char*)"Welcome to DBGU have fun and good luck!\r\n");
  
  sendStringUsingFIFO((char*)"Hello world!\r\n");

  if(fifoStatus == FIFO_OK){
    printFIFOcontent();
  }
  FIFO_Empty(&fifo);

  while(1){
    readDataUsingFIFO();
  }
}

void sendStringUsingFIFO(char* string){
  while(*string){
    fifoStatus = FIFO_Put(&fifo,*string++);
    if(fifoStatus == FIFO_ERROR){
      FIFO_Empty(&fifo);
      DBGU_sendString((char*)"Buffer Overflow Error\r\n");
      break;
    }
  }
}

void readDataUsingFIFO(){
  int fs = 0;
  char c;

  do {
    c = DBGU_readChar();
    if(c == ESCAPE_CHAR){
      break;
    }
    fs = FIFO_Put(&fifo,c);
  } while (fs != FIFO_ERROR);

  if(fs == FIFO_ERROR){
    DBGU_sendString((char*)"Buffer Overflow Error");
    FIFO_Empty(&fifo);
  }else{
    printFIFOcontent();
  }
}

void printFIFOcontent(){
  char c;
  while(FIFO_Get(&fifo, &c) != FIFO_ERROR){
    DBGU_sendChar(c);
  }
  DBGU_sendString((char*)"\r\n");
}