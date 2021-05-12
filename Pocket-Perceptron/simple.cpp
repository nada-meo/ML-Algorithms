#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



vector< vector<double> > x;
vector<double> w;
vector<double> y;
vector<double> w_old;
int n = 8;
int t_max = 100;

double produit_scalaire(vector<double> w, vector<double> x){
    double s=0;
    for (int i =0; i<=3 ; i++){
        s = s + w[i]*x[i];
    }
    return s;

}

double Ls(vector<double> w){
    double ls=0;
    for(int i=0 ; i<n ; i++){
        if ( (produit_scalaire(w,x[i]) *y[i]) <0 ){
            ls= ls+1;
        }
    }
    return ls/n;
}


vector<double> perceptron(){
    int t=0;
    double function = Ls(w);
    while (function != 0){
        for(int i=0; i<n; i++){
            if ( ( produit_scalaire(w,x[i]) * y[i]) <0 ){
                w[0] = w[0] + y[i];
                w[1] = w[1] + y[i] * x[i][1];
                w[2] = w[2] + y[i] * x[i][2];
                t = t+1;
            }
        }
        function = Ls(w);   
    }
    cout << "Function " << function << "\n";
    std::cout << "t " << t << "\n";
    return w;   
}




vector<double> pocket(){
    int i, t;

    for(int k=0; k<3; k++){
        w_old.push_back(w[k]);
    }

    for (t = 0 ; t < t_max ; t++)
    {
        for(i=0; i<n; i++){
            if ( ( produit_scalaire(w,x[i]) * y[i]) <0 ){
                w.at(0) = w.at(0) + y[i];               
                w.at(1) = w.at(1) + y[i] * x[i][1];                
                w.at(2) = w.at(2) + y[i] * x[i][2];    
            }
        }
        if (Ls(w) < Ls(w_old)) {
            for(int k=0; k<3; k++){
                w_old[k] = (w[k]);
            }
        }
    }
    std::cout << t << "\n";
    std::cout << Ls(w_old) << "\n";
    return w_old;
}




int main(int argc, const char * agrv[]){
    std::ofstream file("pocket.csv");
    
    //file << "x" ; "y" ; "w" ;
    file << "x" << "," << "y" << "," <<  "w" << std::endl;

    x.push_back(vector<double>(3)) ;
    x[0][0]=1 ;
    x[0][1]=-0.22 ;
    x[0][2]=0.51 ;
    y.push_back(1) ;
 
    x.push_back(vector<double>(3)) ;
    x[1][0]=(1) ;
    x[1][1]=(-0.64) ;
    x[1][2]=(-0.37) ;
    y.push_back(1);


    x.push_back(vector<double>(3)) ;
    x[2][0]=(1) ;
    x[2][1]=(-0.82) ;
    x[2][2]=(-0.16) ;
    y.push_back(1) ;


    x.push_back(vector<double>(3)) ;
    x[3][0]=(1) ;
    x[3][1]=(-0.22) ;
    x[3][2]=(0.04) ;
    y.push_back(1) ;
 
    x.push_back(vector<double>(3)) ;
    x[4][0]=(1) ;
    x[4][1]=(0.47) ;
    x[4][2]=(0.23) ;
    y.push_back(-1) ;

     x.push_back(vector<double>(3)) ;
    x[5][0]=(1) ;
    x[5][1]=(-0.47) ;
    x[5][2]=(-0.84) ;
    y.push_back(-1) ;

    x.push_back(vector<double>(3)) ;
    x[6][0]=(1) ;
    x[6][1]=(0.16) ;
    x[6][2]=-0.62 ;
    y.push_back(-1) ;

    x.push_back(vector<double>(3)) ;
    x[7][0]=(1) ;
    x[7][1]=(0.41) ;
    x[7][2]=-0.25 ;
    y.push_back(-1) ;

    w.push_back(0) ;
    w.push_back(1) ;
    w.push_back(1);

   /* x.push_back(vector<double>(3)) ;
    x[0][0]=1 ;
    x[0][1]=1 ;
    x[0][2]=1 ;
    y.push_back(1) ;

    x.push_back(vector<double>(3)) ;
    x[1][0]=(1) ;
    x[1][1]=(2) ;
    x[1][2]=(1) ;
    y.push_back(1);

    x.push_back(vector<double>(3)) ;
    x[2][0]=(1) ;
    x[2][1]=(2) ;
    x[2][2]=(2) ;
    y.push_back(1) ;

    x.push_back(vector<double>(3)) ;
    x[3][0]=(1) ;
    x[3][1]=(1) ;
    x[3][2]=(3) ;
    y.push_back(1) ;

    x.push_back(vector<double>(3)) ;
    x[4][0]=(1) ;
    x[4][1]=(3) ;
    x[4][2]=(3) ;
    y.push_back(-1) ;

    x.push_back(vector<double>(3)) ;
    x[5][0]=(1) ;
    x[5][1]=(2) ;
    x[5][2]=4 ;
    y.push_back(-1) ;

    x.push_back(vector<double>(3)) ;
    x[6][0]=(1) ;
    x[6][1]=(5) ;
    x[6][2]=-4 ;
    y.push_back(-1) ;

    x.push_back(vector<double>(3)) ;
    x[7][0]=(1) ;
    x[7][1]=(4) ;
    x[7][2]=5 ;
    y.push_back(-1) ;
    
    w.push_back(0) ;
    w.push_back(1) ;
    w.push_back(1);*/


    int a =0;
    

    //perceptron(); 
    pocket();

   for (int k = 0; k < n; k++)
    {
        for(int j=0; j<3; j++){
            if(a<8){
                if(a<3){
                    file << x[k][j] << ","<< y[a] <<"," <<  w[j] << std::endl;
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
    }
    cout<<"vector \n"<<w_old[0]<<" \n"<<w_old[1]<<" \n"<<w_old[2]<<"\n"<<endl;
    //cout<<"\n"<<w[0]<<"\n"<<w[1]<<"\n"<<w[2]<<"\n"<<endl;
    file.close();
}


    