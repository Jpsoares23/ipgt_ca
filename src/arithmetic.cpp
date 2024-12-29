#include "arithmetic.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

int exponencial(int a, int b) {
    int result = 1;

    for (int i = 0; i < b; ++i) {
        result *= a;
    }
    return result;
}