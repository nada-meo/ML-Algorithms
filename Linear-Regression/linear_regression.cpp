#include <iostream>
#include <cmath>
#include "linear_regression.h"
#include <vector>
#include <fstream>


using namespace std;


double LinearRegression::array_sum(double arr[], int len) {
    double s = 0;

    for (int i = 0; i < len; ++i) {
        s += arr[i];
    }

    return s;
    }



double *LinearRegression::array_pow(double arr[], int len, int power) {
    double *arr2 = new double[len];

    for (int i = 0; i < len; ++i) {
        arr2[i] = pow(arr[i], power);
    }

    return arr2;
}

double *LinearRegression::array_multiplication(double arr1[], double arr2[], int len) {
    double *arr = new double[len];

    for (int i = 0; i < len; ++i) {
        arr[i] = arr1[i] * arr2[i];
    }

    return arr;
}

double *LinearRegression::array_diff(double arr1[], double arr2[], int len) {
    double *arr = new double[len];

    for (int i = 0; i < len; ++i) {
        arr[i] = arr1[i] - arr2[i];
    }

    return arr;
}





LinearRegression::LinearRegression(double x[], double y[], int m) {
    this->x = x;
    this->y = y;
    this->m = m;
    }

double *LinearRegression::train(double alpha) {
    //double *J = new double[2];
    this->theta = gradient_descent(x, y, alpha , m);

    /*cout << "J = ";
    for (int i = 0; i < iterations; ++i) {
        cout << J[i] << ' ';
    }*/
    cout << endl << "Theta: " << theta[0] << " " << theta[1] << endl;
    return theta;
}


double LinearRegression::predict(double x) {
    return h(x, theta);
}

double LinearRegression::compute_cost(double x[], double y[], double theta[], int m) {
    double *predictions = calculate_predictions(x, theta, m);
    double *diff = array_diff(predictions, y, m);
    double *sq_errors = array_pow(diff, m, 2);
    return (1.0 / (2 * m)) * array_sum(sq_errors, m);
}

double LinearRegression::h(double x, double theta[]) {
    return theta[0] + theta[1] * x;
}

double *LinearRegression::calculate_predictions(double x[], double theta[], int m) {
    double *predictions = new double[m];

    // calculate h for each training example
    for (int i = 0; i < m; ++i) {
        predictions[i] = h(x[i], theta);
    }

    return predictions;
}







double LinearRegression::norme(double x, double y) {
    return sqrt( pow(x,2) + pow(y,2) );
 
}



double *LinearRegression::gradient_descent(double x[], double y[], double alpha, int m) {
    double *theta = new double[2];
    theta[0] = 1;
    theta[1] = 1;
    double *errors_x1;
    double *errors_x2;
    double n;
    int iteration=0;

    do {
        
        double *predictions = calculate_predictions(x, theta, m);
        double *diff = array_diff(predictions, y, m);


        errors_x1 = diff;
        errors_x2 = array_multiplication(diff, x, m);

        theta[0] = theta[0] - alpha * (1.0 / m) * array_sum(errors_x1, m);
        theta[1] = theta[1] - alpha * (1.0 / m) * array_sum(errors_x2, m);
       // cout << (1.0 / m) * array_sum(errors_x1, m) <<endl;
       // cout << (1.0 / m) * array_sum(errors_x2, m) << endl;

        //J[i] = compute_cost(x, y, theta, m);

        cout << array_sum(errors_x1, m) << endl;
         cout << array_sum(errors_x2, m) << endl;
        
        n = norme((1.0 / m) * array_sum(errors_x1, m) , (1.0 / m) * array_sum(errors_x2, m));

        cout << n << "\n";
        iteration++;

    } while ( n > 0.01 );
    
    //cout << theta[0] << "\n" << theta[1] << "\n";


    return theta;
}

/*double *LinearRegression::gradient_descent(double x[], double y[], double alpha, int iters, double *J, int m) {
    double *theta = new double[2];
    theta[0] = 1;
    theta[1] = 1;

    for (int i = 0; i < iters; ++i) {
        double *predictions = calculate_predictions(x, theta, m);
        double *diff = array_diff(predictions, y, m);

        double *errors_x1 = diff;
        double *errors_x2 = array_multiplication(diff, x, m);

        theta[0] = theta[0] - alpha * (1.0 / m) * array_sum(errors_x1, m);
        theta[1] = theta[1] - alpha * (1.0 / m) * array_sum(errors_x2, m);

        J[i] = compute_cost(x, y, theta, m);
    }

    return theta;
}*/



