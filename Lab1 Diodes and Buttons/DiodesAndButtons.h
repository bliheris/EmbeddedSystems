#define BIT(x) (1 << (x))
#define SETBIT(P, B) (P) |= BIT(B)
#define DS1 8
#define DS2 29
#define BP1 5
#define BP2 4

void initializeDiode1();
void turnOnDiode1();
void turnOffDiode1();

void initializeDiode2();
void turnOnDiode2();
void turnOffDiode2();

void configureButtons();
int button1IsPressed();
int button2IsPressed();