/**
    \file
    \brief
    programm for solve equation
*/


#include "Solver.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


static void find_discriminant(const struct Coefficients *, struct Discriminant_and_imagine_units *);/*discriminant*/
static void quadratic_equation(const struct Coefficients *, struct Solutions *);
static void find_real_solutions(const struct Coefficients *, float discriminant, struct Solutions *);
static void find_complex_solutions(const struct Coefficients *, float discriminant, struct Solutions *);
static void linear_equation(const struct Coefficients *, struct Solutions *);
static void special_cases(float coefficient_c, struct Solutions *);

int comparison(float a, float b){
    float eps = 1e-6f;
    if (b >= a + eps){
        return -1;
    } else if (b < (a + eps) && b > (a - eps)){
        return 0;
    } else {
        return 1;
    }
}

/**
    \brief Function for finding discriminant

    \param [in] const struct Coefficients - Values of the coefficients a, b, c
    \param [in] struct Discriminant_and_imagine_unit - The place where discriminant and
                                                       complex status will be saved


*/

static void find_discriminant(const struct Coefficients *coefficients, struct Discriminant_and_imagine_units *Discriminant){
    assert(coefficients != NULL);
    assert(Discriminant != NULL);
    if (comparison(coefficients->coefficient_a, 0.0f) == 0){
        printf("Error: It is not the quadratic equation!\n");
        return;
    }
    float discriminant2 = coefficients->coefficient_b * coefficients->coefficient_b - 4 * coefficients->coefficient_a * coefficients->coefficient_c;
    Discriminant->discriminant = sqrtf(fabsf(discriminant2));
    Discriminant->is_complex = comparison(discriminant2, 0.0f) < 0;
}

/**
    \brief Function of finding solutions


    \param [in] struct Coefficients - Values of coefficients a, b, c
    \param [in] struct Solutions - The place where the solutions will be saved
*/

void find_solutions(const struct Coefficients *coefficients, struct Solutions *solutions){
    assert(isfinite(coefficients->coefficient_a));
    assert(isfinite(coefficients->coefficient_b));
    assert(isfinite(coefficients->coefficient_c));
    assert(solutions != NULL);
    assert(coefficients != NULL);

    if (comparison(coefficients->coefficient_a, 0.0f) != 0){
        quadratic_equation(coefficients, solutions);
    }
    else if (comparison(coefficients->coefficient_b, 0.0f) != 0){
        linear_equation(coefficients, solutions);
    }
    else {
        special_cases(coefficients->coefficient_c, solutions);
    }
}

/**
    \brief A function for solving exactly the quadratic equation


    \param [in] struct Coefficients - Values of coefficients a, b, c
    \param [in] struct Solutions - The place where the solutions will be saved

    \warning coefficient_a int struct Coefficients must be != 0

*/

static void quadratic_equation(const struct Coefficients *coefficients, struct Solutions *solutions){
    assert(solutions != NULL);
    assert(coefficients != NULL);

    struct Discriminant_and_imagine_units Discriminant = {0};
    find_discriminant(coefficients, &Discriminant);
    if (comparison(coefficients->coefficient_a, 0.0f) == 0){
        printf("Error: It is not the quadratic equation!\n");
        return;
    }

    if (Discriminant.is_complex){/*Complex solutions*/
        find_complex_solutions(coefficients, Discriminant.discriminant, solutions);
        return;
    }
    find_real_solutions(coefficients, Discriminant.discriminant, solutions);

}

/**
    \brief Function for searching real solutions

    \param [in] const struct Coefficients - Values of coefficients a, b, c
    \param [in] discriminant - the value of the discriminant of equation
    \param [in] struct Solutions - The place where the solutions will be saved

    \warning This function for REAL solutions, so discriminant != 0

*/

static void find_real_solutions(const struct Coefficients *coefficients, float discriminant, struct Solutions *solutions){
    assert(coefficients != NULL);
    assert(solutions != NULL);

    if (comparison(discriminant, 0.0f) == 0){
        float x = ((comparison(coefficients->coefficient_b, 0.0f)) == 0) ? 0 : (-(coefficients->coefficient_b)) / (2 * (coefficients->coefficient_a));
        solutions->first_solution.real_part = x;
        solutions->first_solution.complex_part = 0.0f;
        solutions->second_solution.real_part = 0.0f;
        solutions->second_solution.complex_part = 0.0f;
        solutions->special_cases = CASE_ONE_SOLUTION;
        return;
    }
    solutions->special_cases = CASE_TWO_SOLUTIONS_REAL;
    float x1 = 0.0f;
    float x2 = 0.0f;
    x1 = (-(coefficients->coefficient_b) + discriminant) / (2 * (coefficients->coefficient_a));
    x2 = (-(coefficients->coefficient_b) - discriminant) / (2 * (coefficients->coefficient_a));
    solutions->first_solution.real_part = x1;
    solutions->first_solution.complex_part = 0.0f;
    solutions->second_solution.real_part = x2;
    solutions->second_solution.complex_part = 0.0f;
}

/**
    \brief Function for searching complex solutions

    \param [in] const struct Coefficients - Values of the coefficients a, b, c
    \param [in] discriminant - the value of the discriminant of the equation
    \param [in] struct Solutions - The place where the solutions will be saved

*/

static void find_complex_solutions(const struct Coefficients *coefficients, float discriminant, struct Solutions *solutions){
    assert(coefficients != NULL);
    assert(solutions != NULL);

    solutions->special_cases = CASE_TWO_SOLUTIONS_COMPLEX;
    solutions->first_solution.real_part = (-(coefficients->coefficient_b) / (2 * (coefficients->coefficient_a)));
    solutions->first_solution.complex_part = (discriminant / (2 * (coefficients->coefficient_a)));
    solutions->second_solution.real_part = (-(coefficients->coefficient_b) / (2 * (coefficients->coefficient_a)));
    solutions->second_solution.complex_part = (discriminant / (2 * (coefficients->coefficient_a)));
}

/**
    \brief Function for solving exactly linear equation

    \param [in] const struct Coefficients - Values of the coefficients a, b, c
    \param [in] struct Solutions - The place where the solutions will be saved

*/

static void linear_equation(const struct Coefficients *coefficients, struct Solutions *solutions){
    assert(solutions != NULL);
    assert(coefficients != NULL);

    if (comparison(coefficients->coefficient_b, 0.0f) == 0){
        printf("Error:It is not linear equation!\n");
        return;
    }
    solutions->first_solution.real_part = (comparison(coefficients->coefficient_c, 0.0f) != 0) ? ((-(coefficients->coefficient_c)) / (coefficients->coefficient_b)) : 0;
    solutions->first_solution.complex_part = 0;
    solutions->special_cases = CASE_ONE_SOLUTION;
}

/**
    \brief Function for searching special cases NONE_SOLUTIONS and INFINITY_SOLUTIONS

    \param [in] float coefficient_c - the value of the coefficient c
    \param [in] struct Solutions - The place where the solutions will be saved

*/

static void special_cases(float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);

    if (comparison(coefficient_c, 0.0f) != 0){
        solutions->special_cases = NONE_SOLUTIONS;
    } else {
        solutions->special_cases = INFINITY_SOLUTIONS;
    }
}

