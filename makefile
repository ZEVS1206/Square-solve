CC=g++
CFLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
SOURCE_DIR = source
BUILD_DIR = build
OBJECTS=$(wildcard *.o)
SOURCES=$(wildcard *.cpp)

# wildcart patsubst

all: $(SOURCE_DIR) comp built square_solve

$(SOURCE_DIR): $(SORCE_DIR)
	mkdir $(SOURCE_DIR)
	mv $(SOURCES) $(SOURCE_DIR)
comp:
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.cpp $(SOURCE_DIR)/auxiliary_functionality.cpp -c

#main.o:
#	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.cpp -c


#auxiliary_functionality.o:
#	$(CC) $(CFLAGS) $(SOURCE_DIR)/auxiliary_functionality.cpp -c


built:
	mkdir $(BUILD_DIR)
	mv $(OBJECTS) $(BUILD_DIR)

square_solve:
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/auxiliary_functionality.o -o square_solve
	mv square_solve.exe $(BUILD_DIR)


#Headers: main.cpp auxiliary_functionality.cpp
#	$(CC) $(CFLAGS) -c main.cpp auxiliary_functionality.cpp

clean:
	rm -rf $(BUILD_DIR) *.o $(BUILD_DIR)/*.o $(BUILD_DIR)/square_solve.exe


run:
	$(BUILD_DIR)/square_solve.exe


