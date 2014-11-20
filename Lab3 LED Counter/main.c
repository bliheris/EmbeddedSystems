#include "PIT_Timer.h"
#include "LED_Display.h"

void dbgu_print_ascii(const char *a) {}
void showNumber(int number);

int main()
{
  initializeTimer();
  intializeLEDdisplay();
  
  while(1){
    int c = 0;
    while(c < 100){
      showNumber(c);
      c++;
    }
  }
}

void showNumber(int number){
  int waitTime = 500;
  int smallWait = 10;
  int waitCounter = waitTime/(2*smallWait);

  if(number < 10){
    turnOffLeftCounter();
    turnOnRightCounter();
    displayDigit(number);
    timerWait(waitTime);
  }else{
    int tensDigit = number/10;
    int unitsDigit = number % 10;
    int temp = waitCounter;
    while(temp--){
      turnOnLeftCounter();
      turnOffRightCounter();
      displayDigit(tensDigit);
      timerWait(smallWait);

      turnOffLeftCounter();
      turnOnRightCounter();
      displayDigit(unitsDigit);
      timerWait(smallWait);
    }
  }
}
