#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

const int nMax =14;

double t[nMax], v[nMax], v0;
int n;

int main() {
    ifstream ulaz("ulaz.in");
    int i = 0;

    while(!(ulaz.eof())) {
        ulaz >> t[i] >> v[i];
        cout << "t" << t[i] << "v" << v[i] << endl;
        i ++;
    }
    n = i;
    ulaz.close();
    v0 = 0;
    // odredjuje jednosmernu komponentu
    for (i = 0; i < n; i ++) {
        v0 += v[i];
        cout << v0 << endl;
    }
    cout << (v0 - v[n-1]);
    return 0;
}
