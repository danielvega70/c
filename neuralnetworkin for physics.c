using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallController : MonoBehaviour
{
    public float speed;
    public float jumpForce;

    private Rigidbody2D rb;

    // Neural network variables
    private NeuralNetwork neuralNetwork;
    public int numInputs = 4;
    public int numHidden = 10;
    public int numOutputs = 1;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();

        // Initialize neural network
        neuralNetwork = new NeuralNetwork(numInputs, numHidden, numOutputs);
    }

    // Update is called once per frame
    void Update()
    {
        float moveHorizontal = Input.GetAxis("Horizontal");
        float moveVertical = Input.GetAxis("Vertical");

        Vector2 movement = new Vector2(moveHorizontal, moveVertical);
        rb.AddForce(movement * speed);

        // Use neural network to determine jump force
        float[] inputs = new float[numInputs];
        inputs[0] = transform.position.x;
        inputs[1] = transform.position.y;
        inputs[2] = rb.velocity.x;
        inputs[3] = rb.velocity.y;

        float[] outputs = neuralNetwork.FeedForward(inputs);

        if (outputs[0] > 0.5f)
        {
            rb.AddForce(Vector2.up * jumpForce);
        }
    }
}

public class NeuralNetwork
{
    private int numInputs;
    private int numHidden;
    private int numOutputs;

    private float[,] weightsInputToHidden;
    private float[,] weightsHiddenToOutput;

    private float[] hiddenLayer;
    private float[] outputLayer;

    public NeuralNetwork(int numInputs, int numHidden, int numOutputs)
    {
        this.numInputs = numInputs;
        this.numHidden = numHidden;
        this.numOutputs = numOutputs;

        weightsInputToHidden = new float[numInputs, numHidden];
        weightsHiddenToOutput = new float[numHidden, numOutputs];

        // Randomize weights
        for (int i = 0; i < numInputs; i++)
        {
            for (int j = 0; j < numHidden; j++)
            {
                weightsInputToHidden[i, j] = Random.Range(-1f, 1f);
            }
        }

        for (int i = 0; i < numHidden; i++)
        {
            for (int j = 0; j < numOutputs; j++)
            {
                weightsHiddenToOutput[i, j] = Random.Range(-1f, 1f);
            }
        }

        hiddenLayer = new float[numHidden];
        outputLayer = new float[numOutputs];
    }

    public float[] FeedForward(float[] inputs)
    {
        // Calculate hidden layer values
        for (int i = 0; i < numHidden; i++)
        {
            float sum = 0f;

            for (int j = 0; j < numInputs; j++)
            {
                sum += inputs[j] * weightsInputToHidden[j, i];
            }

            hiddenLayer[i] = Sigmoid(sum);
        }

        // Calculate output layer values
        for (int i = 0; i < numOutputs; i++)
        {
            float sum = 0f;

            for (int j = 0; j < numHidden; j++)
            {
                sum += hiddenLayer[j] * weightsHiddenToOutput[j, i];
            }

            outputLayer[i] = Sigmoid(sum);
        }

        return outputLayer;
    }

   
