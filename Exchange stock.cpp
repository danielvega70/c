#include <iostream>
#include <random>

int main() {
    // Set the probability of a stock increasing to 0.6
    double probability = 0.6;

    // Seed the random number generator with a non-deterministic seed
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    // Generate a random number between 0 and 1
    double r = dis(gen);

    // Determine if the stock will increase or decrease based on the probability
    if (r < probability) {
        std::cout << "The stock is predicted to increase." << std::endl;
    } else {
        std::cout << "The stock is predicted to decrease." << std::endl;
    }

    return 0;
}
