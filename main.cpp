#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum Cases_of_solution
{
    NONE_SOLUTIONS     = -2,
    CASE_ONE_SOLUTION  = -1,
    NO_SPECIAL_CASES   =  0,
    INFINITY_SOLUTIONS =  1
};

struct Discriminant_and_imagine_units{
    float discriminant;
    bool is_complex;
    //int is_equation_quadratic;
    //int special_case;/*1 - there is infinity of solutions, -1 - there is no solutions, 0 - no special cases(1 or 2 solutions)*/
};

struct Complex_number{
    float real_part;
    float complex_part;
};

struct Solution {
    Complex_number first_solution;
    Complex_number second_solution;
    Cases_of_solution special_cases;
};



int check_type(float coefficient_a, float coefficient_b, float coefficient_c);
void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solution *);/*Find solutions*/
void print_solutions(struct Solution *);/*print the solutions*/
void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *, struct Solution *);
void linear_equation(float coefficient_b, float coefficient_c, struct Solution *);
void special_cases(int type, struct Solution *);
bool comparison(float a, float b);

int main(){
    float coefficient_a = 0.0f;
    float coefficient_b = 0.0f;
    float coefficient_c = 0.0f;
    enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);
    struct Solution solutions = {0};/*list of solutions*/
    find_solutions(coefficient_a, coefficient_b, coefficient_c, &solutions);
    print_solutions(&solutions);
    return 0;
}

int check_type(float coefficient_a, float coefficient_b, float coefficient_c){
    int result = 0;
    if (!comparison(coefficient_a, 0.0f)){
        result = NO_SPECIAL_CASES;
    } else {
        if (!comparison(coefficient_b, 0.0f)){
            result = CASE_ONE_SOLUTION;
        } else {
            if (!comparison(coefficient_c, 0.0f)){
                result = NONE_SOLUTIONS;
            } else {
                result = INFINITY_SOLUTIONS;
            }
        }
    }
    return result;
}

bool comparison(float a, float b){
    float eps = 0.000001f;
    if (fabs(a - b) < eps){
        return true;
    } else {
        return false;
    }
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
    if (solutions->special_cases == NO_SPECIAL_CASES){
        if (!comparison(solutions->first_solution.complex_part, 0.0f)){
            printf("Уравнение имеет два комплексных решения:\n");
            printf("x1 = %.8f + %.8fi\n", solutions->first_solution.real_part, solutions->first_solution.complex_part);
            printf("x2 = %.8f - %.8fi\n", solutions->second_solution.real_part, solutions->second_solution.complex_part);
        } else {
            printf("Уравнение имеет два действительных решения:\n");
            printf("x1 = %.8f\nx2 = %.8f\n", solutions->first_solution.real_part, solutions->second_solution.real_part);
        }
    }else if (solutions->special_cases == CASE_ONE_SOLUTION){
        printf("Уравнение имеет единственное действительное решение:\n");
        printf("x = %.8f\n", solutions->first_solution.real_part);
    } else if (solutions->special_cases == NONE_SOLUTIONS){
        printf("Данное уравнение не имеет решений!\n");
    } else {
        printf("Данное уравнение имеет бесконечно много решений!\n");
    }
}

void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *element){
    if (comparison(coefficient_a, 0.0f)){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        float discriminant2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;
        if (discriminant2 > 0 || comparison(discriminant2, 0.0f)){
            element->discriminant = sqrtf(discriminant2);
            element->is_complex = false;
        } else {
            element->discriminant = sqrtf(-discriminant2);
            element->is_complex = true;
        }
    }
}

void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solution *solutions){
    int type = 0;
    type = check_type(coefficient_a, coefficient_b, coefficient_c);
    if (type == NO_SPECIAL_CASES){
        struct Discriminant_and_imagine_units element = {0};
        find_discriminant(coefficient_b, coefficient_c, coefficient_a, &element);
        quadratic_equation(coefficient_a, coefficient_b, &element, &(*solutions));
    } else if (type == CASE_ONE_SOLUTION){
        linear_equation(coefficient_b, coefficient_c, solutions);
    } else {
        special_cases(type, solutions);
    }
}

void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *element, struct Solution *solutions){
    if (comparison(coefficient_a, 0.0f)){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        solutions->special_cases = NO_SPECIAL_CASES;
        if (element->is_complex){/*Complex solutions*/
            solutions->first_solution.real_part = (-coefficient_b / (2 * coefficient_a));
            solutions->first_solution.complex_part = (element->discriminant / (2 * coefficient_a));
            solutions->second_solution.real_part = (-coefficient_b / (2 * coefficient_a));
            solutions->second_solution.complex_part = (element->discriminant / (2 * coefficient_a));
        } else {/*Real Solutions*/
            if (comparison(element->discriminant, 0.0f)){
                float x = (-coefficient_b) / (2 * coefficient_a);
                solutions->first_solution.real_part = x;
                solutions->first_solution.complex_part = 0;
                solutions->special_cases = CASE_ONE_SOLUTION;
            } else {
                float x1 = 0.0f, x2 = 0.0f;
                x1 = (-coefficient_b + element->discriminant) / (2 * coefficient_a);
                x2 = (-coefficient_b - element->discriminant) / (2 * coefficient_a);
                solutions->first_solution.real_part = x1;
                solutions->first_solution.complex_part = 0;
                solutions->second_solution.real_part = x2;
                solutions->second_solution.complex_part = 0;
            }
        }
    }
}

void linear_equation(float coefficient_b, float coefficient_c, struct Solution *solutions){
    if (comparison(coefficient_b, 0.0f)){
        printf("Error: Данное уравнение не является линейным!\n");
    } else {
        solutions->first_solution.real_part = (!comparison(coefficient_c,0)) ? ((-coefficient_c) / coefficient_b) : 0;
        solutions->first_solution.complex_part = 0;
        solutions->special_cases = CASE_ONE_SOLUTION;
    }
}

void special_cases(int type, struct Solution *solutions){
    if (type == NONE_SOLUTIONS){
        solutions->special_cases = NONE_SOLUTIONS;
    } else {
        solutions->special_cases = INFINITY_SOLUTIONS;
    }
}



