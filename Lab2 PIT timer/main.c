#include "DiodesAndButtons.h"
#include "PIT_Timer.h"

void dbgu_print_ascii(const char *a) {}

int main()
{
  initializeDiode1();
  
  while(1){
    turnOnDiode1();
    timerWait(500);
    turnOffDiode1();
    timerWait(500);
  }
}

