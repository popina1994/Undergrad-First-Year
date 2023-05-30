#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>

using namespace std;

const int nMax = 20, R2 = 1000;
double pi = 3.141592653589793238462643383279502884197;

double x[nMax][nMax], y[nMax][nMax], tabela[nMax];

void ispis(double a[][nMax]) {
    for (int i = 0; i < nMax; i++) {
        for (int j = 0; j < nMax; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void ispisNiza(double x[], int n) {
    for (int i = 0; i <= n; i ++)
        cout << x[i] << " ";
}

void setTabela(double x[], int &n) {
    ifstream ulaz("ulaz.in");
    int i = 0, time;
    while (ulaz >> time)
        ulaz >> x[i++];
    ulaz.close();
    n = i - 1;
}

void setLastColumnCos(double x[][nMax], double v[], double vamp[], int brVrInt) {
    int brJedn = brVrInt / 2;
    for (int i = 1; i <= brJedn; i ++)
        x[i][brJedn+1] = v[i] + v[brVrInt-i] - 2 * vamp[0];
}

void setLastColumnSin(double x[][nMax], double v[], int brVrInt) {
    int brJedn = brVrInt / 2;
    // radi samo kad je brVrInt paran
    for (int i = 1; i <= brJedn; i ++)
        x[i][brJedn+1] = v[brVrInt-i] - v[i];
}

void solve(double a[][nMax], int n) {
    // i broji vrste koje ostaju
    // j broji vrste koje su u "opticaju"
    // k broji po vrstama
    double koefDonje, koefGornje;
    // pravi trougaonu matricu
    for (int i = 1; i <= n; i++) {
        koefGornje = a[i][i];
        for  (int j = i + 1; j <= n; j++) {
            koefDonje = -a[j][i];
            for (int k = 1; k <= n + 1; k++)
                a[j][k] += a[i][k] * koefDonje / koefGornje;
        }
    }
    // i broji jednacine
    // j broji do jednacina

    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j >= i; j--)
            a[i][j] /= a[i][i];
    // pravi dijagonalu
}

//na glavnoj dijagonali ostaju resenja
void output(double a[][nMax], int n) {
    // i broji x-ove od dna
    // j broji do "x-ova" od desne strane, bez koeficijenata
    for (int i = n; i >= 1; i--) {
        double sum = a[i][n+1];
        for (int j = n; j > i; j --)
            sum -= a[j][j] * a[i][j];
        a[i][i] = sum;
    }
}

void setPhiV(double x[][nMax], double y[][nMax], double v[], double phi [], int n) {
    for (int i = 1; i <= n; i ++) {
        phi[i] = atan(y[i][i] / x[i][i]);
        v[i] = y[i][i] / sin(phi[i]);
        phi[i] = phi[i] / pi * 180;
    }
}

void setV0(double v[], double tabela[], int brVrInt) {
    for (int i = 1; i <= brVrInt; i ++)
        v[0] += tabela[i];
    v[0] /= brVrInt;
}

int main() {
    int m, l, k, n, brVrInt;
    double phi[nMax], v[nMax];
    cout << "unesite koliko hocete da proveravate" << endl;
    cin >> n;
    freopen("izlaz.out", "w", stdout);
    setTabela(tabela, brVrInt);
    int brJedn = brVrInt / 2;
    for (m = 1; m <= n; m ++) {
        memset(x, 0, sizeof(x));
        memset(y, 0, sizeof(y));
        memset(v, 0, sizeof(v));
        memset(phi, 0, sizeof(phi));

        for (l = 1; l <= brJedn; l++)
            for (k = 1; k <= brJedn; k++) {
                x[l][k] = 2 * cos(2 * k * pi * l * m / brVrInt);
                y[l][k] = 2 * sin(2 * k * pi * l * m / brVrInt);
            }
        setV0(v, tabela, brVrInt);
        setLastColumnCos(x, tabela, v, brVrInt);
        setLastColumnSin(y, tabela, brVrInt);
        solve(x, brJedn);
        output(x, brJedn);
        solve(y, brJedn);
        output(y, brJedn);
        setPhiV(x, y, v, phi, brJedn);
        double pEff = v[0] * v[0] / R2;
        for (int i = 1; i <= brJedn; i ++) {
            pEff += (v[i] * v[i] / (2 * R2));
        }
        cout << "m je " << m << endl;
        for (int i = 0; i <= brJedn; i++)
            cout << "V_" << i << " = " << v[i] << " ";
        cout << endl;
        for (int i = 0; i <= brJedn; i++)
            cout << "phi_" << i << " = " << phi[i] << " ";
        cout << endl;
        cout << "snaga na R2 je " << pEff << endl;

    }
    return 0;
}
