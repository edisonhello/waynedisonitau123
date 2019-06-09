#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int, long long>> v;
    for (int i = 0; i < n; ++i) {
        int a; long long b; cin >> a >> b;
        v.emplace_back(a, b);
    }
    sort(v.begin(), v.end());
    bool ok = true;
    if (n) {
        __int128 sum = 0;
        int I = v.back().first;
        while (I) {
            if (v.size() && v.back().first == I) {
                sum += v.back().second;
                v.pop_back();
            }
            if (sum % I) { ok = false; break; }
            --I;
        }
    }
    if (ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}
