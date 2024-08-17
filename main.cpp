#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


enum cases {NONE_SOLUTIONS=-2, CASE_ONE_SOLUTION=-1, NO_SPECIAL_CASES=0, INFINITY_SOLUTIONS=1};

struct Discriminant_and_imagine_units{
    float discriminant;
    int count_of_iu;
    //int is_equation_quadratic;
    //int special_case;/*1 - there is infinity of solutions, -1 - there is no solutions, 0 - no special cases(1 or 2 solutions)*/
};

struct Solution {
    float real_part;
    int imagine_unit;
    float complex_part;
    int is_solution;/*0 - it is not a solution, 1 - it is a solution*/
    int special_case;/*1 - there is infinity of solutions, -1 - there is no solutions, 0 - no special cases(1 or 2 solutions)*/
};



int check_type(float coefficient_a, float coefficient_b, float coefficient_c);
void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, int type, struct Solution *);/*Find solutions*/
void print_solutions(struct Solution *);/*print the solutions*/
void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *, struct Solution *);
void linear_equation(float coefficient_b, float coefficient_c, struct Solution *);
void special_cases(int type, struct Solution *);

int main(){
    float coefficient_a = 0.0f, coefficient_b = 0.0f, coefficient_c = 0.0f;
    enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);
    int type = 0;
    type = check_type(coefficient_a, coefficient_b, coefficient_c);
    struct Solution solutions[2] = {0};/*list of solutions*/
    find_solutions(coefficient_a, coefficient_b, coefficient_c, type, solutions);
    print_solutions(solutions);
    return 0;
}

int check_type(float coefficient_a, float coefficient_b, float coefficient_c){
    int result = 0;
    if (coefficient_a != 0){
        result = NO_SPECIAL_CASES;
    } else {
        if (coefficient_b != 0){
            result = CASE_ONE_SOLUTION;
        } else {
            if (coefficient_c != 0){
                result = NONE_SOLUTIONS;
            } else {
                result = INFINITY_SOLUTIONS;
            }
        }
    }
    return result;
}


void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c){
    printf("Введите коэффициент a:");
    scanf("%f", &(*coefficient_a));
    printf("\n");
    printf("Введите коэффициент b:");
    scanf("%f", &(*coefficient_b));
    printf("\n");
    printf("Введите коэффициент c:");
    scanf("%f", &(*coefficient_c));
    printf("\n");
}

void print_solutions(struct Solution *solutions){
    if (solutions[0].special_case == NO_SPECIAL_CASES){
        if (solutions[0].imagine_unit == 1){
            printf("Уравнение имеет два комплексных решения:\n");
            printf("x1 = %.8f + %.8fi\n", solutions[0].real_part, solutions[0].complex_part);
            printf("x2 = %.8f - %.8fi\n", solutions[1].real_part, solutions[1].complex_part);
        } else {
            if (solutions[1].is_solution == 0){
                printf("Уравнение имеет единственное действительное решение:\n");
                printf("x = %.8f\n", solutions[0].real_part);
            } else {
                printf("Уравнение имеет два действительных решения:\n");
                printf("x1 = %.8f\nx2 = %.8f\n", solutions[0].real_part, solutions[1].real_part);
            }
        }
    } else if (solutions[0].special_case == NONE_SOLUTIONS){
        printf("Данное уравнение не имеет решений!\n");
    } else {
        printf("Данное уравнение имеет бесконечно много решений!\n");
    }
}

void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *element){
    if (coefficient_a == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        float discriminant2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;
        if (discriminant2 >= 0){
            element->discriminant = sqrt(discriminant2);
            element->count_of_iu = 0;
        } else {
            element->discriminant = sqrt(-discriminant2);
            element->count_of_iu = 1;
        }
    }
}

void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, int type, struct Solution *solutions){
    if (type == NO_SPECIAL_CASES){
        struct Discriminant_and_imagine_units element = {0};
        find_discriminant(coefficient_b, coefficient_c, coefficient_a, &element);
        quadratic_equation(coefficient_a, coefficient_b, &element, solutions);
    } else if (type == CASE_ONE_SOLUTION){
        linear_equation(coefficient_b, coefficient_c, solutions);
    } else {
        special_cases(type, solutions);
    }
}

void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *element, struct Solution *solutions){
    if (coefficient_a == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        if (element->count_of_iu > 0){/*Complex solutions*/
            solutions[0].imagine_unit = 1;
            solutions[0].real_part = (-coefficient_b / (2 * coefficient_a));
            solutions[0].complex_part = (element->discriminant / (2 * coefficient_a));
            solutions[0].is_solution = 1;
            solutions[1].imagine_unit = 1;
            solutions[1].real_part = (-coefficient_b / (2 * coefficient_a));
            solutions[1].complex_part = (element->discriminant / (2 * coefficient_a));
            solutions[1].is_solution = 1;
        } else {/*Real Solutions*/
            if (element->discriminant == 0){
                float x = (-coefficient_b) / (2 * coefficient_a);
                solutions[0].imagine_unit = 0;
                solutions[0].real_part = x;
                solutions[0].complex_part = 0;
                solutions[0].is_solution = 1;
                solutions[1].is_solution = 0;
            } else {
                float x1 = 0.0f, x2 = 0.0f;
                x1 = (-coefficient_b + element->discriminant) / (2 * coefficient_a);
                x2 = (-coefficient_b - element->discriminant) / (2 * coefficient_a);
                solutions[0].imagine_unit = 0;
                solutions[0].real_part = x1;
                solutions[0].complex_part = 0;
                solutions[0].is_solution = 1;
                solutions[1].imagine_unit = 0;
                solutions[1].real_part = x2;
                solutions[1].complex_part = 0;
                solutions[1].is_solution = 1;
            }
        }
    }
}

void linear_equation(float coefficient_b, float coefficient_c, struct Solution *solutions){
    if (coefficient_b == 0){
        printf("Error: Данное уравнение не является линейным!\n");
    } else {
        solutions[0].imagine_unit = 0;
        solutions[0].real_part = (-coefficient_c) / coefficient_b;
        solutions[0].complex_part = 0;
        solutions[0].is_solution = 1;
        solutions[1].is_solution = 0;
    }
}

void special_cases(int type, struct Solution *solutions){
    if (type == NONE_SOLUTIONS){
        solutions[0].special_case = NONE_SOLUTIONS;
        solutions[0].is_solution = 1;
        solutions[1].is_solution = 0;
    } else {
        solutions[0].special_case = INFINITY_SOLUTIONS;
        solutions[0].is_solution = 1;
        solutions[1].is_solution = 0;
    }
}



