#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


void discriminant(float b, float c, float a, float D[]);/*discriminant*/
void decisions(float a, float b, float D[]);/*Finding solutions*/

int main(){
    float a, b, c;
    printf("Введите коэффициент a:");
    scanf("%f", &a);
    printf("\n");
    printf("Введите коэффициент b:");
    scanf("%f", &b);
    printf("\n");
    printf("Введите коэффициент c:");
    scanf("%f", &c);
    printf("\n");
    float D[2] = {0, 0};
    discriminant(b, c, a, D);/*discriminant*/
    decisions(a, b, D);
    return 0;
}

void discriminant(float b, float c, float a, float D[]){
    float discr2 = b * b - 4 * a * c;/*D**2*/
    /*D[0] - discriminant, D[1] - count of imaginary units*/
    if (discr2 >= 0){/*There are real solutions*/
        D[0] = sqrt(discr2);
        D[1] = 0;
    } else {/*There are complex solutions*/
        discr2 = -discr2;
        D[0] = sqrt(discr2);
        D[1] = 1;
    }
}

void decisions(float a, float b, float Discr[]){
    if (Discr[1] > 0){/*Complex solutions*/
        printf("Уравнение имеет два комплексных решения:\n");
        printf("x1 = (%.8f + %.8fi) / %.8f\n", -b, Discr[0], 2 * a);
        printf("x2 = (%.8f - %.8fi) / %.8f\n", -b, Discr[0], 2 * a);
    } else {/*Real Solutions*/
        if (Discr[0] == 0){
            printf("Уравнение имеет единственное действительное решение:\n");
            float x = (-b) / (2 * a);
            printf("x = %.8f\n", x);
        } else {
            printf("Уравнение имеет два действительных решения:\n");
            float x1, x2;
            x1 = (-b + Discr[0]) / (2 * a);
            x2 = (-b - Discr[0]) / (2 * a);
            printf("x1 = %.8f\nx2 = %.8f\n", x1, x2);
        }
    }
}


