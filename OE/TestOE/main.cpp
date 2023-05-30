#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <fstream>

using namespace std;

const int nMax = 10;

int a, b, c;
    char ch;

    double x[nMax][nMax];

void ispis(double a[][nMax], int n) {
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void solve(double a[][nMax], int n) {
    // i broji vrste koje ostaju
    // j broji vrste koje su u "opticaju"
    // k broji po vrstama
    double koefDonje, koefGornje;
    // pravi trougaonu matricu    cout << "prva";
    ispis(a, n);
    for (int i = 1; i <= n; i++) {
        koefGornje = a[i][i];
        for  (int j = i + 1; j <= n; j++) {
            koefDonje = -a[j][i];
            for (int k = 1; k <= n + 1; k++)
                a[j][k] += a[i][k] * koefDonje / koefGornje;
        }
    }
    ispis(a, n);
    // i broji jednacine
    // j broji do jednacina

    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j >= i; j--)
            a[i][j] /= a[i][i];
    // pravi dijagonalu
    ispis(a, n);
}

void output(double a[][nMax], int n) {
    // i broji x-ove od dna
    // j broji do "x-ova" od desne strane, bez koeficijenata
    for (int i = n; i >= 1; i--) {
        double sum = a[i][n+1];
        for (int j = n; j > i; j --)
            sum -= a[j][j] * a[i][j];
        a[i][i] = sum;
    }
    for (int i = 1; i <= n; i ++)
        printf("%.3lf\n", a[i][i]);
}


int main() {
    int n;
    ifstream ulaz("test.in");
    ulaz >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j ++) {
            ulaz >> x[i][j];
            cout << x[i][j];
        }
    ulaz.close();
    ispis(x, n);
    solve(x, n);
    output(x, n);
    return 0;
}
