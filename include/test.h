#ifndef test_h
#define test_h
#include "solver.h"
#include "input_output.h"

void test_programm(void);

struct Test_solutions {
    float coefficient_a;
    float coefficient_b;
    float coefficient_c;
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};

#endif
