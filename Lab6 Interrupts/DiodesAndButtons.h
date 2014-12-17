#define BIT(x) (1 << (x))
#define SETBIT(P, B) (P) = BIT(B)
#define SETVALUE(P, V) (P) = V

void initializeDiode1();
void turnOnDiode1();
void turnOffDiode1();

void initializeDiode2();
void turnOnDiode2();
void turnOffDiode2();

void configureButtonsWithInterrupts(unsigned int handler);
