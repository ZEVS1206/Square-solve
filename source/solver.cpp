#include "solver.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


static void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
static void quadratic_equation(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);
static void find_real_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
static void find_complex_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
static void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *);
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

static void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *Discriminant){
    assert(Discriminant != NULL);
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: It is not the quadratic equation!\n");
        return;
    }
    float discriminant2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;
    Discriminant->discriminant = sqrtf(fabsf(discriminant2));
    Discriminant->is_complex = comparison(discriminant2, 0.0f) < 0;
}

void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *solutions){
    assert(isfinite(coefficient_a));
    assert(isfinite(coefficient_b));
    assert(isfinite(coefficient_c));
    assert(solutions != NULL);

    if (comparison(coefficient_a, 0.0f) != 0){
        quadratic_equation(coefficient_a, coefficient_b, coefficient_c, solutions);
    }
    else if (comparison(coefficient_b, 0.0f) != 0){
        linear_equation(coefficient_b, coefficient_c, solutions);
    }
    else {
        special_cases(coefficient_c, solutions);
    }
}

static void quadratic_equation(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);
    struct Discriminant_and_imagine_units Discriminant = {0};
    find_discriminant(coefficient_b, coefficient_c, coefficient_a, &Discriminant);
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: It is not the quadratic equation!\n");
        return;
    }

    if (Discriminant.is_complex){/*Complex solutions*/
        find_complex_solutions(coefficient_a, coefficient_b, Discriminant.discriminant, solutions);
        return;
    }
    find_real_solutions(coefficient_a, coefficient_b, Discriminant.discriminant, solutions);

}

static void find_real_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *solutions){
    if (comparison(discriminant, 0.0f) == 0){
        float x = ((comparison(coefficient_b, 0.0f)) == 0) ? 0 : (-coefficient_b) / (2 * coefficient_a);
        solutions->first_solution.real_part = x;
        solutions->first_solution.complex_part = 0;
        solutions->second_solution.real_part = 0;
        solutions->second_solution.complex_part = 0;
        solutions->special_cases = CASE_ONE_SOLUTION;
        return;
    }
    solutions->special_cases = CASE_TWO_SOLUTIONS_REAL;
    float x1 = 0.0f;
    float x2 = 0.0f;
    x1 = (-coefficient_b + discriminant) / (2 * coefficient_a);
    x2 = (-coefficient_b - discriminant) / (2 * coefficient_a);
    solutions->first_solution.real_part = x1;
    solutions->first_solution.complex_part = 0;
    solutions->second_solution.real_part = x2;
    solutions->second_solution.complex_part = 0;
}

static void find_complex_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *solutions){
    solutions->special_cases = CASE_TWO_SOLUTIONS_COMPLEX;
    solutions->first_solution.real_part = (-coefficient_b / (2 * coefficient_a));
    solutions->first_solution.complex_part = (discriminant / (2 * coefficient_a));
    solutions->second_solution.real_part = (-coefficient_b / (2 * coefficient_a));
    solutions->second_solution.complex_part = (discriminant / (2 * coefficient_a));
}

static void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);

    if (comparison(coefficient_b, 0.0f) == 0){
        printf("Error:It is not linear equation!\n");
        return;
    }
    solutions->first_solution.real_part = (comparison(coefficient_c, 0.0f) != 0) ? ((-coefficient_c) / coefficient_b) : 0;
    solutions->first_solution.complex_part = 0;
    solutions->special_cases = CASE_ONE_SOLUTION;
}

static void special_cases(float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);

    if (comparison(coefficient_c, 0.0f) != 0){
        solutions->special_cases = NONE_SOLUTIONS;
    } else {
        solutions->special_cases = INFINITY_SOLUTIONS;
    }
}

