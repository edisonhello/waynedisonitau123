#include <bits/stdc++.h>
using namespace std;
#define double long double

double pw(double b, int n, double a = 1) {
    while (n) {
        if (n & 1) a = a * b;
        b = b * b; n >>= 1;
    } return a;
}

int main() {
    long long n, k; cin >> n >> k;
    double fk = (double)(k + 1) / 2;
    long long now = 1;
    if (n < 1000000) {
        while (now < n) {
            ++now;
            fk = floor(fk) / k * fk + ((k - floor(fk)) * (k + floor(fk) + 1)) / (2 * k);
        }
        cout << fixed << setprecision(20) << fk << endl;
        exit(0);
    } while (now < 10000) {
        ++now;
        fk = floor(fk) / k * fk + ((k - floor(fk)) * (k + floor(fk) + 1)) / (2 * k);
        // cout << "now = " << now << " fk = " << fk << endl;
        if (abs(fk - k) < 1e-10) {
            cout << k << endl;
            exit(0);
        }
    } while (true) {
        auto fast = [&](long long nn) -> double {
            // cout << "calc fast = " << nn << " ";
            double a = floor(fk) / k;
            double b = (k - floor(fk)) * (k + floor(fk) + 1) / (2 * k);
            // cout << " , a = " << a << " , b = " << b;
            double nfk = pw(a, nn - now) * (fk + b / (a - 1)) - b / (a - 1);
            // cout << " is " << nfk << endl;
            return nfk;
        };
        // cout << "now fk = " << fk << endl;
        long long L = now + 1, R = n;
        while (L < R) {
            long long M = (L + R + 1) >> 1;
            if (floor(fast(M)) > floor(fk)) R = M - 1;
            else L = M;
        }
        // cout << "new L = " << L << " , new fk = " << fast(L) << endl;
        if (n <= L) {
            cout << fixed << setprecision(20) << fast(n) << endl;
            break;
        } else {
            fk = fast(L);
            now = L;
            if (abs(fk - k) < 1e-10) {
                cout << k << endl;
                exit(0);
            }
        }
    }
}
