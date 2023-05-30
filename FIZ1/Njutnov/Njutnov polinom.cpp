#include <iostream>
#include <cstdio>
using namespace std;
class njutnpolinom1{
    protected:int n;
    protected: double x[20], y[20][20];
    protected: void input(); //unosi x_i, y_i
    protected: void calculatey(); //racuna vrednosti y
    protected: void calculate();
    public: void dothejob();
};
class njutnpolinom2:public njutnpolinom1{
    void calculate();
};
void njutnpolinom1::input(){
    cout << "unesi broj vrednosti funkcije";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << "unesi" << i << "-ti clan\n";
        cin >> x[i];
        cout << "unesi" << i << "-tu vrednost\n";
        cin >> y[0][i];
    }
}

void njutnpolinom1::calculatey(){
    for (int i = 1;i <= n-1;i++) //ide po kolonama
        for (int j = 0; j <= n-i-1;j++){    //ide po vrstama
            y[i][j] = y[i-1][j+1] - y[i-1][j];
        }
}

void njutnpolinom1::calculate(){
    double val, result, quotient;
    result = y[0][0];
    cout << "unesi vrednost u kojoj zelis da izracunas funkciju\n";
    cin >> val;
    quotient = 1;
    for (int i = 1; i < n; i++){
        quotient *= (val - x[i-1])/(i * (x[1]-x[0]));
        result += y[i][0]*quotient;
    }
    cout << "vas rezultat je:" << result << "\n";
}

void njutnpolinom1::dothejob(){
    input();
    calculatey();
    calculate();
}

void njutnpolinom2::calculate(){
double val, result, quotient;
    result = y[0][n-1];
    cout << "unesi vrednost u kojoj zelis da izracunas funkciju\n";
    cin >> val;
    quotient = 1;
    for (int i = 1; i < n; i++){
        quotient *= (val - x[n-i])/(i * (x[1]-x[0]));
        result += y[i][0]*quotient;
    }
    cout << "vas rezultat je: " << result << "\n";
}
int main(){
int n;
njutnpolinom1 p1;
njutnpolinom2 p2;
cout << "unesi vrednost\n1)ako hoces prvi, \n2)ako hoces drugi\n3)ako hoces kraj\n";
cin >> n;
while (n < 3)
    if (n == 1){
        p1.dothejob();
        cin >> n;
    }
    else if (n == 2){
        p2.dothejob();
        cin >> n;
    }
    else if (n == 3) break;

return 0;
}
