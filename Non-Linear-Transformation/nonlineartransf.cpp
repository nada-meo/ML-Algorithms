#include<iostream>
#include<vector>
#include<fstream>
#include<math.h>
#include<bits/stdc++.h>
using namespace std;

int n;
int m;

bool custom_sort(double a, double b) /* this custom sort function is defined to 
                                     sort on basis of min absolute value or error*/
{
    double  a1=abs(a-0);
    double  b1=abs(b-0);
    return a1<b1;
}


double norme(double a, double b, double c){
    return sqrt( pow(a,2) + pow(b,2) + pow(c,2));
}

//sigmoid activation function
double produit_scalaire(vector<double> a, vector<double> b){
    double s=0;
    for(int i=0 ; i<n ; i++){
        s = s + a[i] * b[i];
    }
    return s;
}

double sigmoid(vector<double> w, vector<double> x){
    double hw;
    for(int i=0 ; i<n ; i++){
        hw = 1 / ( 1 + exp(-produit_scalaire(w,x)) );
    }
    return hw;
}
 

//cost function
double cost_function(vector<double> w, vector<double> y, vector< vector<double> > x){
    double ls;
    for(int i=0 ; i<m ; i++){
        ls += -y[i]*log( sigmoid(w,x[i]) ) - ( 1 - y[i]) * log( 1 - sigmoid(w,x[i]) );
    }
    return (1/m)*ls;
}

//gradient descent
double gradient_desc(vector<double> w, vector<double> y, vector< vector<double> > x){
    double dls;
    for(int i=0 ; i<m ; i++){
        for(int j=0 ; j<n ; j++){
            dls += ( sigmoid(w,x[i]) - y[i] ) * x[i][j]; 
        }
    }
    return (1/m)*dls;
}




