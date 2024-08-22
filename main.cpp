#include <TXLib.h>
#include <stdio.h>
#include "Headers.h"

int main(){

    #if defined(TEST)
        test_programm();
    #elif defined(USUAL)
        float coefficient_a = 0.0f;
        float coefficient_b = 0.0f;
        float coefficient_c = 0.0f;
        enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);
        struct Solutions solutions = {0};
        find_solutions(coefficient_a, coefficient_b, coefficient_c, &solutions);
        print_solutions(&solutions);
    #else
        printfRed("Оно работает!\n");
        printfGreen("Ура!");
    #endif
    return 0;
}
