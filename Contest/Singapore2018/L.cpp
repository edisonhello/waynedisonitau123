#include<bits/stdc++.h>
using namespace std;

const int maxn = 3e6 + 5;
int dv[maxn];

void sieve() {
    vector<int> p;
    for (int i = 2; i < maxn; ++i) {
        if (!dv[i]) {
            dv[i] = i;
            p.push_back(i);
        }
        for (int j = 0; i * p[j] < maxn; ++j) {
            dv[i * p[j]] = p[j];
            if (i % p[j] == 0) break;
        }
    }
}

int main() {
    sieve();
    int q; scanf("%d", &q);
    while (q--) {
        int x; scanf("%d", &x);
        long long ans = 1, off = 0;
        while (x > 1) {
            int d = dv[x], c = 0;
            while (x % d == 0) ++c, x /= d;
            off += 1;
            ans *= (c + 1);
        }
        printf("%lld\n", ans - off);
    }
}
