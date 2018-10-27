#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
string a, b;
string rep[26];
int k;
bool ans;

void dfs(int x, int y) {
    // cout << "x = " << x << " y = " << y << endl;
    if (ans) return;
    if (x == a.size()) {
        if (y == b.size()) {
            ans = true;
        }
        return;
    }
    if (b.size() - y < a.size() - x) return;
    for (int i = 1; i <= k; ++i) {
        if (y + i > b.size()) continue;
        string tg = b.substr(y, i);
        if (rep[a[x] - 'a'].size() > 0) {
            if (rep[a[x] - 'a'] != tg) continue;
        }
        rep[a[x] - 'a'] = tg;
        dfs(x + 1, y + i);
        rep[a[x] - 'a'] = "";
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        cin >> k >> a >> b;
        ans = false;
        memset(rep, 0, sizeof(rep));
        dfs(0, 0);
        if (ans) cout << "1\n";
        else cout << "0\n";
    }
    return 0;
}
