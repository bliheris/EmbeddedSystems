#include "DiodesAndButtons.h"
#include "AT91SAM9263.h"

void turnOnDiode1(){
   SETBIT(AT91C_BASE_PIOB->PIO_CODR, DS1);
}

void turnOffDiode1(){
   SETBIT(AT91C_BASE_PIOB->PIO_SODR, DS1);
}

void turnOnDiode2(){
   SETBIT(AT91C_BASE_PIOC->PIO_CODR, DS2);
}

void turnOffDiode2(){
   SETBIT(AT91C_BASE_PIOC->PIO_SODR, DS2);
}

void initializeDiode1(){
  SETBIT(AT91C_BASE_PIOB->PIO_PER, DS1);
  SETBIT(AT91C_BASE_PIOB->PIO_OER, DS1);
  turnOffDiode1();
}

void initializeDiode2(){
  SETBIT(AT91C_BASE_PIOC->PIO_PER, DS2);
  SETBIT(AT91C_BASE_PIOC->PIO_OER, DS2);
  turnOffDiode2();
}

void turnOnPeripheralClock(){
  SETBIT(*AT91C_PMC_PCER, 4);
}

void enablePushButton1(){
  SETBIT(AT91C_BASE_PIOC->PIO_PER, BP1);
  SETBIT(AT91C_BASE_PIOC->PIO_ODR, BP1);
  SETBIT(AT91C_BASE_PIOC->PIO_PPUER, BP1);
}

void enablePushButton2(){
  SETBIT(AT91C_BASE_PIOC->PIO_PER, BP2);
  SETBIT(AT91C_BASE_PIOC->PIO_ODR, BP2);
  SETBIT(AT91C_BASE_PIOC->PIO_PPUER, BP2);
}

void configureButtons(){
	turnOnPeripheralClock();
	enablePushButton1();
	enablePushButton2();
}

int button1IsPressed(){
  return (AT91C_BASE_PIOC->PIO_PDSR & BIT(BP1)) == 0;
}
int button2IsPressed(){
  return (AT91C_BASE_PIOC->PIO_PDSR & BIT(BP2)) == 0;
}