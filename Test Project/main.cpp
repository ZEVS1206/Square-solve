#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <TXLib.h>


float Dis(float *b, float *c, float *a);/*������������*/
void solve(float *a, float *b, float *c);/*����� ����� �������*/
int cnt_i = 0;/*���������� ������ ������*/

int main(){
    float a, b, c;
    printf("������� ����������� a:");
    scanf("%f", &a);
    printf("\n");
    printf("������� ����������� b:");
    scanf("%f", &b);
    printf("\n");
    printf("������� ����������� c:");
    scanf("%f", &c);
    printf("\n");
    float D = Dis(&b, &c, &a);/*������������*/
    solve(&a, &b, &D);
    return 0;
}

float Dis(float *b, float *c, float *a){
    float D2 = (*b) * (*b) - 4 * (*a) * (*c);/*D**2*/
    if (D2 >= 0){/*���� �������������� �����*/
        cnt_i = 0;
        return sqrt(D2);
    } else {/*���� ����������� �����*/
        D2 = -D2;
        cnt_i = 1;
        return sqrt(D2);
    }
}

void solve(float *a, float *b, float *D){
    if (cnt_i > 0){/*����������� �����*/
        printf("��������� ����� ��� ����������� �������:\n");
        printf("x1 = (%.8f + %.8fi) / %.8f\n", -(*b), *D, 2 * (*a));
        printf("x2 = (%.8f - %.8fi) / %.8f\n", -(*b), *D, 2 * (*a));
    } else {/*�������������� �����*/
        if (*D == 0){
            printf("��������� ����� ������������ �������������� �������:\n");
            float x = (-(*b)) / (2 * (*a));
            printf("x = %.8f\n", x);
        } else {
            printf("��������� ����� ��� �������������� �������:\n");
            float x1, x2;
            x1 = (-(*b) + *D) / (2 * (*a));
            x2 = (-(*b) - *D) / (2 * (*a));
            printf("x1 = %.8f\nx2 = %.8f\n", x1, x2);
        }
    }
}


