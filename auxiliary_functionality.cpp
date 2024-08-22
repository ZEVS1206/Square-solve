#include "Headers.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

enum Case_of_input
{
    NO_PROBLEMS         = 0,
    INCORRECT_INPUT     = 1,
    PROBLEM_OF_OVERFLOW = 2,
    PROBLEM_OF_NO_INPUT = 3
};


static Case_of_input input_check(float *coefficient);
static void input(float *coefficient, char position);
static void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *);/*discriminant*/
static void quadratic_equation(float coefficient_a, float coefficient_b, float coefficient_c, struct Solutions *);
static void find_real_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
static void find_complex_solutions(float coefficient_a, float coefficient_b, float discriminant, struct Solutions *);
static void linear_equation(float coefficient_b, float coefficient_c, struct Solutions *);
static void special_cases(float coefficient_c, struct Solutions *);
static int comparison(float a, float b);
static void print_result_of_testing(int number_of_test, int verdict, const struct Solutions *, const struct Test_solutions *);
static void testing_values(struct Test_solutions *, const int quantity_of_tests);
static int get_verdict(struct Solutions *, const struct Test_solutions *);


struct Discriminant_and_imagine_units {
    float discriminant;
    bool is_complex;
};

struct Test_solutions {
    float coefficient_a;
    float coefficient_b;
    float coefficient_c;
    Complex_number first_solution;
    Complex_number second_solution;
    Case_of_solution special_cases;
};


void test_programm(void){
    struct Test_solutions test_solutions[] = {
    /*#1*/1.0f,   0.0f,  -1.0f,  1.0f,      0.0f, 1.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    /*#2*/1.0f,   0.0f,  -4.0f,  2.0f,      0.0f, -2.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    /*#3*/5.0f,   12.0f,  4.0f, -0.4f,      0.0f, -2.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    /*#4*/-1.0f,  4.0f,  -3.0f,  1.0f,      0.0f,  3.0f,     0.0f, CASE_TWO_SOLUTIONS_REAL,
    /*#5*/-1.232f,4.324f,-2.324f,0.662531f, 0.0f,  2.847209f, 0.0f, CASE_TWO_SOLUTIONS_REAL,


    /*#6*/1.0f, 1.0f, 1.0f, -0.5f, (sqrtf(3) / 2.0f), -0.5f, (sqrtf(3) / 2.0f), CASE_TWO_SOLUTIONS_COMPLEX,
    /*#7*/1.0f, 2.0f, 3.0f, -1.0f,  sqrtf(2),         -1.0f,  sqrtf(2),         CASE_TWO_SOLUTIONS_COMPLEX,


    /*#8*/ 1.0f, 0.0f, 0.0f, 0.0f,          0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,
    /*#9*/ 0.0f,-2.0f, 3.0f, 1.5f,          0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,
    /*#10*/0.0f,-1.5f, 1.0f, (2.0f / 3.0f), 0.0f,    0.0f, 0.0f, CASE_ONE_SOLUTION,


    /*#11*/0.0f, 0.0f, 28.0f, 0.0f, 0.0f, 0.0f, 0.0f, NONE_SOLUTIONS,
    /*#12*/0.0f, 0.0f,-12.0f, 0.0f, 0.0f, 0.0f, 0.0f, NONE_SOLUTIONS,

    /*#13*/0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, INFINITY_SOLUTIONS
    };
    const size_t quantity_of_tests = sizeof(test_solutions) / sizeof(Test_solutions);
    testing_values(test_solutions, quantity_of_tests);
}


static void testing_values(struct Test_solutions *test_solutions, const int quantity_of_tests){
    int i = 0;
    int verdict = 0;
    while (i < quantity_of_tests){
        struct Solutions solutions = {0};
        verdict = get_verdict(&solutions, &test_solutions[i]);
        //printf("Test %d. Verdict %d\n", i+1, verdict);
        print_result_of_testing(i + 1, verdict, &solutions, &test_solutions[i]);
        i++;
    }
}


static int get_verdict(struct Solutions *solutions, const struct Test_solutions *test_solution){
    find_solutions(test_solution->coefficient_a, test_solution->coefficient_b, test_solution->coefficient_c, solutions);
    if (solutions->special_cases == test_solution->special_cases
        && (comparison(test_solution->first_solution.real_part, solutions->first_solution.real_part) == 0
        && comparison(test_solution->second_solution.real_part, solutions->second_solution.real_part) == 0
        && comparison(test_solution->first_solution.complex_part, solutions->first_solution.complex_part) == 0
        && comparison(test_solution->second_solution.complex_part, solutions->second_solution.complex_part) == 0)){
        return 0;
    } else {
        return 1;
    }
}


