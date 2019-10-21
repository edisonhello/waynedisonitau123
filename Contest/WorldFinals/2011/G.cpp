#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
 
#define sq(x) ((x) * (x))
 
const double pi = acos(-1);
const int kIter = 30;
 
double meow(const vector<int> &v) {
    int n = v.size();
    // sort(v.begin(), v.end(), greater<int>());
    int v0 = *max_element(v.begin(), v.end());
 
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += v[i];
    if (v0 + v0 >= sum) return 0;
 
    double r = v0 / 2.0;
    double tto = 0;
    for (int i : v) {
        tto += acos((sq(r) * 2 - sq(i)) / (2 * sq(r)));
    }
    
    if (tto >= 2 * pi) { 
        double L = v0 / 2.0, R = v.size() * v0 + 1;
        int it = kIter;
        while (R - L > 1e-6 * L) {
            double M = (L + R) / 2;
            
            double tto = 0;
            for (int i : v) {
                tto += acos((sq(M) * 2 - sq(i)) / (2 * sq(M)));
            }
 
            if (tto >= 2 * pi) L = M;
            else R = M;
        }
 
        double r = L;
        double area = 0;
        for (int i : v) {
            double s = (r + r + i) / 2;
            area += sqrt(s * (s - r) * (s - r) * (s - i));
        }
        return area;
    } else {
        double L = v0 / 2.0, R = v.size() * v0 + 1;
        int it = kIter;
        while (R - L > 1e-6 * L) {
            double M = (L + R) / 2;
 
            double one = acos((sq(M) * 2 - sq(v0)) / (2 * sq(M)));
            double oth = -one;
            for (int i : v) {
                oth += acos((sq(M) * 2 - sq(i)) / (2 * sq(M)));
            }
            if (one > oth) L = M;
            else R = M;
        }
 
        double r = L;
        double area = 0;
        double s = (r + r + v0) / 2;
        area -= sqrt(s * (s - r) * (s - r) * (s - v0)) * 2;
        for (int i : v) {
            double s = (r + r + i) / 2;
            area += sqrt(s * (s - r) * (s - r) * (s - i));
        }
        return area;
    }
}
 
const int kN = 500 + 5;
double dp[kN];
bool ch[kN];
int a[kN];
 
 
int main() {
    int n, tc = 0; 
    while (cin >> n) {
        if (n == 0) break;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) ch[i] = false;
        // sort(a + 1, a + n + 1);
 
        dp[0] = 0.0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            vector<int> v;
            for (int j = i - 1; j >= 0; --j) {
                v.push_back(a[j + 1]);
                if (!ch[j]) {
                    double dd = dp[j] + meow(v);
                    if (dd > dp[i]) {
                        dp[i] = dd;
                        ch[i] = true;
                    }
                }
            }
        }
 
        cout << "Case " << (++tc) << ": ";
        cout << fixed << setprecision(20) << dp[n] << endl;
    }
}
