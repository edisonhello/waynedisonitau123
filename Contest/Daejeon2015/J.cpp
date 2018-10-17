#include <bits/stdc++.h>
using namespace std;

const int maxc = 1000 + 5;
bool v[maxc];
int c[maxc];
vector<int> p;

void sieve() {
    for (int i = 2; i < maxc; ++i) {
        if (!v[i]) p.push_back(i);
        for (int j = 0; i * p[j] < maxc; ++j) {
            v[i * p[j]] = true;
            if (i % p[j] == 0) break;
        }
    }
}

int main() {
    sieve();
    for (int i : p) {
        for (int j : p) {
            if (i + j < maxc) c[i + j] = i;
        }
    }
    int t; cin >> t;
    while (t--) {
        int k; cin >> k;
        bool ans = false;
        for (int i = 1; i <= k; ++i) if (c[i]) {
            if (!v[k - i]) {
                vector<int> q = { c[i], i - c[i], k - i };
                sort(q.begin(), q.end());
                cout << q[0] << ' ' << q[1] << ' ' << q[2] << endl;
                ans = true;
                break;
            }
        }
        if (!ans) cout << 0 << endl;
    }
}
