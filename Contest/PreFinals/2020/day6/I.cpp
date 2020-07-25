#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<long long, long long>> seg;
    for (int i = 0; i < n; ++i) {
        long long x, l; cin >> x >> l;
        seg.emplace_back(x, x + l);
    }

    sort(seg.begin(), seg.end());
    
    auto Ok = [&] (long long d) {
        long long nl = 0;
        for (auto &p : seg) {
            if (nl > p.second) return false;
            if (nl < p.first) nl = p.first;
            nl += d;
        }
        return true;
    };

    long long L = 0, R = 3000000000;
    while (L < R) {
        long long M = (L + R + 1) >> 1;
        if (Ok(M)) L = M;
        else R = M - 1;
    }

    cout << L << endl;
}

