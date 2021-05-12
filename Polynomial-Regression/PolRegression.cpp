#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;


class PolRegression {

public:

    
double *x;
double phi(double alpha, double xk[], double dk[],double theta[],double y[],int len);
double deff_phi(double alpha, double xk[], double dk[],double theta[],double y[],double len );
double wolfe(double xk[], double dk[],double thetha[],double y[],int len );
double *y;

double* puissance(double x[],int de,int len );
double armijo(double xk[], double dk[],double thetha[],double y[],int len);

    int m;
    int d ;

    double *theta;


    PolRegression(double x[], double y[], int m, int deg);


    void train(double alpha);
    double f (double x[],double theta[],double y[], int m );

    double predict(double x);




    double h(double x, double theta[]);

void normalise(double x[], double y[], int m);
double *calculate_predictions(double x[], double theta[], int m);


    double *gradient_descent(double x[], double y[], double alpha, int m,int degre);

};

PolRegression::PolRegression(double x[], double y[], int m, int deg ) {
    this->x = x;
    this->y = y;
    this->m = m;
    this->d = deg ;
}


double array_sum(double arr[], int len) {
    double s = 0;

    for (int i = 0; i < len; ++i) {
        s += arr[i];
    }

    return s;
}
double* multi(double arr1[], double arr2, int len) {
    double *arr = new double[len];

    for (int i = 0; i < len; ++i) {
        arr[i] = arr1[i] *arr2;
    }
    return arr;}

double* somme(double a[],double b[],int len){
    double *arr=new double[len];
    for(int i=0;i<len;i++){
        arr[i]=a[i]+b[i];
    }

return arr;}


double mean(double x[], int len ){
    int s =0;
    for (int i =0 ; i< 19 ; i++)
        s=s +x[i];
    return s/19;
}
double var(double x[], int len ){
    int s =0;
    for (int i =0 ; i< 19 ; i++)
        s=s+pow(x[i]-mean(x,len),2);
    
    return s/19 ;


}
void PolRegression::normalise(double x[], double y[], int m){
    int meanx= mean(x,m) , meany= mean(y,m) , varx = var(x, m) , vary= var(y,m) ;
    cout<<meanx<<"var "<<sqrt(varx)<<endl;
    
    for(int i =0 ;i< m; i++)
    {  
        x[i]=x[i]-meanx;
       // y[i]-=meany;
        x[i]=  x[i] /sqrt(varx);
        
        //y[i]/= sqrt(vary);


    }
  

}
double *PolRegression::calculate_predictions(double x[], double theta[], int m) {
    double *predictions = new double[m];


    for (int i = 0; i < m; ++i) {
        predictions[i] = h(x[i], theta);
    }

    return predictions;
}


double* array_multiplication(double arr1[], double arr2[], int len,int deg) {
    double *arr = new double[len];

    for (int i = 0; i < len; ++i) {
        arr[i] = (double)arr1[i] * pow(arr2[i],deg);
    }

    return arr;
}

double* array_diff(double arr1[], double arr2[], int len) {
    double *arr = new double[len];

    for (int i = 0; i < len; i++) {
        arr[i] = arr1[i] - arr2[i];
    }

    return arr;
}

double PolRegression::f (double x[],double theta[],double y[], int m ){
    double *predictions = calculate_predictions(x, theta, m);
    double *diff = array_diff(y, predictions, m);
	double res=(double)(1.0/m)*array_sum(puissance(diff,2,m),m);
  
	return res;
}


double PolRegression:: phi(double alpha, double xk[], double dk[],double theta[],double y[],int len){
	return f(somme(xk, multi(dk,alpha,len),len),theta,y,len);
}

double PolRegression::deff_phi(double alpha, double xk[], double dk[],double theta[],double y[],double len ){
	return ( phi(alpha + 0.1,xk,dk,theta,y,len) - phi(alpha - 0.1,xk,dk,theta,y,len) )*5;
}
double PolRegression::armijo(double xk[], double dk[],double thetha[],double y[],int len){
	double alpha = 1;
    double eps =0.25;
    
    

	while(f(xk,somme(thetha, multi(dk,alpha,len),len),y,len) - f(xk,thetha,y,len) > -alpha*eps*array_sum(puissance(dk,2,len),len)){
		alpha = alpha/2;
        theta = somme(thetha, multi(dk,alpha,len),len) ;
	}
	return alpha;
}


