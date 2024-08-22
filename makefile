CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
OBJECTS=main.o auxiliary_functionality.o

all: square_solve

square_solve: $(OBJECTS)
	$(CC) $(OBJECTS) -o square_solve
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -c
auxiliary_functionality.o: auxiliary_functionality.cpp
	$(CC) $(CFLAGS) auxiliary_functionality.cpp -c
clean:
	rm -rf *.o square_solve
run: 
	square_solve.exe