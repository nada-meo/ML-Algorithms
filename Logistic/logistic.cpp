#include<bits/stdc++.h> // header file for all c++ libraries
#include<vector>

using namespace std;   // stdout library for printing values 
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

int main()
{
//Intialization Phase
double x1[] = {2.7810836, 1.465489372, 3.396561688, 1.38807019, 3.06407232,7.627531214,5.332441248,6.922596716,8.675418651 ,7.673756466};                          
double x2[] = {2.550537003,2.362125076,4.400293529,1.850220317,3.005305973,2.759262235,2.088626775,1.77106367,-0.2420686549,3.508563011};
double y[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};


    //ifstream fichier("/Users/aboulfathnaslouby/Downloads/binary.csv");
    string ligne;
    istringstream s(ligne);
    string g ="";

    int i=0;
    std::vector<std::string>   result;
  //  vector<double> y, x1, x2, x3;

  
  /* while(getline(fichier, ligne, ',')) //Tant qu'on n'est pas à la fin, on lit
    {
  
        result.push_back(ligne);*/
        //getline(fichier, ligne);
    
    // This checks for a trailing comma with no data after it.
       /* if (!fichier && ligne.empty())
        {
        // If there was a trailing comma then add an empty element.
            result.push_back("");}*/
    
   /* 
        
        i++;
    }

  
    for (i=4;i<=1600;i++){
        if (i%4 == 0){
            y.push_back(atof(result[i].c_str()));
        }
        if (i%4 == 1){
            x1.push_back(atof(result[i].c_str()));
        }
        if (i%4 == 2){
            x2.push_back(atof(result[i].c_str()));
        }
        if (i%4 == 3){
            x3.push_back(atof(result[i].c_str()));
        }
    }*/

    /*for(i=0;i<200;i++){
       cout << x2[i]<< endl;
    }*/
        
    

vector<double>error; // for storing the error values
double err;    // for calculating error on each stage
double b0 = 0; // initializing b0
double b1 = 0; // initializing b1
double b2=  0; // initializing b2
double alpha = 0.01; // initializing our learning rate
double  e = 2.71828;
double d ;
double s0, s1, s2;
  
/*Training Phase*/
do{
    s0 = 0; 
    s1 = 0;
    s2 = 0;
    for (int idx = 0; idx<10; idx++){
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

} while(d > 0.1);

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
}


/*
double x2[]={3.61,3.67,4,3.19,2.93,3,2.98,3.08,3.39,3.92};
    double x1[]={
380,
660,
800,
640,
520,
760,
560,
400,
540,
700,
800};
double  y[]={
0,
1,
1,
1,
0,
1,
1,
0,
1,
0,
0};


double	X2[]	={
	2.550537003	,
	2.362125076	,
    4.400293529	,
	1.850220317	,
	3.005305973	,
	2.759262235	,
	2.088626775	,
	1.77106367	,
	-0.242068655,	
	3.508563011	, };*/