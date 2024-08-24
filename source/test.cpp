#include "test.h"
#include "solver.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

static void print_result_of_testing(int number_of_test, int verdict, const struct Solutions *, const struct Test_solutions *);
static void testing_values(struct Test_solutions *, const int quantity_of_tests);
static int get_verdict(struct Solutions *, const struct Test_solutions *);

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
        printfGreen("Test %2d:  OK\n", number_of_test);
    } else {
        printfRed("Test %2d:  Failed\n", number_of_test);
        printf("There are coefficients:\na=%f\nb=%f\nc=%f\n", test_solution->coefficient_a,
                                                              test_solution->coefficient_b,
                                                              test_solution->coefficient_c);
        printf("There are correct answers:\n");
        struct Solutions test = {0};
        test.first_solution.real_part     = test_solution->first_solution.real_part;
        test.second_solution.real_part    = test_solution->second_solution.real_part;
        test.first_solution.complex_part  = test_solution->first_solution.complex_part;
        test.second_solution.complex_part = test_solution->second_solution.complex_part;
        test.special_cases = solutions->special_cases;
        print_solutions(&test);
        printf("\nThere are your answers:\n");
        print_solutions(solutions);
        printf("\n");
    }
}
