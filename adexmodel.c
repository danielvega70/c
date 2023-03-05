#include <iostream>
#include <cmath>
#include <vector>

// Define model parameters
const double tau_m = 5.0; // membrane time scale
const double R = 500.0; // membrane resistance
const double v_rest = -70.0; // resting potential
const double v_reset = -51.0; // reset potential
const double v_rheobase = -50.0; // rheobase threshold
const double a = 0.5; // Adaptation-Voltage coupling
const double b = 7.0; // Spike-triggered adaptation current
const double v_spike = -30.0; // voltage threshold for spike condition
const double delta_T = 2.0; // Sharpness of exponential term
const double tau_w = 100.0; // Adaptation time constant

// Define simulation parameters
const double dt = 0.01; // time step
const double t_start = 0.0; // start time
const double t_end = 200.0; // end time

// Define input stimulus
double I_stim(double t)
{
    // Zero current
    return 0.0;
}

int main()
{
    // Initialize state variables
    double v = v_rest;
    double w = 0.0;

    // Initialize time and spike variables
    double t = t_start;
    std::vector<double> spike_times;

    // Define loop for simulation
    while (t < t_end)
    {
        // Calculate input current
        double I = I_stim(t);

        // Update state variables using Euler's method
        double dv = (-1.0*(v-v_rest) + delta_T*exp((v-v_rheobase)/delta_T) + R*I - R*w) / tau_m;
        double dw = (a*(v-v_rest) - w) / tau_w;
        v = v + dt*dv;
        w = w + dt*dw;

        // Check for spike condition
        if (v >= v_spike)
        {
            // Record spike time and reset state variables
            spike_times.push_back(t);
            v = v_reset;
            w = w + b;
        }

        // Increment time step
        t = t + dt;
    }

    // Visualize results (e.g. using gnuplot or matplotlib)
    // ...
    
    return 0;
}
