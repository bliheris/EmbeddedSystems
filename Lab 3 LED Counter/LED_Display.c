#include "LED_Display.h"
#include "AT91SAM9263.h"

/*    
    a
  f|_|b __g
  e|_|c
    d  
*/
int digits[10][7] = {
  /* 0 */ {ON, ON, ON, ON, ON, ON, OFF},     
  /* 1 */ {OFF, ON, ON, OFF, OFF, OFF, OFF},
  /* 2 */ {ON, ON, OFF, ON, ON, OFF, ON},    
  /* 3 */ {ON, ON, ON, ON, OFF, OFF, ON},
  /* 4 */ {OFF, ON, ON, OFF, OFF, ON, ON},
  /* 5 */ {ON, OFF, ON, ON, OFF, ON, ON},
  /* 6 */ {ON, OFF, ON, ON, ON, ON, ON},
  /* 7 */ {ON, ON, ON, OFF, OFF, OFF, OFF},
  /* 8 */ {ON, ON, ON, ON, ON, ON, ON},
  /* 9 */ {ON, ON, ON, ON, OFF, ON, ON}
};

int devices[10] = {
  BRIGHTNESS_CONTROL,LEFT,RIGHT,
  SEGMENT_A,SEGMENT_B,SEGMENT_C,SEGMENT_D,
  SEGMENT_E,SEGMENT_F,SEGMENT_G
};

void turnOnLeftCounter(){
  SETBIT(AT91C_BASE_PIOB->PIO_CODR, LEFT);
}

void turnOffLeftCounter(){
  SETBIT(AT91C_BASE_PIOB->PIO_SODR, LEFT);
}

void turnOnRightCounter(){
  SETBIT(AT91C_BASE_PIOB->PIO_CODR, RIGHT);
}

void turnOffRightCounter(){
  SETBIT(AT91C_BASE_PIOB->PIO_SODR, RIGHT);
}

void turnOnSegment(int segment){
  SETBIT(AT91C_BASE_PIOB->PIO_SODR, segment);
}
void turnOffSegment(int segment){
  SETBIT(AT91C_BASE_PIOB->PIO_CODR, segment);
}

void setSegment(int segment, int status){
  if(status == ON){
    turnOnSegment(segment);
  }else{
    turnOffSegment(segment);
  }
}

void turnOffAllSegments(){
  turnOffSegment(SEGMENT_A);
  turnOffSegment(SEGMENT_B);
  turnOffSegment(SEGMENT_C);
  turnOffSegment(SEGMENT_D);
  turnOffSegment(SEGMENT_E);
  turnOffSegment(SEGMENT_F);
  turnOffSegment(SEGMENT_G);
}

void intializeLEDdisplay(){
  int i;
  for(i = 0; i < 10; i++){
    SETBIT(AT91C_BASE_PIOB->PIO_PER, devices[i]);
    SETBIT(AT91C_BASE_PIOB->PIO_OER, devices[i]);
  }

  turnOffLeftCounter();
  turnOffRightCounter();
  turnOffAllSegments();
}

void displayDigit(int digit){
  setSegment(SEGMENT_A, digits[digit][0]);
  setSegment(SEGMENT_B, digits[digit][1]);
  setSegment(SEGMENT_C, digits[digit][2]);
  setSegment(SEGMENT_D, digits[digit][3]);
  setSegment(SEGMENT_E, digits[digit][4]);
  setSegment(SEGMENT_F, digits[digit][5]);
  setSegment(SEGMENT_G, digits[digit][6]);
}