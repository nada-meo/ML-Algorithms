#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<double> y;
vector<double> w;
vector< vector<double> > x;
int t_max = 2000;
int n=8;

double produit_scalaire(vector< vector<double> > X, int k,vector<double> b){
    double s=0;
    for(int i=0 ; i<3 ; i++){
        s = s + X[k][i] * b[i];
    }
    if(s>=0)
        return 1;
        else
        return -1;

}






vector<double> adaline(){
    double error;
    int t;

    for (t=1 ; t<=t_max ; t++){
        for(int i =0 ; i<n ; i++){

            double e = y[i] - produit_scalaire(x,i,w);
            if ( e != 0 ){
                w[0] = w[0] + 0.1 * e ;
                w[1] = w[1] + 0.1 * e * x[i][1];
                w[2] = w[2] + 0.1 * e * x[i][2];
            }
        }

    }
    cout << "t  " << t << "\n";
    //error = Ls();
    //cout << "Error   " << error << "\n";
    return w;
}




int main(int argc, const char * agrv[]){
    std::ofstream file("adaline.csv");

    file << "x" << "," << "y" << "," <<  "w" << std::endl;

    x.push_back(vector<double>(3)) ;
    x[0][0]=1 ;
    x[0][1]=-0.22 ;
    x[0][2]=0.51 ;
    y.push_back(1) ;

    x.push_back(vector<double>(3)) ;
    x[1][0]=(1) ;
    x[1][1]=(-0.64) ;
    x[1][2]=(0.37) ;
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
    y.push_back(1) ;

    w.push_back(0) ;
    w.push_back(1) ;
    w.push_back(1);

    /*x.push_back(vector<double>(3)) ;
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


    adaline();

    int a=0;

    cout<<"\n"<<w[0]<<"\n"<<w[1]<<"\n"<<w[2]<<"\n"<<endl;

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
    file.close();

}
