#ifndef UTILS_H
#define UTILS_H

double min(double a, double b);
double max(double a, double b);

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

#endif