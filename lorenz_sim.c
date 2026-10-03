#include "diff_engine.h"
#include <stdio.h>

// Lorenz System parameters
#define SIGMA 10.0
#define RHO 28.0
#define BETA (8.0 / 3.0)

void lorenz_system(double t, const Vector *y, Vector *dydt) {
    (void)t;
    double x = y->data[0];
    double y_val = y->data[1];
    double z = y->data[2];

    dydt->data[0] = SIGMA * (y_val - x);
    dydt->data[1] = x * (RHO - z) - y_val;
    dydt->data[2] = x * y_val - BETA * z;
}

int main(void) {
    Vector *y = vector_create(3);
    Vector *y_next = vector_create(3);

    // Initial state: x=1.0, y=1.0, z=1.0
    y->data[0] = 1.0;
    y->data[1] = 1.0;
    y->data[2] = 1.0;

    double t = 0.0;
    double dt = 0.01;
    int steps = 5000;

    FILE *fp = fopen("lorenz_output.csv", "w");
    fprintf(fp, "t,x,y,z\n");

    for (int i = 0; i < steps; i++) {
        fprintf(fp, "%.4f,%.6f,%.6f,%.6f\n", t, y->data[0], y->data[1], y->data[2]);
        ode_step_rk4(lorenz_system, t, y, y_next, dt);

        for (size_t j = 0; j < 3; j++) {
            y->data[j] = y_next->data[j];
        }
        t += dt;
    }

    fclose(fp);
    vector_free(y);
    vector_free(y_next);

    printf("Lorenz trajectory generated successfully in lorenz_output.csv\n");
    return 0;
}