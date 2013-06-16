#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALPHA 0.01
#define THETA_INITIAL 5
#define ERROR_TOLERANCE 0.000001
#define DIMENSIONS 2

double h_theta(double theta[], double x[]) {
    double accum = 0;
    for (int i = 0; i < DIMENSIONS; i++) {
        accum += (theta[i] * x[i]);
    }
    return accum;
}

double predicted_minus_actual(double theta[], double x[], double y) {
    return (h_theta(theta, x) - y);
}

double dXdTheta_J(double theta[], double x[][DIMENSIONS], double y[], int index, int obs_count) {
    double accum = 0;
    for (int i = 0; i < obs_count; i++) {
        accum += predicted_minus_actual(theta, x[i], y[i]) * x[i][index];
    }
    return (1.0/obs_count) * accum;
}

int valuesWithinErrorBound(double values[], int len) {
    for (int i = 0; i < len; i++ ) {
        if ((fabs(values[i]) - ERROR_TOLERANCE) <= 0) {
            return 0;
        }
    }
    return 1;
}

double *descend_gradient(double x[][DIMENSIONS], double y[], int obs_count) {
    double theta[DIMENSIONS], delta[DIMENSIONS];

    for (int i = 0; i < DIMENSIONS; i++) {
        theta[i] = THETA_INITIAL;
        delta[i] = 0;
    }

    do {
        for (int i = 0; i < DIMENSIONS; i++) {
            delta[i] = ALPHA * dXdTheta_J(theta, x, y, i, obs_count);
        }
        for (int i = 0; i < DIMENSIONS; i++) {
            theta[i] = theta[i] - delta[i];
        }
    } while (valuesWithinErrorBound(delta, DIMENSIONS));

    double *result = malloc(sizeof(double) * DIMENSIONS);
    for (int i = 0; i < DIMENSIONS; i++) {
        result[i] = theta[i];
    }

    return result;
}

int main(int argc, char **argv) {
    double x[][DIMENSIONS] = {
        {1.0, 2.0}, 
        {1.0, 6.0}, 
        {1.0, 9.0}, 
        {1.0, 12.0}
    };
    double y[] = { 4.0, 12.0, 18.0, 24.0 };

    int size = sizeof(y)/sizeof(double);
    double *gd = descend_gradient(x, y, size);

    printf("optimal parameters, calculated from %d observations: (", size); 
    for (int i = 0; i < DIMENSIONS; i++) {
        printf("%f", gd[i]);
        if (i + 1 < DIMENSIONS) printf(", ");
    }
    printf(")\n");

    return 0;
}
