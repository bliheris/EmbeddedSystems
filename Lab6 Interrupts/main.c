#include "DiodesAndButtons.h"
#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"

void dbgu_print_ascii(const char *a) {}

int interruptStatus;

void BUTTON_IRQ_handler (void) {
  //If flag on the suitable bit-position is active the button is/was pressed (PIO_ISR)
  //Read PIO_ISR status register to clear the flag
  interruptStatus = AT91C_BASE_PIOC->PIO_ISR;
  if(interruptStatus & AT91B_BP1){
    turnOnDiode1();
  }else if(interruptStatus & AT91B_BP2){
    turnOffDiode1();
  }
}

int main()
{
  initializeDiode1();
  initializeDiode2();
  configureButtonsWithInterrupts((unsigned int) BUTTON_IRQ_handler);

  while(1){
  }
}
