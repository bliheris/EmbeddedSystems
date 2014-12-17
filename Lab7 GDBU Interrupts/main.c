#include "GDBU_driver.h"
#include "FIFO.h"
#include "AT91SAM9263.h"

#define TRUE 1
#define FALSE 0
void dbgu_print_ascii(const char *buffer){}
void sendStringUsingFIFO(char* string);

FIFO fifo;
int interruptStatus;
char c;
int interruptTurnedOn = FALSE;

void turnOnInterrupts(){
  AT91C_BASE_AIC->AIC_IECR = 1 << AT91C_ID_SYS;
  SET(AT91C_BASE_DBGU->DBGU_IER, AT91C_US_TXRDY);
  interruptTurnedOn = TRUE;
}

void turnOffInterrupts(){
  AT91C_BASE_AIC->AIC_IDCR = 1 << AT91C_ID_SYS;
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_TXRDY);
  interruptTurnedOn = FALSE;
}

int interruptFromTrasmitterRecieved(){
  return (interruptStatus & AT91C_BASE_DBGU->DBGU_IMR) && (interruptStatus & AT91C_US_TXRDY);
}

void DGBU_INT_handler (void) {
  interruptStatus = AT91C_BASE_DBGU->DBGU_CSR;
  if(interruptFromTrasmitterRecieved()){
    if(FIFO_Get(&fifo, &c) != FIFO_ERROR){
      AT91C_BASE_DBGU->DBGU_THR = c;
    }else{
      turnOffInterrupts();
    }
  }
  AT91C_BASE_AIC->AIC_ICCR = 1 << AT91C_ID_SYS;
}

int main(){

  FIFO_Init(&fifo);
  configureDBGU((unsigned int) DGBU_INT_handler);

  DBGU_sendString((char*)"Welcome to DBGU have fun and good luck!\r\n");
  sendStringUsingFIFO((char*)"Hello world\r\n");
  sendStringUsingFIFO((char*)"Hello world once again\r\n");
  sendStringUsingFIFO((char*)"Goodbye world\r\n");
  sendStringUsingFIFO((char*)"Hello world\r\n");
  sendStringUsingFIFO((char*)"Hello world once again\r\n");
  sendStringUsingFIFO((char*)"Goodbye world\r\n");
  sendStringUsingFIFO((char*)"Hello world\r\n");
  sendStringUsingFIFO((char*)"Hello world once again\r\n");
  sendStringUsingFIFO((char*)"Goodbye world\r\n");

  while(1){
  }

}

void sendStringUsingFIFO(char* string){

  while(*string){
    if(interruptTurnedOn == FALSE){
      turnOnInterrupts();
    }
    
    if(FIFO_Put(&fifo,*string++) == FIFO_ERROR){
      FIFO_Empty(&fifo);
      DBGU_sendString((char*)"Buffer Overflow Error\r\n");
      break;
    }
  }
}

