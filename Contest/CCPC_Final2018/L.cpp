#include <bits/stdc++.h>
using namespace std;

vector<int> prime;
bitset<1000006> np;

void init() {
    for (int i = 2; i < 1000000; ++i) {
        if (np[i]) continue;
        prime.push_back(i);
        for (long long j = 1ll * i * i; j < 1000000; j += i) {
            np[j] = 1;
        }
    }
}

bool is_prime(long long x) {
    for (long long p : prime) {
        if (p * p > x) break;
        if (x % p == 0) return 0;
    }
    return 1;
}

void meow(long long n) {
    for (int i : prime) {
        if (i >= n) break;
        for (int j : prime) {
            if (i + j > n) break;
            if (i + j == n) {
                cout << i << " " << j << '\n';
                return;
            }
        }
    }
}

void meow6(long long n) {
    if (n & 1) cout << "2 2 2 3 ", meow(n - 9);
    else cout << "2 2 2 2 ", meow(n - 8);
}

void meow5(long long n) {
    if (n & 1) cout << "2 2 3 ", meow(n - 7);
    else cout << "2 2 2 ", meow(n - 6);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    init();
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        long long n; cin >> n;
        cout << "Case " << T << ": ";
        if (n < 12) { cout << "IMPOSSIBLE" << endl; continue; }
        if (n <= 300) meow6(n);
        else for (long long p = n - 10; ; --p) {
            if (is_prime(p)) {
                cout << p << " ";
                meow5(n - p);
                break;
            }
        }
    }
}
