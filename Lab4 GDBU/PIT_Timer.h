#define BIT(x) (1 << (x))
#define SETBIT(P, B) (P) |= BIT(B)

#define PIT_MR  (unsigned int*)  0xFFFFFD30
#define PIT_SR  (unsigned int*)  0xFFFFFD34
#define PIT_PIVR (unsigned int*) 0xFFFFFD38

void clearPIST();
void initializeTimer();
void timerWait(int miliseconds);