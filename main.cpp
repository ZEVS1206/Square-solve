#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum Case_of_solution
{
    NONE_SOLUTIONS             = -2,
    CASE_ONE_SOLUTION          = -1,
    CASE_TWO_SOLUTIONS_REAL    =  0,
    CASE_TWO_SOLUTIONS_COMPLEX =  1,
    INFINITY_SOLUTIONS         =  2
};

struct Discriminant_and_imagine_units {
    float discriminant;
    bool is_complex;
};

struct Complex_number {
    float real_part;
    float complex_part;
};

struct Solutions {
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};

struct Test_solutions {
    float coefficient_a;
    float coefficient_b;
    float coefficient_c;
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};





void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c);/*enter the values*/
int input_check(float *coefficient);
void input(float *coefficient, char position);
void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
void find_solutions(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);/*Find solutions*/
void print_solutions(struct Solutions *);/*print the solutions*/
void quadratic_equation(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);
void find_real_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
void find_complex_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *);
void special_cases(float coefficient_c, struct Solutions *);
int comparison(float a, float b);
void testing_values(struct Solutions *, struct Test_solutions *, const int quantity_of_tests);
int get_verdict(struct Solutions *, struct Test_solutions *);
void print_result_of_testing(int number_of_test, int verdict, struct Solutions *, struct Test_solutions *);



int main(){
    float coefficient_a = 0.0f;
    float coefficient_b = 0.0f;
    float coefficient_c = 0.0f;
    const int quantity_of_tests = 13;
    struct Test_solutions test_solutions[quantity_of_tests] = {
    1.0f,   0.0f,   -1.0f,   1.0f,      0.0f, -1.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    1.0f,   0.0f,   -4.0f,   2.0f,      0.0f, -2.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    5.0f,   12.0f,   4.0f,  -0.4f,      0.0f, -2.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
   -1.0f,   4.0f,   -3.0f,   1.0f,      0.0f,  3.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
   -1.232f, 4.324f, -2.324f, 0.662531f, 0.0f,  2.84721f, 0.0f, CASE_TWO_SOLUTIONS_REAL,


    1.0f, 1.0f, 1.0f, -0.5f, (sqrt(3) / 2.0f), -0.5f, (sqrt(3) / 2.0f), CASE_TWO_SOLUTIONS_COMPLEX,
    1.0f, 2.0f, 3.0f, -1.0f,  sqrt(2),          1.0f,  sqrt(2),         CASE_TWO_SOLUTIONS_COMPLEX,


    1.0f, 0.0f, 0.0f, 0.0f,          0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,
    0.0f,-2.0f, 3.0f, 1.5f,          0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,
    0.0f,-1.5f, 1.0f, (2.0f / 3.0f), 0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,


    0.0f, 0.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0.0f, NONE_SOLUTIONS,
    0.0f, 0.0f,-12.0f, 0.0f, 0.0f, 0.0f, 0.0f, NONE_SOLUTIONS,

    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, INFINITY_SOLUTIONS
    };

    //enter_coefficients(&coefficient_a, &coefficient_b, &coefficient_c);

    struct Solutions solutions = {0};
    testing_values(&solutions, test_solutions, quantity_of_tests);
    find_solutions(coefficient_a, coefficient_b, coefficient_c, &solutions);

    //print_solutions(&solutions);
    return 0;
}

void testing_values(struct Solutions *solutions, struct Test_solutions *test_solutions, const int quantity_of_tests){
    int i = 0;
    int verdict = 0;
    while (i < quantity_of_tests){
        verdict = get_verdict(solutions, &test_solutions[i]);
        print_result_of_testing(i + 1, verdict, solutions, &test_solutions[i]);
        i++;
    }
}


int get_verdict(struct Solutions *solutions, struct Test_solutions *test_solution){
    find_solutions(test_solution->coefficient_a, test_solution->coefficient_b, test_solution->coefficient_c, solutions);
    if (solutions->special_cases == test_solution->special_cases
    && (comparison(solutions->first_solution.real_part, test_solution->first_solution.real_part) == 0
    && comparison(solutions->second_solution.real_part, test_solution->second_solution.real_part) == 0
    && comparison(solutions->first_solution.complex_part, test_solution->first_solution.complex_part) == 0
    && comparison(solutions->second_solution.complex_part, test_solution->second_solution.complex_part) == 0)){
        return 0;
    } else {
        return 1;
    }
}

void print_resulting_of_testing(int number_of_test, int verdict, struct Solutions *solutions, struct Test_solutions *test_solution){
    if (verdict == 0){
        printf("Тест %d успешно пройден!\n", number_of_test);
    } else {
        printf("Тест %d не пройден!\n", number_of_test);
        printf("Здесь данные коэффициенты:\na=%f\nb=%f\nc=%f\n", test_solution->coefficient_a, test_solution->coefficient_b, test_solution->coefficient_c);
        printf("Вот верный ответ:\n");
        struct Solutions test = {0};
        test.first_solution.real_part = solutions->first_solution.real_part;
        test.second_solution.real_part = solutions->second_solution.real_part;
        test.first_solution.complex_part = solutions->first_solution.complex_part;
        test.second_solution.complex_part = solutions->second_solution.complex_part;
        print_solutions(&test);
        printf("\nВот ваш ответ:\n");
        print_solutions(solutions);
    }
}









int comparison(float a, float b){
    float eps = 1e-8f;
    if (b > a + eps){
        return -1;
    } else if (b <= (a + eps) && b >= (a - eps)){
        return 0;
    } else {
        return 1;
    }
}

