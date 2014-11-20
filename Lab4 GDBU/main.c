#include "GDBU_driver.h"
#include "PIT_Timer.h"

#define ALPHABET_MODE
#define CAPITALIZE_OFFSET -32

void dbgu_print_ascii(const char *buffer){}
void sendAlphabet();
void capitalizeEcho();

int main(){
  configureDBGU();
  initializeTimer();

  DBGU_sendString((char*)"Welcome to DBGU have fun and good luck!\r\n");
  while(1){
  #ifdef ALPHABET_MODE
    sendAlphabet();
  #else
    capitalizeEcho();
  #endif
  }
}

void sendAlphabet(){
  int letter = 'a';
  while(letter <= 'z'){
    DBGU_sendChar((char)letter);
    letter++;
    timerWait(100);
  }
  DBGU_sendString((char*)"\r\n");
}

void capitalizeEcho(){
  char letter = DBGU_readChar();
  letter += CAPITALIZE_OFFSET;
  DBGU_sendChar(letter);  
}

