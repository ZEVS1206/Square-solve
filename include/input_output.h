#ifndef input_h
#define input_h
#include "Colours.h"
#include "Solver.h"

enum Type
{
    TEST_COEFFICIENTS = 0,
    USER_COEFFICIENTS = 1,
    ERROR_OF_INPUT    = 2,
};

void enter_coefficients(struct Coefficients *);/*enter the values*/
void print_solutions(const struct Solutions *);/*print the solutions*/
void special_input(int argc, char *argv[]);

enum Case_of_input
{
    NO_PROBLEMS         = 0,
    INCORRECT_INPUT     = 1,
    PROBLEM_OF_OVERFLOW = 2,
    PROBLEM_OF_NO_INPUT = 3
};


#endif
