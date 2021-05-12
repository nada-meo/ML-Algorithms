#include<vector>
using namespace std;

class LinearRegression {

public:

    // First feature
    double *x;

    // Target feature
    double *y;

    // Number of training examples
    int m;

    // The theta coefficients
    double *theta;

    /**
     * Create a new instance from the given data set.
     */
    LinearRegression(double x[], double y[], int m);

    /**
     * Train the model with the supplied parameters.
     *
     *    The number of gradient descent steps to do.
     */
    double *train(double alpha);

    /**
     * Try to predict y, given an x.
     */
    double predict(double x);


    

private:

    /**
     * Compute the cost J.
     */
    static double compute_cost(double x[], double y[], double theta[], int m);

    /**
     * Compute the hypothesis.
     */
    static double h(double x, double theta[]);

    /**
     * Calculate the target feature from the other ones.
     */
    static double *calculate_predictions(double x[], double theta[], int m);

    /**
     * Performs gradient descent to learn theta by taking num_items gradient steps with learning rate alpha.
     */
    static double *gradient_descent(double x[], double y[], double alpha, int m);

    static double norme(double a, double b);



public:
    static double array_sum(double arr[], int len);

    static double *array_pow(double arr[], int len, int power);

    static double *array_multiplication(double arr1[], double arr2[], int len);

    static double *array_diff(double arr1[], double arr2[], int len);

    

};

