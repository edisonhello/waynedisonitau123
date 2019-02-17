#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int q; cin >> q;
    string s; cin >> s;
    vector<vector<int>> p;
    long long ans = 0;
    string z = "";
    for (int i = 0; i < q; ++i) {
        if (s[i] == '-') {
            z.pop_back();
            ans -= (int)p.back().size();
            p.pop_back();
        } else {
            vector<int> v;
            v.push_back((int)z.size());
            if (!z.empty() && z.back() == s[i]) v.push_back((int)z.size() - 1);
            if (!p.empty()) {
                vector<int> &w = p.back();
                for (int k = 0; k < (int)w.size(); ++k) {
                    if (w[k] > 0 && z[w[k] - 1] == s[i]) 
                        v.push_back(w[k] - 1);
                }
            }
            z += s[i];
            p.push_back(v);
            ans += (int)v.size();
        }
        cout << ans << ' ';
    }
    cout << endl;
}
