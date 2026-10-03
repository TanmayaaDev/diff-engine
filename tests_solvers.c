#include "diff_engine.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

void decay_system(double t, const Vector *y, Vector *dydt) {
    (void)t;
    dydt->data[0] = -y->data[0];
}

int main(void) {
    Vector *y = vector_create(1);
    Vector *y_next = vector_create(1);

    y->data[0] = 1.0;
    double dt = 0.1;
    double t = 0.0;

    // Run 10 steps of RK4
    for (int i = 0; i < 10; i++) {
        ode_step_rk4(decay_system, t, y, y_next, dt);
        y->data[0] = y_next->data[0];
        t += dt;
    }

    double analytical = exp(-1.0); // y(1.0) = e^-1
    double error = fabs(y->data[0] - analytical);

    printf("RK4 Result at t=1.0: %.8f | Expected: %.8f | Error: %.8e\n", 
           y->data[0], analytical, error);

    assert(error < 1e-5);
    printf("Unit test PASSED!\n");

    vector_free(y);
    vector_free(y_next);
    return 0;
}