static void print_result_of_testing(int number_of_test, int verdict, const struct Solutions *solutions, const struct Test_solutions *test_solution){
    if (verdict == 0){
        printfGreen("Тест %d успешно пройден!\n", number_of_test);
    } else {
        printfRed("Тест %d не пройден!\n", number_of_test);
        printf("Здесь данные коэффициенты:\na=%f\nb=%f\nc=%f\n", test_solution->coefficient_a, test_solution->coefficient_b, test_solution->coefficient_c);
        printf("Вот верный ответ:\n");
        struct Solutions test = {0};
        test.first_solution.real_part = solutions->first_solution.real_part;
        test.second_solution.real_part = solutions->second_solution.real_part;
        test.first_solution.complex_part = solutions->first_solution.complex_part;
        test.second_solution.complex_part = solutions->second_solution.complex_part;
        test.special_cases = solutions->special_cases;
        print_solutions(&test);
        printf("\nВот ваш ответ:\n");
        print_solutions(solutions);
        printf("\n");
    }
}


static int comparison(float a, float b){
    float eps = 1e-6f;
    if (b >= a + eps){
        return -1;
    } else if (b < (a + eps) && b > (a - eps)){
        return 0;
    } else {
        return 1;
    }
}

static Case_of_input input_check(float *coefficient){
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
        return PROBLEM_OF_NO_INPUT;
    }
    if (c == '\n' || flag){
        if (flag){
            while(getchar() != '\n');
        }
        bufer[i] = '\0';
        *coefficient = strtof(bufer, &end);
        if (*end != '\0'){
            return INCORRECT_INPUT;
        }
    } else {
        while(getchar() != '\n');
        return PROBLEM_OF_OVERFLOW;
    }
    return NO_PROBLEMS;
}


static void input(float *coefficient, char position){
    printf("Введите коэффициент %c:", position);
    Case_of_input status = NO_PROBLEMS;
    do {
        status = input_check(coefficient);
        if (status == INCORRECT_INPUT){
            printf("Неверный ввод! Введите коэффициент %c:", position);
        } else if (status == PROBLEM_OF_OVERFLOW){
            printf("Переполнение буфера ввода! Повторите ввод коэффициента %c: ", position);
        } else if (status == PROBLEM_OF_NO_INPUT) {
            printf("Вы ничего не ввели! Повторите ввод коэффициента %c: ", position);
        }
    } while (status != NO_PROBLEMS);
}


void enter_coefficients(float *coefficient_a, float *coefficient_b, float *coefficient_c){
    input(coefficient_a, 'a');
    input(coefficient_b, 'b');
    input(coefficient_c, 'c');
    //printf("%f %f %f\n", *coefficient_a, *coefficient_b, *coefficient_c);
}


void print_solutions(const struct Solutions *solutions){
    switch (solutions->special_cases){
        case CASE_TWO_SOLUTIONS_COMPLEX:
            //printf("Уравнение имеет два комплексных решения:\n");
            printf("x1 = %.6f + %.6fi\n", solutions->first_solution.real_part, solutions->first_solution.complex_part);
            printf("x2 = %.6f - %.6fi\n", solutions->second_solution.real_part, solutions->second_solution.complex_part);
            break;
        case CASE_TWO_SOLUTIONS_REAL:
            //printf("Уравнение имеет два действительных решения:\n");
            printf("x1 = %.6f\nx2 = %.6f\n", solutions->first_solution.real_part, solutions->second_solution.real_part);
            break;
        case CASE_ONE_SOLUTION:
            //printf("Уравнение имеет единственное действительное решение:\n");
            printf("x = %.6f\n", solutions->first_solution.real_part);
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


static void find_discriminant(float coefficient_b, float coefficient_c, float coefficient_a, struct Discriminant_and_imagine_units *Discriminant){
    assert(Discriminant != NULL);
    if (comparison(coefficient_a, 0.0f) == 0){
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
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
        printf("Error: Данное уравнение не является квадратным, поэтому вызов функции дискриминанта не корректен!\n");
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
        float x = (-coefficient_b) / (2 * coefficient_a);
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
        printf("Error: Данное уравнение не является линейным!\n");
        return;
    }
    solutions->first_solution.real_part = (comparison(coefficient_c, 0) != 0) ? ((-coefficient_c) / coefficient_b) : 0;
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
