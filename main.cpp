#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

struct Discriminant_and_imagine_units{
    float discriminant;
    int count_of_iu;
};

struct Discriminant_and_imagine_units *finding_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void finding_solutions(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *);/*Finding solutions*/

int main(){
    float coefficient_a, coefficient_b, coefficient_c;
    printf("Введите коэффициент a:");
    scanf("%f", &coefficient_a);
    printf("\n");
    printf("Введите коэффициент b:");
    scanf("%f", &coefficient_b);
    printf("\n");
    printf("Введите коэффициент c:");
    scanf("%f", &coefficient_c);
    printf("\n");
    struct Discriminant_and_imagine_units *element;// = (struct Discriminant_and_imagine_units *) malloc(sizeof(struct Discriminant_and_imagine_units));
    element = finding_discriminant(coefficient_b, coefficient_c, coefficient_a, &element);/*discriminant*/
    finding_solutions(coefficient_a, coefficient_b, &element);
    return 0;
}

struct Discriminant_and_imagine_units *finding_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *element){
    float discr2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;/*D**2*/
    /*D[0] - discriminant, D[1] - count of imaginary units*/
    if (discr2 >= 0){/*There are real solutions*/
        element->discriminant = sqrt(discr2);
        element->count_of_iu = 0;
        return element;
    } else {/*There are complex solutions*/
        discr2 = -discr2;
        element->discriminant = sqrt(discr2);
        element->count_of_iu = 1;
        return element;
    }
}

void finding_solutions(float coefficient_a, float coefficient_b, struct Discriminant_and_imagine_units *element){
    if (element->count_of_iu > 0){/*Complex solutions*/
        printf("Уравнение имеет два комплексных решения:\n");
        printf("x1 = (%.8f + %.8fi) / %.8f\n", -coefficient_b, element->discriminant, 2 * coefficient_a);
        printf("x2 = (%.8f - %.8fi) / %.8f\n", -coefficient_b, element->discriminant, 2 * coefficient_a);
    } else {/*Real Solutions*/
        if (element->discriminant == 0){
            printf("Уравнение имеет единственное действительное решение:\n");
            float x = (-coefficient_b) / (2 * coefficient_a);
            printf("x = %.8f\n", x);
        } else {
            printf("Уравнение имеет два действительных решения:\n");
            float x1, x2;
            x1 = (-coefficient_b + element->discriminant) / (2 * coefficient_a);
            x2 = (-coefficient_b - element->discriminant) / (2 * coefficient_a);
            printf("x1 = %.8f\nx2 = %.8f\n", x1, x2);
        }
    }
}


