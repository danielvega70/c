using Accord.MachineLearning;
using Accord.Math;

// Define the training data
double[][] inputs =
{
    new double[] { 0, 0 },
    new double[] { 0, 1 },
    new double[] { 1, 0 },
    new double[] { 1, 1 }
};

int[] outputs = { 0, 1, 1, 0 };

// Create the machine learning model
var teacher = new Accord.Neuro.Learning.BackPropagationLearning(new Accord.Neuro.ActivationFunctions.SigmoidFunction());
var network = new Accord.Neuro.NeuralNetwork(2, 2, 1);
teacher.Learn(network, inputs, outputs);

// Use the model to make predictions
double[] prediction = network.Compute(new double[] { 0, 1 });

// Output the prediction
Console.WriteLine(prediction[0]);
