#include <TXLib.h>
#include <stdio.h>
#include "Solver.h"
#include "Input_output.h"
#include "Test.h"

int main(){

    #if defined(TEST)
        test_programm();
    #elif defined(USUAL)
        struct Coefficients coefficients = {0};
        enter_coefficients(&coefficients);
        struct Solutions solutions = {0};
        find_solutions(&coefficients, &solutions);
        print_solutions(&solutions);
    #else
        printfRed("It's working, yees!\n");
        printfGreen("Lets go!");
    #endif
    return 0;
}