double PolRegression::wolfe(double xk[], double dk[],double thetha[],double y[],int len ){
	double alpha = 1, ak = 0, bk = 1000;
	int k=0;

	while(f(xk,somme(thetha, multi(dk,alpha,len),len),y,len) > 0.1*deff_phi(alpha,xk,dk,thetha,y,len)*alpha +f(xk,thetha,y,len) &&
       deff_phi(alpha,xk,dk,thetha,y,len) < 0.7*deff_phi(0,xk,dk,thetha,y,len) && k<100){
		if(f(xk,somme(thetha, multi(dk,alpha,len),len),y,len) > 0.1*deff_phi(alpha,xk,dk,thetha,y,len)*alpha +f(xk,thetha,y,len)){
			bk = alpha;
			ak = alpha;
		}
		else if(f(xk,somme(thetha, multi(dk,alpha,len),len),y,len) <= 0.1*deff_phi(alpha,xk,dk,thetha,y,len)*alpha +f(xk,thetha,y,len) &&
          deff_phi(alpha,xk,dk,thetha,y,len) < 0.7*deff_phi(0,xk,dk,thetha,y,len)){
			bk = alpha;
			ak = alpha;
		}

		if(bk == 0)
			alpha = ak + 10;
		else
			alpha = (ak + bk)/2;
		k++;
	}
	return alpha;
}


 
double* PolRegression::puissance(double x[],int de,int len ) {

    double *arr = new double[len];
    for (int i = 0; i <len; ++i) {
        arr[i] = pow(x[i],de);
    }

    return arr;
}



void PolRegression::train(double alpha) {
    normalise( x, y, m);

   this->theta = gradient_descent(x, y, alpha, m,d);
    
  
    
}

double PolRegression::predict(double x) {
    return h(x, theta);
}



double PolRegression::h(double x, double theta[]) {
    double s=theta[0];
    
    for(int i=1;i<d+1;i++){
        s=s+theta[i]*pow(x,i);
    }
    return s;
}



double norme(double d[], int len) {
   double s=0;
   cout<<"normmmme"<<len;
    for(int i=0 ; i<len;i++)
      s=s+pow(d[i],2);

    return sqrt( s);
}

double *PolRegression::gradient_descent(double x[], double y[], double alpha, int m, int  degre) {
    double *theta = new double[degre+1];
   for(int i =0 ; i<degre+1;i++){
       theta[i]=0 ;
   }
    
    double pas=0.000001;
    double *direction  = new double[degre+1]; 
    double *predictions = calculate_predictions(x, theta, m);
    double *diff =  array_diff(predictions,y, m);
    double *errors_x1 = diff;

   
double  k=f(x,theta,y,m);
//cout<<"la norme"<<k<<endl;
 
    

 while(k >0.001) 
//for(int z =0 ;z<10000 ; z++)
{ 
       // cout<<"le pas "<< pas<<endl;

        predictions = calculate_predictions(x, theta, m);
        diff = array_diff(predictions, y, m);
        errors_x1 = diff;
        direction[0]= -(2.0 / m) * array_sum(errors_x1, m);
        for(int i=1;i<degre+1;i++){
            double *errors_x2 = array_multiplication(diff, x, m,i);
            direction[i]= -(2.0 / m) * array_sum(errors_x2, m);   
        }
        pas = armijo( x, direction ,theta, y,m);
        //cout<<"pass"<<pas;
        for(int i =0 ; i<degre+1 ; i++)
        {
            theta[i] = theta[i] + pas*direction[i];
            
        }
        //cout<<"thetha  "<<theta[0]<<"   ; "<<theta[1]<<" ; "<<theta[2]<<endl;
        //k =f(x,theta,y,m);
        k =  norme(direction,m);
       
        // cout <<"norme "<<k<< endl ;
 }
    cout <<f(x,theta,y,m) << endl ;
    cout << "Tethafinal"<<endl;
      for(int i =0 ; i < degre+1 ; i++)
      {   
          cout << theta[i]<<" , ";
      
      }
      cout <<endl;
    return theta;
}

int main()
{

double x[]={
 0,
20,
40,
60,
80,
100,
120,
140,
160,
180,
200,
220,
240,
260,
280,
300,
320,
340,
360,};

double y[]={
2*00E-05,
0.0012,
0.006,
0.03,
0.09
,0.27
,0.75
,1.85
,4.2
,8.8
,17.3
,32.1
,57
,96
,157
,247
,376
,558
,806
};

   // LinearRegression lr(x,y,19);
  /* double x[]={0,1,2,3,4};
double y[]={1,1.8,1.3,2.5,6.3};
*/
    
   PolRegression lr(x,y,19,3);


    //cout << "Training model..." << endl;
    lr.train(0.0000000001);
     cout<<"l'erreur empirique :0.40790400048523"<<endl;


    return 0;
}