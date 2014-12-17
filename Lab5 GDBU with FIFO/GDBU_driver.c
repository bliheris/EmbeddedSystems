#include "GDBU_driver.h"
#include "AT91SAM9263.h"

void deactivateDBGUinterrupts(){
  /*1. Deactivate DBGU interrupts (register AT91C_BASE_DBGU->DBGU_IDR)*/
  /* Documentation Chapter 30.5.4 DGBU_InterruptDisableRegister */
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_RXRDY);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_TXRDY);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_ENDRX);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_ENDTX);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_OVRE);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_FRAME);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_PARE);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_TXEMPTY);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_TXBUFE);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_RXBUFF);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_COMM_TX);
  SET(AT91C_BASE_DBGU->DBGU_IDR, AT91C_US_COMM_RX);
}

void resetAndTurnOffReceiver(){
  //2. Reset and turn off receiver (register AT91C_BASE_DBGU->DBGU_CR)
  /* Documentation Chapter 30.5.1 DGBU_ControlRegister */
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_RSTRX);
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_RXDIS);
}

void resetAndTurnOffTransmitter(){
  //3. Reset and turn off transmitter (register AT91C_BASE_DBGU->DBGU_CR)
  /* Documentation Chapter 30.5.1 DGBU_ControlRegister */
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_RSTTX);
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_TXDIS);
}

void configureReceiverAndTransmitterAsInputPeripheralsPorts(){
  //4. Configure RxD i TxD DBGU as input peripheral ports (registers AT91C_BASE_PIOC->PIO_ASR and
  //AT91C_BASE_PIOC->PIO_PDR)
  SET(AT91C_BASE_PIOC->PIO_ASR, AT91C_PC30_DRXD);
  SET(AT91C_BASE_PIOC->PIO_PDR, AT91C_PC30_DRXD);

  SET(AT91C_BASE_PIOC->PIO_ASR, AT91C_PC31_DTXD);
  SET(AT91C_BASE_PIOC->PIO_PDR, AT91C_PC31_DTXD);
}

void configureBaudrate(){
  //5. Configure throughput (e.g. 115200 kbps, register AT91C_BASE_DBGU->DBGU_BRGR)
  /* Documentation Chapter 30.5.9 DGBU_BaudRateGeneratorRegister */
  AT91C_BASE_DBGU->DBGU_BRGR = (int)(MASTERCLOCK/(16*BAUDRATE));
}

void configureOperationMode8N1(){
  //6. Configure operation mode (e.g. 8N1, register AT91C_BASE_DBGU->DBGU_MR, flags
  /* Documentation Chapter 30.5.2 DGBU_ModeRegister */
  SET(AT91C_BASE_DBGU->DBGU_MR, AT91C_US_CHMODE_NORMAL);
  SET(AT91C_BASE_DBGU->DBGU_MR, AT91C_US_PAR_NONE);
}

void turnOnReceiver(){
  // 8. Turn on receiver (register AT91C_BASE_DBGU->DBGU_CR),
  /* Documentation Chapter 30.5.1 DGBU_ControlRegister */
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_RXEN);
}

void turnOnTransmitter(){
  // 9. Turn on transmitter if required (register AT91C_BASE_DBGU->DBGU_CR),
  /* Documentation Chapter 30.5.1 DGBU_ControlRegister */
  SET(AT91C_BASE_DBGU->DBGU_CR, AT91C_US_TXEN);
}

void configureDBGU(){
  deactivateDBGUinterrupts();
  resetAndTurnOffReceiver();
  resetAndTurnOffTransmitter();
  configureReceiverAndTransmitterAsInputPeripheralsPorts();
  configureBaudrate();
  configureOperationMode8N1();
  //7. Configure interrupts if used, e.g. Open_DBGU_INT() !! here not used !!
  turnOnReceiver();
  turnOnTransmitter();
}

void DBGU_sendChar(char data){
  /* Documentation Chapter 30.5.6 DGBU_UnitStatusRegister */
  /* Documentation Chapter 30.5.8 DGBU_TransmitHoldingRegister */
  while (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXRDY)) {};
  AT91C_BASE_DBGU->DBGU_THR = data;
}

void DBGU_sendString(char* string){
  while(*string){
    DBGU_sendChar(*string++);
  }
}

char DBGU_readChar(){
  /* Documentation Chapter 30.5.6 DGBU_UnitStatusRegister */
  /* Documentation Chapter 30.5.7 DGBU_ReceiverHoldingRegister */
  while (!(AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY)){};
  return  *((char*) AT91C_DBGU_RHR);
}
