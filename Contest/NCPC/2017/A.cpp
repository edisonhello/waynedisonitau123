#include <bits/stdc++.h>
using namespace std;

const int maxc = 1e5 + 5;
vector<int> pr;
int dv[maxc];
bool v[maxc];

void sieve() {
    for (int i = 2; i < maxc; ++i) {
        if (!v[i]) pr.push_back(i), dv[i] = i;
        for (int j = 0; i * pr[j] < maxc; ++j) {
            v[i * pr[j]] = true;
            dv[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    sieve();
    int t; cin >> t;
    while (t--) {
        long long n; cin >> n;
        long long ans = n;
        while (true) {
            long long s = 0, k = n;
            ans = n;
            for (int i = 0; i < pr.size() && n >= maxc; ++i) {
                int c = 0;
                while (n % pr[i] == 0) n /= pr[i], ++c;
                if (c > 0) s += pr[i];
            }
            while (n > 1 && n < maxc) {
                int d = dv[n];
                while (n % d == 0) n /= d;
                s += d;
            }
            if (n > 1) s += n;
            if (s == k) break;
            n = s;
        }
        cout << ans << '\n';
    }
}
