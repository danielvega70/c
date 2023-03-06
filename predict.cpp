#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

class NeuralNetwork {
private:
    int input_dim, hidden_dim, output_dim;
    MatrixXd weights_ih, weights_ho;
    VectorXd bias_h, bias_o;

public:
    NeuralNetwork(int input_dim, int hidden_dim, int output_dim) : 
        input_dim(input_dim), hidden_dim(hidden_dim), output_dim(output_dim) {
        // Initialize weights and biases with random values
        weights_ih = MatrixXd::Random(hidden_dim, input_dim);
        weights_ho = MatrixXd::Random(output_dim, hidden_dim);
        bias_h = VectorXd::Random(hidden_dim);
        bias_o = VectorXd::Random(output_dim);
    }

    VectorXd predict(const VectorXd& input) {
        // Calculate hidden layer
        VectorXd hidden = weights_ih * input + bias_h;
        hidden = (1.0 / (1.0 + exp(-hidden)));

        // Calculate output layer
        VectorXd output = weights_ho * hidden + bias_o;
        output = (1.0 / (1.0 + exp(-output)));

        return output;
    }
};

int main() {
    NeuralNetwork nn(2, 3, 1);

    VectorXd input(2);
    input << 0.1, 0.9;

    VectorXd output = nn.predict(input);

    std::cout << "Output: " << output << std::endl;

    return 0;
}
