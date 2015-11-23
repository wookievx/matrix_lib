#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    size_t a,b;
    cout<<"Podaj współrzędne macierzy: "<<endl;
    cin>>a>>b;
    cout<<"Podaj zawartość macierzy a: "<<endl;
    matrix<int> ma(a,b);
    cout<<ma.dim_m()<<" "<<ma.dim_n()<<endl;
    for (int i=0; i<a; ++i) {
        for (int j=0; j<b; ++j) {
            cin>>ma[i][j];
        }
    }
    cout<<ma+ma<<endl;
    return 0;
}