#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


struct Discriminant_and_imagine_units{
    float discriminant;
    int count_of_iu;
    int is_square_state;
    int special_case;/*1 - there is infinity of solutions, -1 - there is no solutions, 0 - no special cases(1 or 2 solutions)*/
};

struct Solution {
    float real_part;
    int imagine_unit;
    float complex_part;
    int is_solution;/*0 - it is not a solution, 1 - it is a solution*/
    int special_case;/*1 - there is infinity of solutions, -1 - there is no solutions, 0 - no special cases(1 or 2 solutions)*/
};

void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void find_solutions(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *, struct Solution *);/*Find solutions*/
void print_solutions(struct Solution *);/*print the solutions*/

int main(){
    float coefficient_a = 0.0f, coefficient_b = 0.0f, coefficient_c = 0.0f;
    enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);
    struct Discriminant_and_imagine_units element = {0};// = (struct Discriminant_and_imagine_units *) malloc(sizeof(struct Discriminant_and_imagine_units));
    find_discriminant(coefficient_b, coefficient_c, coefficient_a, &element);/*discriminant*/
    struct Solution decisions[2] = {0};/*list of solutions*/
    find_solutions(coefficient_a, coefficient_b, &element, decisions);
    print_solutions(decisions);
    return 0;
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

void print_solutions(struct Solution *decisions){
    if (decisions[0].special_case == 0){
        if (decisions[0].imagine_unit == 1){
            printf("Уравнение имеет два комплексных решения:\n");
            printf("x1 = %.8f + %.8fi\n", decisions[0].real_part, decisions[0].complex_part);
            printf("x2 = %.8f - %.8fi\n", decisions[1].real_part, decisions[1].complex_part);
        } else {
            if (decisions[1].is_solution == 0){
                printf("Уравнение имеет единственное действительное решение:\n");
                printf("x = %.8f\n", decisions[0].real_part);
            } else {
                printf("Уравнение имеет два действительных решения:\n");
                printf("x1 = %.8f\nx2 = %.8f\n", decisions[0].real_part, decisions[1].real_part);
            }
        }
    } else if (decisions[0].special_case == -1){
        printf("Данное уравнение не имеет решений!\n");
    } else {
        printf("Данное уравнение имеет бесконечно много решений!\n");
    }
}

void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *element){
    if (coefficient_a != 0){
        element->is_square_state = 1;
        float discr2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;/*Discriminant**2*/
        /*D[0] - discriminant, D[1] - count of imaginary units*/
        if (discr2 >= 0){/*There are real solutions*/
            element->discriminant = sqrt(discr2);
            element->count_of_iu = 0;
        } else {/*There are complex solutions*/
            discr2 = -discr2;
            element->discriminant = sqrt(discr2);
            element->count_of_iu = 1;
        }
    } else if (coefficient_b != 0){
        float solution = (-coefficient_c / coefficient_b);
        element->is_square_state = 0;
        element->discriminant = solution;
        element->count_of_iu = 0;
    } else {
        if (coefficient_c != 0){
           element->is_square_state = 0;
           element->discriminant = 0;
           element->count_of_iu = 0;
           element->special_case = -1;/*no solutions*/
        } else {
           element->is_square_state = 0;
           element->discriminant = 0;
           element->count_of_iu = 0;
           element->special_case = 1;/*infinity of solutions*/
        }
    }
}

void find_solutions(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *element, struct Solution *decisions){
    if (element->is_square_state == 1){
        if (element->count_of_iu > 0){/*Complex solutions*/
            decisions[0].imagine_unit = 1;
            decisions[0].real_part = (-coefficient_b / (2 * coefficient_a));
            decisions[0].complex_part = (element->discriminant / (2 * coefficient_a));
            decisions[0].is_solution = 1;
            decisions[1].imagine_unit = 1;
            decisions[1].real_part = (-coefficient_b / (2 * coefficient_a));
            decisions[1].complex_part = (element->discriminant / (2 * coefficient_a));
            decisions[1].is_solution = 1;
        } else {/*Real Solutions*/
            if (element->discriminant == 0){
                float x = (-coefficient_b) / (2 * coefficient_a);
                decisions[0].imagine_unit = 0;
                decisions[0].real_part = x;
                decisions[0].complex_part = 0;
                decisions[0].is_solution = 1;
                decisions[1].is_solution = 0;
            } else {
                float x1 = 0.0f, x2 = 0.0f;
                x1 = (-coefficient_b + element->discriminant) / (2 * coefficient_a);
                x2 = (-coefficient_b - element->discriminant) / (2 * coefficient_a);
                decisions[0].imagine_unit = 0;
                decisions[0].real_part = x1;
                decisions[0].complex_part = 0;
                decisions[0].is_solution = 1;
                decisions[1].imagine_unit = 0;
                decisions[1].real_part = x2;
                decisions[1].complex_part = 0;
                decisions[1].is_solution = 1;
            }

        }
    } else {
        if (element->special_case == 0){
            decisions[0].imagine_unit = 0;
            decisions[0].real_part = element->discriminant;
            decisions[0].complex_part = 0;
            decisions[0].is_solution = 1;
            decisions[1].is_solution = 0;
        } else if (element->special_case == 1){
            decisions[0].special_case = 1;
            decisions[0].is_solution = 1;
            decisions[1].is_solution = 0;
        } else {
            decisions[0].special_case = -1;
            decisions[0].is_solution = 1;
            decisions[1].is_solution = 0;
        }
    }
}
