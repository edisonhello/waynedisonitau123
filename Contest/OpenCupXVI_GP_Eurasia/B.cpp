#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 18;
int lt[maxn], rg[maxn];
string s[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int n; cin >> n;
    int m = (1 << n);
    map<string, int> rev;
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
        rev[s[i]] = i;
    }

    string r; cin >> r;
    vector<int> v, w;

    for (int i = 0; i < m; ++i) lt[i] = rg[i] = i;

    for (int i = 0; i < m; ++i)
        v.push_back(i);

    int ptr = 0;
    for (int i = 0; i < (int)r.size(); ++i) {
        int x = v[ptr];
        int y = v[ptr + 1];

        if (r[i] == 'W') {
            w.push_back(x);
            lt[x] = min(lt[x], lt[y]);
            rg[x] = max(rg[x], rg[y]);
        } else {
            w.push_back(y);
            lt[y] = min(lt[x], lt[y]);
            rg[y] = max(rg[x], rg[y]);
        }
        ptr += 2;
        if (ptr >= (int)v.size()) {
            v = w;
            w.clear();
            ptr = 0;
        }
    }

    int q; cin >> q;
    while (q--) {
        string a, b; cin >> a >> b;
        int x = rev[a], y = rev[b];

        if (y >= lt[x] && y <= rg[x]) {
            cout << "Win\n";
        } else if (x >= lt[y] && x <= rg[y]) {
            cout << "Lose\n";
        } else {
            cout << "Unknown\n";
        }
    }
}