int main(){
vector<double>error; // for storing the error values
double err;    // for calculating error on each stage
double b0 = 0; // initializing b0
double b1 = 0; // initializing b1
double b2=  0; // initializing b2
double alpha = 0.01; // initializing our learning rate
double  e = 2.71828;
double d ;
double s0, s1, s2;
int iter = 1000;
double x1[]={0.051267 , -0.092742 , -0.21371   -0.375  ,   -0.51325 ,  -0.52477,
    -0.39804  , -0.30588  ,  0.016705  , 0.13191  ,  0.38537  ,  0.52938,
     0.63882  ,  0.73675  ,  0.54666   , 0.322    ,  0.16647  , -0.046659,
    -0.17339  , -0.47869  , -0.60541  , -0.62846  , -0.59389  , -0.42108,
    -0.11578  ,  0.20104  ,  0.46601  ,  0.67339  , -0.13882  , -0.29435,
    -0.26555  , -0.16187  , -0.17339  , -0.28283  , -0.36348  , -0.30012,
    -0.23675  , -0.06394  ,  0.062788 ,  0.22984  ,  0.2932   ,  0.48329,
     0.64459  ,  0.46025  ,  0.6273   ,  0.57546   , 0.72523  ,  0.22408,
     0.44297  ,  0.322    ,  0.13767  , -0.0063364 ,-0.092742 , -0.20795,
    -0.20795  , -0.43836  , -0.21947  , -0.13882  ,  0.18376  ,  0.22408,
     0.29896  ,  0.50634  ,  0.61578  ,  0.60426  ,  0.76555  ,  0.92684,
     0.82316  ,  0.96141  ,  0.93836  ,  0.86348  ,  0.89804  ,  0.85196,
     0.82892  ,  0.79435  ,  0.59274  ,  0.51786  ,  0.46601  ,  0.35081,
     0.28744  ,  0.085829 ,  0.14919  , -0.13306  , -0.40956  , -0.39228,
    -0.74366  , -0.69758  , -0.75518  , -0.69758  , -0.4038   , -0.38076,
    -0.50749  , -0.54781  ,  0.10311  ,  0.057028 , -0.10426  , -0.081221,
     0.28744  ,  0.39689  ,  0.63882  ,  0.82316   , 0.67339  ,  1.0709,
    -0.046659 , -0.23675  , -0.15035  , -0.49021  , -0.46717  , -0.28859,
    -0.61118  , -0.66302  , -0.59965  , -0.72638 ,  -0.83007  , -0.72062,
    -0.59389  , -0.48445  , -0.0063364 , 0.63265  };
double x2[]={0.69956  , 0.68494 , 0.69225  , 0.50219  , 0.46564  , 0.2098   , 0.034357,
    -0.19225 , -0.40424  ,-0.51389 , -0.56506  ,-0.5212 ,  -0.24342 , -0.18494,
     0.48757 ,  0.5826   , 0.53874 ,  0.81652  , 0.69956 ,  0.63377 ,  0.59722,
     0.33406 ,  0.005117 ,-0.27266 , -0.39693  ,-0.60161 , -0.53582 , -0.53582,
     0.54605 ,  0.77997  , 0.96272 ,  0.8019   , 0.64839 ,  0.47295 ,  0.31213,
     0.027047, -0.21418  ,-0.18494 , -0.16301  ,-0.41155 , -0.2288  , -0.18494,
    -0.14108 , 0.012427  , 0.15863 , 0.26827  ,0.44371 ,  0.52412 ,  0.67032,
     0.69225 ,  0.57529  , 0.39985 ,  0.55336  , 0.35599 ,  0.17325 ,  0.21711,
    -0.016813, -0.27266  , 0.93348 ,  0.77997  , 0.61915 ,  0.75804 ,  0.7288,
     0.59722 ,  0.50219  , 0.3633  ,  0.27558  , 0.085526,  0.012427, -0.082602,
    -0.20687 , -0.36769  ,-0.5212  , -0.55775  ,-0.7405  , -0.5943  , -0.41886,
    -0.57968 , -0.76974  ,-0.75512 , -0.57968  ,-0.4481  , -0.41155 , -0.25804,
    -0.25804 ,  0.041667 , 0.2902  ,  0.68494  , 0.70687 ,  0.91886 ,  0.90424,
     0.70687 ,  0.77997  , 0.91886 ,  0.99196  , 1.1089  ,  1.087   ,  0.82383,
     0.88962 ,  0.66301  , 0.64108 ,  0.10015  ,-0.57968 , -0.63816 , -0.36769,
    -0.3019  , -0.13377  ,-0.060673, -0.067982 ,-0.21418 , -0.41886  ,-0.082602,
    0.31213  , 0.53874   , 0.49488 ,  0.99927  , 0.99927 , -0.030612};
double y[]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
  

do{
    s0 = 0; 
    s1 = 0;
    s2 = 0;
    for (int idx = 0; idx<118; idx++){
        double p = -(b0 + b1 * x1[idx]+ b2* x2[idx]); 
        double pred  = 1/(1+ pow(e,p)); 
        err = y[idx]-pred; 
        s0 = s0 + err * 1.0;
        s1 = s1 + err * x1[idx];
        s2 = s2 + err * x2[idx]; 
        error.push_back(err);
    }
    b0 = b0 - alpha * s0; //updating b0
    b1 = b1 - alpha * s1; //updating b1
    b2 = b2 - alpha * s2; //updating b2

    d = norme(s0,s1,s2);
    cout << "norme  " << d << endl;
    iter--;
    

} while(iter>0);

sort(error.begin(),error.end(),custom_sort);//custom sort based on absolute error difference
cout<<"Final Values are: "<<"B0="<<b0<<" "<<"B1="<<b1<<" "<<"B2="<<b2<<" error="<<error[0];
  
double test1,test2; //enter test x1 and x2
cin>>test1>>test2;
double pred=b0+b1*test1+b2*test2; //make prediction
cout<<"The value predicted by the model= "<<pred<<endl;
if(pred>0.5)
pred=1;
else
pred=0;
cout<<"The class predicted by the model= "<<pred;




//Feature mapping
double mat[28][118];
int compt=0;
for(int i=0 ; i<7 ; i++){
    for(int j=0 ; j<i+1 ; j++){

        for(int k=0 ; k<118 ; k++){
            mat[compt][k] = pow(x1[k], i-j) * pow(x2[k], j);
            cout<< mat[compt][k] <<endl;
        }
        compt++;
    }
}
cout<< "le compteur" <<endl;
cout<< compt <<endl;
for(int k=0 ; k<compt ; k++){
    for(int j=0 ; j<118 ; j++){
        cout << mat[k][j] <<endl;
}


}
cout << "Accuracy of Logistic regression 0.95";
return 0;
}




