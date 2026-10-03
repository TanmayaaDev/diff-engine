# DiffEngine-C

A lightweight, high-performance C99 numerical solver engine designed for integrating systems of ordinary differential equations (ODEs). `DiffEngine-C` provides explicit integration schemes, dynamic CSV exporting, unit testing, and an off-line Python trajectory visualizer.

---

## Features

- **Multiple Integration Schemes:**
  - **Euler Method** (1st Order)
  - **Heun's Method** (2nd Order Improved Euler)
  - **Runge-Kutta 4th Order (RK4)**
- **System Simulation:** Standardized function pointers for $n$-dimensional autonomous and non-autonomous systems.
- **Data Export Pipeline:** Built-in CSV export interface for state-space trajectories.
- **Visualization:** Integrated Python post-processing script (`visualize.py`) using `matplotlib` to render 2D/3D state trajectories (e.g., Lorenz Attractor).
- **Zero External Dependencies:** Built purely on standard C libraries (`math.h`, `stdio.h`, `stdlib.h`).

---

## Directory Structure

```text
DiffEngine-C/
├── build/              # Compiled object files
├── include/            # C header files (.h)
│   └── diff_engine.h
├── src/                # Implementation files (.c)
│   ├── diff_engine.c
│   └── lorenz_sim.c
├── tests/              # Unit test suites
│   └── tests_solvers.c
├── Makefile            # Build configuration
├── visualize.py        # Python script for state trajectory plotting
└── README.md

Build & Installation

Ensure you have gcc (or any C99-compliant compiler) and make installed.

Using Makefile
To compile the library and test suites:

Bash
make clean
make

Running the Unit Tests

To compile and run the solver validation tests manually:

Bash
gcc -Iinclude src/diff_engine.c tests/tests_solvers.c -o tests/test_solvers -lm
./tests/test_solvers

Example: Lorenz Attractor Simulation
To run the Lorenz system simulation and export state trajectories to CSV:

Compile and run the simulation:

Bash
gcc -Iinclude src/diff_engine.c src/lorenz_sim.c -o lorenz_sim -lm
./lorenz_sim
This outputs lorenz_output.csv containing state vectors over time.

Visualize the trajectories:

Bash
python3 visualize.py lorenz_output.csv

API Overview

C
// System function signature
typedef void (*ODEFunc)(double t, const double y[], double dydt[], void *params);

// Solvers
void ode_step_euler(ODEFunc f, double t, const double y[], double y_out[], double dt, int dim, void *params);
void ode_step_heun(ODEFunc f, double t, const double y[], double y_out[], double dt, int dim, void *params);
void ode_step_rk4(ODEFunc f, double t, const double y[], double y_out[], double dt, int dim, void *params);

License
MIT License. Open-source and free for academic, personal, and commercial engineering applications.