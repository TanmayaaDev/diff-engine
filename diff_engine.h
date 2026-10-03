#ifndef DIFF_ENGINE_H
#define DIFF_ENGINE_H

#include <stddef.h>

// Vector state representation for n-coupled equations
typedef struct {
    size_t dim;
    double *data;
} Vector;

// Function pointer for system derivatives: dydt = f(t, y)
typedef void (*ODEFunc)(double t, const Vector *y, Vector *dydt);

// Memory management helpers
Vector* vector_create(size_t dim);
void vector_free(Vector *v);

// Solvers
void ode_step_euler(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt);
void ode_step_heun(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt);
void ode_step_rk4(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt);

#endif // DIFF_ENGINE_H