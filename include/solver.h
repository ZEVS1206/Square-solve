#ifndef solver_h
#define solver_h
//#define TEST
#define USUAL

void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);/*Find solutions*/
int comparison(float a, float b);

struct Complex_number {
    float real_part;
    float complex_part;
};

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

struct Discriminant_and_imagine_units {
    float discriminant;
    bool is_complex;
};
#endif
