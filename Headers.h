#ifndef Headers
#define Headers
//#define TEST
#define USUAL
#include "Colours.h"

void test_programm(void);
void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);/*Find solutions*/
void print_solutions(const struct Solutions *);/*print the solutions*/

struct Complex_number {
    float real_part;
    float complex_part;
};

// printfRed, printfGreen
//define FUNC(...) __VA_ARGS__
enum Case_of_solution
{
    NONE_SOLUTIONS             = -2,
    CASE_ONE_SOLUTION          = -1,
    CASE_TWO_SOLUTIONS_REAL    =  0,
    CASE_TWO_SOLUTIONS_COMPLEX =  1,
    INFINITY_SOLUTIONS         =  2
};

struct Solutions {
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};
#endif



