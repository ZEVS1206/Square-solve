#include <TXLib.h>
#include <stdio.h>
#include "Solver.h"
#include "Input_output.h"
#include "Test.h"

int main(int argc, char *argv[]){
    if (argc == 1){
        test_programm();
    } else {
        special_input(argc, argv);
    }
    return 0;
}
