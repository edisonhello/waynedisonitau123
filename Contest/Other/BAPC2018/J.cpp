#include <bits/stdc++.h>
using namespace std;


int main() {
    double a, b, c, d; 
    cin >> a >> b >> c >> d;
    double s = (a + b + c + d) / 2;
    cout << fixed << setprecision(12);
    cout << sqrt((s - a) * (s - b) * (s - c) * (s - d)) << endl;
}

