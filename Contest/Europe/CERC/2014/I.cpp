#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<pair<char, long long>> v(n);
        long long b = 0, w = 0;
        for (int i = 0; i < n; ++i) {
            cin >> v[i].second >> v[i].first;
            if (v[i].first == 'B') b += v[i].second;
            else w += v[i].second;
        }
        if (b == 0 || w == 0) {
            cout << b + w << '\n';
            continue;
        }
        long long g = __gcd(b, w);
        b /= g, w /= g;
        long long ans = 0;
        long long nb = 0, nw = 0;
        for (auto &p : v) {
            long long nnb = nb, nnw = nw;
            if (p.first == 'B') {
                nnb += p.second;
                if (nw) {
                    if (nw * b % w == 0) {
                        long long qb = nw * b / w;
                        if (nb <= qb && qb <= nnb) {
                            ++ans;
                            nnb -= qb;
                            nnw = 0;
                        }
                    }                    
                }
            } else if (p.first == 'W') {
                nnw += p.second;
                if (nb) {
                    if (nb * w % b == 0) {
                        long long qw = nb * w / b;
                        if (nw <= qw && qw <= nnw) {
                            ++ans;
                            nnw -= qw;
                            nnb = 0;
                        }
                    }
                }
            }
            nb = nnb, nw = nnw;
        }
        cout << ans << '\n';
    }
}
