#define MASTERCLOCK 100000000 /* Hz */
#define BAUDRATE 115200
#define SET(P, B) (P) |= (B)

void configureDBGU();

void DBGU_sendChar(char data);
void DBGU_sendString(char* string);

char DBGU_readChar();