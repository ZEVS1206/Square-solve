#include "Input_output.h"
#include "Solver.h"
#include "Test.h"

#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


static Case_of_input input_check(float *coefficient);
static void input(float *coefficient, char position);
static void user_input();
static Type input_from_console(int argc, char *argv[]);
static void mode_of_programm(Type type);

void special_input(int argc, char *argv[]){
    Type type = ERROR_OF_INPUT;
    type = input_from_console(argc, argv);
    mode_of_programm(type);
}


Type input_from_console(int argc, char *argv[]){
    if (argc > 2 || argv[1][0] != '-'){
        return ERROR_OF_INPUT;
    }
    int symbol = 0;
    int cnt = 0;
    Type result = ERROR_OF_INPUT;
    int index = 0;
    while ((symbol = argv[1][++index])){
        cnt++;
        switch (symbol){
            case 't':
                result = TEST_COEFFICIENTS;
                break;
            case 'u':
                result = USER_COEFFICIENTS;
                break;
            default:
                result = ERROR_OF_INPUT;
                break;
        }
        if (cnt > 1){
            break;
        }
    }
    if (cnt > 1){
        return ERROR_OF_INPUT;
    }
    return result;


}

static void mode_of_programm(Type type){
    if (type == ERROR_OF_INPUT){
        printfRed("Incorrect input!\n");
    } else if (type == TEST_COEFFICIENTS){
        test_programm();
    } else {
        user_input();
    }
}


static void user_input(){
    struct Coefficients coefficients = {0};
    enter_coefficients(&coefficients);
    struct Solutions solutions = {0};
    find_solutions(&coefficients, &solutions);
    print_solutions(&solutions);
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
    if (   strcmp(bufer, "nan") == 0
        || strcmp(bufer, "inf") == 0
        || strcmp(bufer, "NAN") == 0
        || strcmp(bufer, "INF") == 0){
        return PROBLEM_OF_NO_INPUT;
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
    printf("Enter coefficient %c:", position);
    Case_of_input status = NO_PROBLEMS;
    do {
        status = input_check(coefficient);
        if (status == INCORRECT_INPUT){
            printf("Incorrect input! Repeat the input of coefficient %c:", position);
        } else if (status == PROBLEM_OF_OVERFLOW){
            printf("The buffer was overflowed. Repeat the input of coefficient %c: ", position);
        } else if (status == PROBLEM_OF_NO_INPUT) {
            printf("Incorrect input! You did not enter anything, please enter the coefficient %c: ", position);
        }
    } while (status != NO_PROBLEMS);
}

void enter_coefficients(struct Coefficients *coefficients){
    input(&(coefficients->coefficient_a), 'a');
    input(&(coefficients->coefficient_b), 'b');
    input(&(coefficients->coefficient_c), 'c');
    //printf("%f %f %f\n", *coefficient_a, *coefficient_b, *coefficient_c);
}

void print_solutions(const struct Solutions *solutions){
    switch (solutions->special_cases){
        case CASE_TWO_SOLUTIONS_COMPLEX:
            printf("x1 = %.6f + %.6fi\n", solutions->first_solution.real_part,
                                          solutions->first_solution.complex_part);
            printf("x2 = %.6f - %.6fi\n", solutions->second_solution.real_part,
                                          solutions->second_solution.complex_part);
            break;
        case CASE_TWO_SOLUTIONS_REAL:
            printf("x1 = %.6f\nx2 = %.6f\n", solutions->first_solution.real_part,
                                             solutions->second_solution.real_part);
            break;
        case CASE_ONE_SOLUTION:
            printf("x = %.6f\n", solutions->first_solution.real_part);
            break;
        case NONE_SOLUTIONS:
            printf("This equation has no solutions!\n");
            break;
        case INFINITY_SOLUTIONS:
            printf("This equation has an infinity of solutions!\n");
            break;
        default:
            printf("Error: Unknown case!\n");
            break;
    }
}
