#include <bits/stdc++.h>
using namespace std;

bool isprime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

long long ans[55][55];
long double fans[55][55];

int main() {
#ifdef ONLINE_JUDGE
    freopen("elegant.in", "r", stdin);
    freopen("elegant.out", "w", stdout);
#endif
    vector<int> p, q;
    int X = 2;
    while (p.size() < 30u) {
        ++X;
        if (isprime(X)) p.push_back(X);
    }
    while (q.size() < 30u) {
        ++X;
        if (isprime(X)) q.push_back(X);
    }
    do { ++X; } while (!isprime(X));
    int n; cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        ans[i][j] = 1;
        ans[i][j] *= p[(i + j) % n];
        ans[i][j] *= q[(i - j + n) % n];
    }
    if (n % 2 == 0) {
        if (n % 4 == 0) {
            for (int i = 0; i < n; ++i) {
                if (i & 1) {
                    for (int j = 0; j < (n / 2); ++j) ans[i][j] *= X;
                } else {
                    for (int j = n / 2; j < n; ++j) ans[i][j] *= X;
                }
            }
        } else {
            set<int> st;
            for (int i = 0; i < n / 4; ++i) st.insert(i), st.insert(i + n / 2);
            st.insert(n / 4);
            for (int i = 0; i < n; ++i) {
                if (st.count(i)) {
                    for (int j = 0; j < (n / 2); ++j) ans[i][j] *= X;
                } else {
                    for (int j = n / 2; j < n; ++j) ans[i][j] *= X;
                }
            }
            st.clear();
            do { ++X; } while (!isprime(X));
            for (int i = n / 4; i < n / 2 - 1; ++i) st.insert(i), st.insert(i + n / 2);
            st.insert(n / 2 - 1);
            for (int i = 0; i < n; ++i) {
                if (st.count(i)) {
                    for (int j = 0; j < (n / 2); ++j) ans[i][j] *= X;
                } else {
                    for (int j = n / 2; j < n; ++j) ans[i][j] *= X;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
#ifndef ONLINE_JUDGE
    /* for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) fans[i][j] = log(ans[i][j]);
    for (int i = 0; i < n; ++i) {
        long double rsum = 0, csum = 0;
        for (int j = 0; j < n; ++j) {
            rsum += fans[i][j];
            csum += fans[j][i];
        }
        cerr << rsum << endl << csum << endl;
    } */
#endif
}