/*void chirps_vs_temp() {
    double chirps[] = {20, 16, 20, 18, 17, 16, 15, 17, 15, 16, 15, 17, 16, 17, 14};
    double temperatures[] = {89, 72, 93, 84, 81, 75, 70, 82, 69, 83, 80, 83, 81, 84, 76};

    LinearRegression lr(chirps, temperatures, 15);*/

   
    /*cout << "Enter number of iterations (default: 1500): ";
    int iterations;
    cin >> iterations;*/

    /*cout << "Training model..." << endl;
    lr.train(alpha);

    cout << "Model has been trained, enter number of chirps: ";
    double x;
    cin >> x;

    double temperature = lr.predict(x);
    cout << "Estimated temperature: " << temperature << " F" << endl;
}*/





/*void sand_vs_slope() {
    double diameter[] = {0.17, 0.19, 0.22, 0.235, 0.235, 0.3, 0.35, 0.42, 0.85};
    double slope[] = {0.63, 0.7, 0.82, 0.88, 1.15, 1.5, 4.4, 7.3, 11.3};

    LinearRegression lr(diameter, slope, 9);

    
    double alpha =0.01;
    

    cout << "Training model..." << endl;
    lr.train(alpha);


}*/



int main() {
    
    double diameter[] = {0.17, 0.19, 0.22, 0.235, 0.235, 0.3, 0.35, 0.42, 0.85};
    double slope[] = {0.63, 0.7, 0.82, 0.88, 1.15, 1.5, 4.4, 7.3, 11.3};


  /* double diameter[]={24,
50,
15,
38,
87,
36,
12,
81,
25,



}
;
double slope[]={21.54945196,
47.46446305,
17.21865634,
36.58639803,
87.28898389,
32.46387493,
10.78089683,
80.7633986,
24.61215147,


};*/




   LinearRegression lr(diameter, slope, 9);

    
   double alpha =0.01;
    lr.train(alpha);

    /*cout << "Training model..." << endl;
    

    std::ofstream file("linear.csv");
    
    //file << "x" ; "y" ; "w" ;
    file << "x" << "," << "y" << "," <<  "w" << std::endl;
    int a = 

    for (int k = 0; k < 9; k++){
        for(int j=0; j<3; j++){
            if(a<8){
                if(a<2){
                    file << diameter[k] << ","<< slope[a] <<"," <<  theta[j] << std::endl;
                    a++;
                    }
                else
                {
                    file << x[k][j] << ","<< y[a] <<"," << std::endl;
                    a++;
                }
                
            }
            else
            {
               file << x[k][j] <<  std::endl;
            }   
        }
    }*/

    //file.close();

   

    /*cout << endl << endl;
    ifstream fichier("/Users/aboulfathnaslouby/train.xlsx");
    string ligne;
    double diameter[50];
    double slope[50];


    int i=0;

    while(getline(fichier, ligne, ',')) //Tant qu'on n'est pas à la fin, on lit
    {
        // cout << ligne << endl;
        diameter[i]=atof(ligne.c_str());
        getline(fichier, ligne);
        //cout << ligne << endl;
        slope[i]=atof(ligne.c_str());
        i++;

    }*/

    /*for (i=0;i<50;i++){
        cout << diameter[i] << "\n";
        cout<< slope[i] << endl;
    }*/

    /*LinearRegression lr(diameter, slope, 50);
    double alpha =0.01;
    

    cout << "Training model..." << endl;
    lr.train(alpha);*/

    /*double chirps[] = {20, 16, 20, 18, 17, 16, 15, 17, 15, 16, 15, 17, 16, 17, 14};
    double temperatures[] = {89, 72, 93, 84, 81, 75, 70, 82, 69, 83, 80, 83, 81, 84, 76};*/


   /* double fires[] = {6.2, 9.5, 10.5, 7.7, 8.6, 34.1, 11, 6.9, 7.3, 15.1, 29.1, 2.2, 5.7, 2, 2.5, 4, 5.4, 2.2, 7.2,
                      15.1, 16.5, 18.4, 36.2, 39.7, 18.5, 23.3, 12.2, 5.6, 21.8, 21.6, 9, 3.6, 5, 28.6, 17.4, 11.3, 3.4,
                      11.9, 10.5, 10.7, 10.8, 4.8};
    double theft[] = {29, 44, 36, 37, 53, 68, 75, 18, 31, 25, 34, 14, 11, 11, 22, 16, 27, 9, 29, 30, 40, 32, 41, 147,
                      22, 29, 46, 23, 4, 31, 39, 15, 32, 27, 32, 34, 17, 46, 42, 43, 34, 19};

    LinearRegression lr(fires, theft, 42);

    
    double alpha = 0.01;
    

    cout << "Training model..." << endl;
    lr.train(alpha);*/
   


    return 0;
}