int input_check(float *coefficient){
    const int BUFSIZE = 10;
    char *end = NULL;
    char bufer[BUFSIZE] = {};
    int i = 0;
    int c = getchar();
    while (c != '\n' && isspace(c)){
        c = getchar();
    }
    bool flag = false;
    while (i < BUFSIZE && c != EOF && c != '\n'){
        if (isspace(c)){
            flag = true;
        } else {
            flag = false;
        }
        if (!flag){
            bufer[i] = (char)c;
            i++;
        }
        c = getchar();
    }

    if (c == EOF || (c == '\n' && i == 0)){
        return 3;
    }
    if (c == '\n' || flag){
        if (flag){
            while(getchar() != '\n');
        }
        bufer[i] = '\0';
        *coefficient = strtof(bufer, &end);
        if (*end != '\0'){
            return 1;
        }
    } else {
        while(getchar() != '\n');
        return 2;
    }
    return 0;
}

void input(float *coefficient, char position){
    printf("Введите коэффициент %c:", position);
    int status = 0;
    do {
        status = input_check(coefficient);
        if (status == 1){
            printf("Неверный ввод! Введите коэффициент %c:", position);
        } else if (status == 2){
            printf("Переполнение буфера ввода! Повторите ввод коэффициента %c: ", position);
        } else if (status == 3) {
            printf("Вы ничего не ввели! Повторите ввод коэффициента %c: ", position);
        }
    } while (status != 0);
}


void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c){
    input(coefficient_a, 'a');
    input(coefficient_b, 'b');
    input(coefficient_c, 'c');
    //printf("%f %f %f\n", *coefficient_a, *coefficient_b, *coefficient_c);
}

void print_solutions(struct Solutions *solutions){
    switch (solutions->special_cases){
        case CASE_TWO_SOLUTIONS_COMPLEX:
            //printf("Уравнение имеет два комплексных решения:\n");
            printf("x1 = %.8f + %.8fi\n", solutions->first_solution.real_part, solutions->first_solution.complex_part);
            printf("x2 = %.8f - %.8fi\n", solutions->second_solution.real_part, solutions->second_solution.complex_part);
            break;
        case CASE_TWO_SOLUTIONS_REAL:
            //printf("Уравнение имеет два действительных решения:\n");
            printf("x1 = %.8f\nx2 = %.8f\n", solutions->first_solution.real_part, solutions->second_solution.real_part);
            break;
        case CASE_ONE_SOLUTION:
            //printf("Уравнение имеет единственное действительное решение:\n");
            printf("x = %.8f\n", solutions->first_solution.real_part);
            break;
        case NONE_SOLUTIONS:
            printf("Данное уравнение не имеет решений!\n");
            break;
        case INFINITY_SOLUTIONS:
            printf("Данное уравнение имеет бесконечно много решений!\n");
            break;
        default:
            printf("Error: Неизвестный случай!\n");
            break;
    }
}

void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *Discriminant){
    assert(Discriminant != NULL);
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
        return;
    }

    float discriminant2 = coefficient_b * coefficient_b - 4 * coefficient_a * coefficient_c;
    if (comparison(discriminant2, 0.0f) >= 0){
        Discriminant->discriminant = sqrtf(discriminant2);
        Discriminant->is_complex = false;
    } else {
        Discriminant->discriminant = sqrtf(-discriminant2);
        Discriminant->is_complex = true;
    }
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

void quadratic_equation(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);
    struct Discriminant_and_imagine_units Discriminant = {0};
    find_discriminant(coefficient_b, coefficient_c, coefficient_a, &Discriminant);
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
        return;
    }

    if (Discriminant.is_complex){/*Complex solutions*/
        find_complex_solutions(coefficient_a, coefficient_b, Discriminant.discriminant, solutions);
        return;
    }
    find_real_solutions(coefficient_a, coefficient_b, Discriminant.discriminant, solutions);

}

void find_real_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *solutions){
    if (comparison(discriminant, 0.0f) == 0){
        float x = (-coefficient_b) / (2 * coefficient_a);
        solutions->first_solution.real_part = x;
        solutions->first_solution.complex_part = 0;
        solutions->second_solution.real_part = 0;
        solutions->second_solution.complex_part = 0;
        solutions->special_cases = CASE_ONE_SOLUTION;
        return;
    }
    solutions->special_cases = CASE_TWO_SOLUTIONS_REAL;
    float x1 = 0.0f, x2 = 0.0f;
    x1 = (-coefficient_b + discriminant) / (2 * coefficient_a);
    x2 = (-coefficient_b - discriminant) / (2 * coefficient_a);
    solutions->first_solution.real_part = x1;
    solutions->first_solution.complex_part = 0;
    solutions->second_solution.real_part = x2;
    solutions->second_solution.complex_part = 0;
}

void find_complex_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *solutions){
    solutions->special_cases = CASE_TWO_SOLUTIONS_COMPLEX;
    solutions->first_solution.real_part = (-coefficient_b / (2 * coefficient_a));
    solutions->first_solution.complex_part = (discriminant / (2 * coefficient_a));
    solutions->second_solution.real_part = (-coefficient_b / (2 * coefficient_a));
    solutions->second_solution.complex_part = (discriminant / (2 * coefficient_a));
}

void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);

    if (comparison(coefficient_b, 0.0f) == 0){
        printf("Error: Данное уравнение не является линейным!\n");
        return;
    }
    solutions->first_solution.real_part = (comparison(coefficient_c, 0) != 0) ? ((-coefficient_c) / coefficient_b) : 0;
    solutions->first_solution.complex_part = 0;
    solutions->special_cases = CASE_ONE_SOLUTION;
}

void special_cases(float coefficient_c, struct Solutions *solutions){
    assert(solutions != NULL);

    if (comparison(coefficient_c, 0.0f) != 0){
        solutions->special_cases = NONE_SOLUTIONS;
    } else {
        solutions->special_cases = INFINITY_SOLUTIONS;
    }
}
