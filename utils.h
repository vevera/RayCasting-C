#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>

double min(double a, double b);
double max(double a, double b);
double maxof(int n, ...);

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

double maxof(int n, ...){

    va_list args;
    va_start(args, n);

    double max = -INFINITY;

    for (int i = 0; i<n; i++) {
        printf("val: %d ", va_arg(args, int));
    }

    va_end(args);
    return max;
}

#endif