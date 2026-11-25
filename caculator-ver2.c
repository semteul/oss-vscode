#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNumber(const char *str) {
    if (*str == '+' || *str == '-') {
        str++;
    }

    if (*str == '\0') {
        return 0;
    }

    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            return 0;
        }
        str++;
    }

    return 1;
}

static int readNumber(const char *prompt, int *number) {
    char input[100];
    char *end;
    long value;

    printf("%s", prompt);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }
    input[strcspn(input, "\r\n")] = '\0';

    if (!isNumber(input)) {
        return 0;
    }

    errno = 0;
    value = strtol(input, &end, 10);
    if (errno == ERANGE || *end != '\0' || value < INT_MIN || value > INT_MAX) {
        return 0;
    }

    *number = (int)value;
    return 1;
}

int main(void) {
    printf("---------- caculator.c --------\n");
    printf("This is a simple calculator program.\n");

    int a, b;
    char operatorInput[100];
    char operator;

    if (!readNumber("Enter first number: ", &a)) {
        printf("Error: Please enter a valid integer.\n");
        return 1;
    }
    printf("Enter an operator (+, -, *, /): ");
    if (fgets(operatorInput, sizeof(operatorInput), stdin) == NULL) {
        printf("Error: Could not read operator.\n");
        return 1;
    }
    operatorInput[strcspn(operatorInput, "\r\n")] = '\0';
    if (operatorInput[0] == '\0' || operatorInput[1] != '\0') {
        printf("Error: Invalid operator.\n");
        return 1;
    }
    operator = operatorInput[0];
    if (!readNumber("Enter second number: ", &b)) {
        printf("Error: Please enter a valid integer.\n");
        return 1;
    }

    if (operator == '/' && b == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return 1;
    }

    switch (operator) {
        case '+':
            printf("%d + %d = %d\n", a, b, a + b);
            break;
        case '-':
            printf("%d - %d = %d\n", a, b, a - b);
            break;
        case '*':
            printf("%d * %d = %d\n", a, b, a * b);
            break;
        case '/':
            if (b != 0) {
                printf("%d / %d = %.2f\n", a, b, (float)a / b);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error: Invalid operator.\n");
    }

    printf("Thank you for using the calculator!\n");


    return 0;
}