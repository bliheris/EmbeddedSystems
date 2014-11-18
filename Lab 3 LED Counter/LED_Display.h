#define BIT(x) (1 << (x))
#define SETBIT(P, B) (P) |= BIT(B)

#define LEFT 28
#define RIGHT 30

#define SEGMENT_A 25
#define SEGMENT_B 24
#define SEGMENT_C 22
#define SEGMENT_D 21
#define SEGMENT_E 20
#define SEGMENT_F 27
#define SEGMENT_G 26

#define ON 1
#define OFF 0

void intializeLEDdisplay();
void displayDigit(int digit);

void turnOnLeftCounter();
void turnOffLeftCounter();

void turnOnRightCounter();
void turnOffRightCounter();