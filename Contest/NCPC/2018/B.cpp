#include <bits/stdc++.h>
using namespace std;

vector<long long> v;

void init() {
    vector<int> v2, v3;
    for (long long i = 1; i <= 2000000000; i *= 2) v2.push_back(i);
    for (long long i = 1; i <= 2000000000; i *= 3) v3.push_back(i);
    for (int x : v2) {
        for (int y : v3) {
            long long z = x * 1ll * y;
            if (z <= 2000000000) v.push_back(z);
        }
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
}

const long long inf = 2e9 + 1;

bool f(pair<long long, long long> a, pair<long long, long long> b) {
    return a.first * b.second < b.first * a.second;
}

bool eq(pair<long long, long long> a, pair<long long, long long> b) {
    return a.first * b.second == b.first * a.second;
}

int main() {
    int t; scanf("%d", &t);
    init();
    while (t--) {
        int x; scanf("%d", &x);
        pair<long long, long long> ans = make_pair(inf, 1);
        int z = -1;
        for (int i : v) {
            int g = __gcd(x, i);
            pair<long long, long long> r1 = make_pair(x / g, i / g);
            pair<long long, long long> r2 = make_pair(i / g, x / g);
            if (f(r1, r2)) r1 = r2;
            if (f(r1, ans) || eq(r1, ans) && i > z) ans = r1, z = i;
        }
        printf("%d\n", z);
    }
}
