#lepiej tego nie modyfikowac
CCFLAGS=-g -mcpu=arm9 -Os -Wall
#LDFLAGS+=-nostartfiles -Wl,--cref -lc -lgcc -T /opt/arm_user/elf32-littlearm.lds -g -Ttext 0x20000000 -Tdata 0x300000 -n
# narzedzia w /opt/arm_user
LDFLAGS+=-nostartfiles -Wl -lc -lgcc -T /opt/arm_user/elf32-littlearm.lds -g -Ttext 0x20000000 -Tdata 0x300000 -n
OBJS=/opt/arm_user/include/cstartup.o /opt/arm_user/include/lowlevel.o PIT_Timer.o GDBU_driver.o
#koniec, dalej mozna dowolnie zmieniac

PROGRAM_NAME=main.elf
OBJ = main.o GDBU_driver.o PIT_Timer.o

all: $(PROGRAM_NAME)

rebuild: clean $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJ) 
	arm-elf-gcc $(LDFLAGS) $(OBJS) $< -o $@

main.o: main.c 
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

PIT_Timer.o: PIT_Timer.c 
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

GDBU_driver.o: GDBU_driver.c 
	arm-elf-gcc -c $(CCFLAGS) $< -o $@

clean:
	rm -f *.o *.elf 
