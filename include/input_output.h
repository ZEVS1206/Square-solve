#ifndef input_h
#define input_h
#include "Colours.h"
#include "Solver.h"

void enter_coefficients(struct Coefficients *);/*enter the values*/
void print_solutions(const struct Solutions *);/*print the solutions*/

enum Case_of_input
{
    NO_PROBLEMS         = 0,
    INCORRECT_INPUT     = 1,
    PROBLEM_OF_OVERFLOW = 2,
    PROBLEM_OF_NO_INPUT = 3
};



#endif
