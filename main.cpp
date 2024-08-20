#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum Case_of_solution
{
    NONE_SOLUTIONS     = -2,
    CASE_ONE_SOLUTION  = -1,
    CASE_TWO_SOLUTIONS =  0,
    INFINITY_SOLUTIONS =  1
};

struct Discriminant_and_imagine_units{
    float discriminant;
    bool is_complex;
};

struct Complex_number{
    float real_part;
    float complex_part;
};

struct Solutions {
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};



//int check_type(float coefficient_a, float coefficient_b, float coefficient_c);
void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);/*Find solutions*/
void print_solutions(struct Solutions *);/*print the solutions*/
void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *, struct Solutions *);
void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *);
void special_cases(float coefficient_c, struct Solutions *);
int comparison(float a, float b);

int main(){
    float coefficient_a = 0.0f;
    float coefficient_b = 0.0f;
    float coefficient_c = 0.0f;
    enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

    struct Solutions solutions = {0};
    find_solutions(coefficient_a, coefficient_b, coefficient_c, &solutions);

    print_solutions(&solutions);
    return 0;
}

/*int check_type(float coefficient_a, float coefficient_b, float coefficient_c){
    int result = 0;
    if (comparison(coefficient_a, 0.0f) != 0){
        result = CASE_TWO_SOLUTIONS;
    } else {
        if (comparison(coefficient_b, 0.0f) != 0){
            result = CASE_ONE_SOLUTION;
        } else {
            if (comparison(coefficient_c, 0.0f) != 0){
                result = NONE_SOLUTIONS;
            } else {
                result = INFINITY_SOLUTIONS;
            }
        }
    }
    return result;
}*/

int comparison(float a, float b){
    float eps = 0.000001f;
    if (b > a + eps){
        return -1;
    } else if (b <= (a + eps) && b >= (a - eps)){
        return 0;
    } else {
        return 1;
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

void print_solutions(struct Solutions *solutions){
    if (solutions->special_cases == CASE_TWO_SOLUTIONS){
        if (comparison(solutions->first_solution.complex_part, 0.0f) != 0){
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
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        float discriminant2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;
        if (comparison(discriminant2, 0.0f) > 0 || comparison(discriminant2, 0.0f) == 0){
            element->discriminant = sqrtf(discriminant2);
            element->is_complex = false;
        } else {
            element->discriminant = sqrtf(-discriminant2);
            element->is_complex = true;
        }
    }
}

void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *solutions){
    /*int type = 0;
    type = check_type(coefficient_a, coefficient_b, coefficient_c);*/

    if (comparison(coefficient_a, 0.0f) != 0){
        struct Discriminant_and_imagine_units element = {0};
        find_discriminant(coefficient_b, coefficient_c, coefficient_a, &element);
        quadratic_equation(coefficient_a, coefficient_b, &element, solutions);
    }
    else if (comparison(coefficient_b, 0.0f) != 0){
        linear_equation(coefficient_b, coefficient_c, solutions);
    }
    else {
        special_cases(coefficient_c, solutions);
    }
}

void quadratic_equation(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *element, struct Solutions *solutions){
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
    } else {
        solutions->special_cases = CASE_TWO_SOLUTIONS;
        if (element->is_complex){/*Complex solutions*/
            solutions->first_solution.real_part = (-coefficient_b / (2 * coefficient_a));
            solutions->first_solution.complex_part = (element->discriminant / (2 * coefficient_a));
            solutions->second_solution.real_part = (-coefficient_b / (2 * coefficient_a));
            solutions->second_solution.complex_part = (element->discriminant / (2 * coefficient_a));
        } else {/*Real Solutions*/
            if (comparison(element->discriminant, 0.0f) == 0){
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

void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *solutions){
    if (comparison(coefficient_b, 0.0f) == 0){
        printf("Error: Данное уравнение не является линейным!\n");
    } else {
        solutions->first_solution.real_part = (comparison(coefficient_c, 0) != 0) ? ((-coefficient_c) / coefficient_b) : 0;
        solutions->first_solution.complex_part = 0;
        solutions->special_cases = CASE_ONE_SOLUTION;
    }
}

void special_cases(float coefficient_c, struct Solutions *solutions){
    if (comparison(coefficient_c, 0.0f) != 0){
        solutions->special_cases = NONE_SOLUTIONS;
    } else {
        solutions->special_cases = INFINITY_SOLUTIONS;
    }
}



