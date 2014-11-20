#define BIT(x) (1 << (x))
#define SETBIT(P, B) (P) |= BIT(B)
#define CLRBIT(P, B) (P) &= ~BIT(B)

#define DS1 8
#define DS2 29

#define BP1 5

#define B_PER  (unsigned int*) 0xFFFFF400
#define B_OER  (unsigned int*) 0xFFFFF410
#define B_SODR (unsigned int*) 0xFFFFF430
#define B_CODR (unsigned int*) 0xFFFFF434

#define C_PER  (unsigned int*) 0xFFFFF600
#define C_OER  (unsigned int*) 0xFFFFF610
#define C_ODR  (unsigned int*) 0xFFFFF614
#define C_SODR (unsigned int*) 0xFFFFF630
#define C_CODR (unsigned int*) 0xFFFFF634
#define C_PUER (unsigned int*) 0xFFFFF664
#define C_PinDataStatusR (unsigned int*) 0xFFFFF63C

#define PMC_PCER (unsigned int*) 0xFFFFFC10

void turnOnPeripheralClock(){
  SETBIT(*PMC_PCER, 4);
}

void initializeDiode1(){
  SETBIT(*B_PER, DS1);
  SETBIT(*B_OER, DS1);
}

void initializeDiode2(){
  SETBIT(*C_PER, DS2);
  SETBIT(*C_OER, DS2);
}

void initializePushButton1(){
  SETBIT(*C_PER, BP1);
  SETBIT(*C_ODR, BP1);
  SETBIT(*C_PUER, BP1);
}

void turnOnDiode1(){
   SETBIT(*B_CODR, DS1);
}

void turnOffDiode1(){
   SETBIT(*B_SODR, DS1);
}

void turnOnDiode2(){
   SETBIT(*C_CODR, DS2);
}

void turnOffDiode2(){
   SETBIT(*C_SODR, DS2);
}

int buttonIsPressed(){
  return (*C_PinDataStatusR &= BIT(BP1)) == 0;
}

void checkButtonToControlDiode1(){
  if(buttonIsPressed()){
    turnOffDiode1();
  }else{
    turnOnDiode1();     
  }
}

void wait(){
  volatile int temp;
  for(temp = 0; temp < 1000000; temp++);
}

void waitWithButtonControl(){
  volatile int temp;
  for(temp = 0; temp < 1000000; temp++){
    checkButtonToControlDiode1();
  }
}

void dbgu_print_ascii(const char *a) {}

int main()
{
  
  turnOnPeripheralClock();
  initializePushButton1();
  initializeDiode1();
  initializeDiode2();
  
  turnOffDiode1();
  turnOffDiode2();

  while(1){
    turnOnDiode2();
    waitWithButtonControl();
    turnOffDiode2();
    waitWithButtonControl();    
  }
}

