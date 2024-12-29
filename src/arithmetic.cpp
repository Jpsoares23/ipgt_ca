#include "arithmetic.h"

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b;
}

float multiply(float a, float b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

// exponencial only handle int b >= 1
float exponencial(float a, float b) { 
    float result = 1;

    for (int i = 0; i < b; ++i) {
        result *= a;
    }
    return result;
}