#include "DiodesAndButtons.h"

void dbgu_print_ascii(const char *a) {}
void checkButtonToControlDiode1();
void waitWithButtonControl();

int main()
{
  configureButtons();
  enableDiode1();
  enableDiode2();
  
  while(1){
    turnOnDiode2();
    waitWithButtonControl();
    turnOffDiode2();
    waitWithButtonControl();
  }
}

void waitWithButtonControl(){
  volatile int temp;
  for(temp = 0; temp < 1000000; temp++){
    checkButtonToControlDiode1();
  }
}

void checkButtonToControlDiode1(){
  if(button1IsPressed()){
    turnOnDiode1();     
  }else if(button2IsPressed()){
    turnOffDiode1();
  }
}


