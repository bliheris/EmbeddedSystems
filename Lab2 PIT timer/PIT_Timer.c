#include "PIT_Timer.h"

void clearPIST(){
  volatile unsigned int temp = *PIT_PIVR;
}

void initializeTimer(){
  *PIT_MR = 6250;
  clearPIST();
}

void timerWait(int miliseconds){
  SETBIT(*PIT_MR, 24);
  while(miliseconds--){
    while((*PIT_SR & BIT(0)) == 0){}
    clearPIST();
  }
}