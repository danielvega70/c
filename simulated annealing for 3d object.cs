#include <iostream>
#include <cmath>
#include <random>

using namespace std;

// Define the size of the search space
const double SPACE_SIZE = 100.0;

// Define the number of iterations
const int NUM_ITERATIONS = 1000;

// Define the initial temperature
const double INITIAL_TEMPERATURE = 100.0;

// Define the cooling rate
const double COOLING_RATE = 0.95;

// Define the random number generator
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> dis(-SPACE_SIZE/2.0, SPACE_SIZE/2.0);

// Define a function to calculate the energy of a solution
double calculate_energy(double x, double y, double z)
{
    // Calculate the distance from the origin
    double distance = sqrt(x*x + y*y + z*z);

    // Return the negative distance as the energy
    return -distance;
}

// Define a function to generate a neighbor solution
void generate_neighbor(double& x, double& y, double& z)
{
    // Generate a random displacement
    double dx = dis(gen);
    double dy = dis(gen);
    double dz = dis(gen);

    // Add the displacement to the current solution
    x += dx;
    y += dy;
    z += dz;
}

int main()
{
    // Initialize the current solution
    double x = dis(gen);
    double y = dis(gen);
    double z = dis(gen);

    // Initialize the current energy
    double energy = calculate_energy(x, y, z);

    // Initialize the best solution
    double best_x = x;
    double best_y = y;
    double best_z = z;

    // Initialize the best energy
    double best_energy = energy;

    // Initialize the temperature
    double temperature = INITIAL_TEMPERATURE;

    // Iterate over the specified number of iterations
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        // Generate a neighbor solution
        double new_x = x;
        double new_y = y;
        double new_z = z;
        generate_neighbor(new_x, new_y, new_z);

        // Calculate the energy of the neighbor solution
        double new_energy = calculate_energy(new_x, new_y, new_z);

        // Calculate the energy difference
        double delta_energy = new_energy - energy;

        // If the neighbor solution is better, accept it
        if (delta_energy > 0 || exp(delta_energy / temperature) > dis(gen))
        {
            x = new_x;
            y = new
