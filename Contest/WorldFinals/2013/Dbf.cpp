#include <bits/stdc++.h>
using namespace std;

long long c[100][100];

long long calc(long long k) {
    vector<pair<int, int>> v;
    int tot = 0;
    for (long long i = 2; i * i <= k; ++i) {
        if (k % i == 0) {
            int c = 0;
            while (k % i == 0) {
                ++c;
                ++tot;
                k /= i;
            }
            v.emplace_back(c, i);
        }
    }
    if (k > 1) v.emplace_back(1, k), ++tot;
    long long ans = 1;
    for (auto p : v) {
        ans *= c[tot][p.first];
        tot -= p.first;
    }
    return ans;
}

long long solve(long long n) {
    if (n == 1) return 2;
    for (long long k = 2; k <= 1000; ++k) {
        if (calc(k) == n) return k;
    }
    return LLONG_MAX;
}

int main() {
    c[0][0] = 1;
    for (int i = 1; i < 100; ++i) {
        for (int j = 0; j <= i; ++j) {
            c[i][j] = c[i - 1][j];
            if (j) c[i][j] += c[i - 1][j - 1];
        }
    }

    long long n; while (cin >> n) {
        long long k = solve(n);
        cout << n << ' ' << k << endl;
    }
}
