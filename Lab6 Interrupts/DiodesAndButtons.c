#include "DiodesAndButtons.h"
#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"

void turnOnDiode1(){
   SETVALUE(AT91C_BASE_PIOB->PIO_CODR, AT91B_LED1);
}

void turnOffDiode1(){
   SETVALUE(AT91C_BASE_PIOB->PIO_SODR, AT91B_LED1);
}

void turnOnDiode2(){
   SETVALUE(AT91C_BASE_PIOC->PIO_CODR, AT91B_LED2);
}

void turnOffDiode2(){
   SETVALUE(AT91C_BASE_PIOC->PIO_SODR, AT91B_LED2);
}

void initializeDiode1(){
  SETVALUE(AT91C_BASE_PIOB->PIO_PER, AT91B_LED1);
  SETVALUE(AT91C_BASE_PIOB->PIO_OER, AT91B_LED1);
  turnOffDiode1();
}

void initializeDiode2(){
  SETVALUE(AT91C_BASE_PIOC->PIO_PER, AT91B_LED2);
  SETVALUE(AT91C_BASE_PIOC->PIO_OER, AT91B_LED2);
  turnOffDiode2();
}

void turnOnPeripheralClock(){
  SETBIT(*AT91C_PMC_PCER, 4);
}

void enablePushButton1(){
  SETVALUE(AT91C_BASE_PIOC->PIO_PER, AT91B_BP1);
  SETVALUE(AT91C_BASE_PIOC->PIO_ODR, AT91B_BP1);
  SETVALUE(AT91C_BASE_PIOC->PIO_PPUER, AT91B_BP1);
}

void enablePushButton2(){
  SETVALUE(AT91C_BASE_PIOC->PIO_PER, AT91B_BP2);
  SETVALUE(AT91C_BASE_PIOC->PIO_ODR, AT91B_BP2);
  SETVALUE(AT91C_BASE_PIOC->PIO_PPUER, AT91B_BP2);
}

void configureButtons(){
	turnOnPeripheralClock();
	enablePushButton1();
	enablePushButton2();
}

void configureButtonsWithInterrupts(unsigned int handler){
   //1. Configure both ports as inputs (left and right hand buttons), activate clock signal
  turnOnPeripheralClock();
  enablePushButton1();
  enablePushButton2();

  //2. Turn off interrupts for port C/D/E (register AIC_IDCR, mask AT91C_ID_PIOCDE)
  //Documentation 29.8.11
  SETBIT(AT91C_BASE_AIC->AIC_IDCR, AT91C_ID_PIOCDE);
  
  //3. Configure pointer for C/D/E port interrupt handler – use AIC_SVR table
  //AIC_SVR[AT91C_ID_PIOCDE] = ...
  //AT91C_BASE_AIC->AIC_SVR[AT91C_ID_PIOCDE] = (unsigned int) BUTTON_IRQ_handler;
  AT91C_BASE_AIC->AIC_SVR[AT91C_ID_PIOCDE] = handler;

  //4. Configure method of interrupt triggering: high level, (AIC_SMR register, triggered by
  //AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL and priority, e.g. AT91C_AIC_PRIOR_HIGHEST)
  AT91C_BASE_AIC->AIC_SMR[AT91C_ID_PIOCDE] = 
    (AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL | AT91C_AIC_PRIOR_HIGHEST);

  //5. Clear interrupt flag for port C/D/E (register AIC_ICCR)
  SETBIT(AT91C_BASE_AIC->AIC_ICCR, AT91C_ID_PIOCDE);

  //6. Turn on interrupts for both input ports (register PIO_IER)
  SETVALUE(AT91C_BASE_PIOC->PIO_IER, AT91B_BP1);
  SETVALUE(AT91C_BASE_PIOC->PIO_IER, AT91B_BP2);

  //7. Turn on interrupts for C/D/E port (register AIC_IECR)
  SETBIT(AT91C_BASE_AIC->AIC_IECR, AT91C_ID_PIOCDE);
}