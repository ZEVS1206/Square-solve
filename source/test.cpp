#include "Test.h"
#include "Solver.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

static void print_result_of_testing(int number_of_test, int verdict, const struct Solutions *, const struct Test_solutions *);
static void testing_values(struct Test_solutions *, int quantity_of_tests);
static int get_verdict(struct Solutions *, const struct Test_solutions *);


void test_programm(void){
    const int max_quantity_of_tests = 20;
    FILE *fp = fopen("C://Users//egor_//Documents//GitHub//Square-solve//source//tests.txt", "r");
    int cnt = 0;
    int c = 0;
    while ((c = getc(fp)) != EOF){
        if (c == '\n'){
            cnt++;
        }
    }
    rewind(fp);
    //printf("%d\n", cnt);
    struct Test_solutions test_solutions[max_quantity_of_tests] = {0};
    int element = 0;
    for (int i = 0; i < cnt; i++){
        fscanf(fp, "%f %f %f %f %f %f %f", &test_solutions[i].coefficients.coefficient_a,
                                           &test_solutions[i].coefficients.coefficient_b,
                                           &test_solutions[i].coefficients.coefficient_c,
                                           &test_solutions[i].solutions.first_solution.real_part,
                                           &test_solutions[i].solutions.first_solution.complex_part,
                                           &test_solutions[i].solutions.second_solution.real_part,
                                           &test_solutions[i].solutions.second_solution.complex_part);

        fscanf(fp, "%d", &element);
        test_solutions[i].solutions.special_cases = (Case_of_solution)element;
        if (element == -2){
            test_solutions[i].solutions.special_cases = NONE_SOLUTIONS;
        } else if (element == -1){
            test_solutions[i].solutions.special_cases = CASE_ONE_SOLUTION;
        } else if (element == 0){
            test_solutions[i].solutions.special_cases = CASE_TWO_SOLUTIONS_REAL;
        } else if (element == 1){
            test_solutions[i].solutions.special_cases = CASE_TWO_SOLUTIONS_COMPLEX;
        } else if (element == 2) {
            test_solutions[i].solutions.special_cases = INFINITY_SOLUTIONS;
        }
    }
    printf("%f\n", test_solutions[0].coefficients.coefficient_a);
    testing_values(test_solutions, cnt);
}

static void testing_values(struct Test_solutions *test_solutions, int quantity_of_tests){
    int verdict = 0;
    for (int i = 0; i < quantity_of_tests; i++){
        struct Solutions solutions = {0};
        verdict = get_verdict(&solutions, &test_solutions[i]);
        //printf("Test %d. Verdict %d\n", i+1, verdict);
        print_result_of_testing(i + 1, verdict, &solutions, &test_solutions[i]);
    }
}

static int get_verdict(struct Solutions *solutions, const struct Test_solutions *test_solution){
    find_solutions(&(test_solution->coefficients), solutions);
    if (solutions->special_cases == test_solution->solutions.special_cases
        && (comparison(test_solution->solutions.first_solution.real_part, solutions->first_solution.real_part) == 0
        &&  comparison(test_solution->solutions.second_solution.real_part, solutions->second_solution.real_part) == 0
        &&  comparison(test_solution->solutions.first_solution.complex_part, solutions->first_solution.complex_part) == 0
        &&  comparison(test_solution->solutions.second_solution.complex_part, solutions->second_solution.complex_part) == 0)){
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
        printf("There are coefficients:\na=%f\nb=%f\nc=%f\n", test_solution->coefficients.coefficient_a,
                                                              test_solution->coefficients.coefficient_b,
                                                              test_solution->coefficients.coefficient_c);
        printf("There are correct answers:\n");
        struct Solutions test = {0};
        test.first_solution.real_part     = test_solution->solutions.first_solution.real_part;
        test.second_solution.real_part    = test_solution->solutions.second_solution.real_part;
        test.first_solution.complex_part  = test_solution->solutions.first_solution.complex_part;
        test.second_solution.complex_part = test_solution->solutions.second_solution.complex_part;
        test.special_cases                = test_solution->solutions.special_cases;
        print_solutions(&test);
        printf("\nThere are your answers:\n");
        print_solutions(solutions);
        printf("\n");
    }
}
