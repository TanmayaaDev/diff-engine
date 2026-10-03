#include "diff_engine.h"
#include <stdio.h>
#include <stdlib.h>

Vector* vector_create(size_t dim) {
    Vector *v = (Vector*)malloc(sizeof(Vector));
    v->dim = dim;
    v->data = (double*)calloc(dim, sizeof(double));
    return v;
}

void vector_free(Vector *v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

// Forward Euler Method: y_{n+1} = y_n + dt * f(t_n, y_n)
void ode_step_euler(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt) {
    Vector *dydt = vector_create(y->dim);
    f(t, y, dydt);
    for (size_t i = 0; i < y->dim; i++) {
        y_next->data[i] = y->data[i] + dt * dydt->data[i];
    }
    vector_free(dydt);
}

// Heun's Method (Predictor-Corrector)
void ode_step_heun(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt) {
    size_t dim = y->dim;
    Vector *k1 = vector_create(dim);
    Vector *y_pred = vector_create(dim);
    Vector *k2 = vector_create(dim);

    f(t, y, k1);
    for (size_t i = 0; i < dim; i++) {
        y_pred->data[i] = y->data[i] + dt * k1->data[i];
    }

    f(t + dt, y_pred, k2);
    for (size_t i = 0; i < dim; i++) {
        y_next->data[i] = y->data[i] + (dt / 2.0) * (k1->data[i] + k2->data[i]);
    }

    vector_free(k1);
    vector_free(y_pred);
    vector_free(k2);
}

// Classical Runge-Kutta 4th Order (RK4)
void ode_step_rk4(ODEFunc f, double t, const Vector *y, Vector *y_next, double dt) {
    size_t dim = y->dim;
    Vector *k1 = vector_create(dim);
    Vector *k2 = vector_create(dim);
    Vector *k3 = vector_create(dim);
    Vector *k4 = vector_create(dim);
    Vector *temp = vector_create(dim);

    // k1 = f(t, y)
    f(t, y, k1);

    // k2 = f(t + dt/2, y + dt/2 * k1)
    for (size_t i = 0; i < dim; i++) temp->data[i] = y->data[i] + 0.5 * dt * k1->data[i];
    f(t + 0.5 * dt, temp, k2);

    // k3 = f(t + dt/2, y + dt/2 * k2)
    for (size_t i = 0; i < dim; i++) temp->data[i] = y->data[i] + 0.5 * dt * k2->data[i];
    f(t + 0.5 * dt, temp, k3);

    // k4 = f(t + dt, y + dt * k3)
    for (size_t i = 0; i < dim; i++) temp->data[i] = y->data[i] + dt * k3->data[i];
    f(t + dt, temp, k4);

    // y_{n+1} = y_n + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    for (size_t i = 0; i < dim; i++) {
        y_next->data[i] = y->data[i] + (dt / 6.0) * (k1->data[i] + 2.0 * k2->data[i] + 2.0 * k3->data[i] + k4->data[i]);
    }

    vector_free(k1);
    vector_free(k2);
    vector_free(k3);
    vector_free(k4);
    vector_free(temp);
}