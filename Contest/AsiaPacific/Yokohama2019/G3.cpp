#include <bits/stdc++.h>
using namespace std;

map<string, int> cnt;
int lmt = 20;
int n;
string s[10005];
int ans;

void dfs(string now) {
    ++cnt[now];
    if (cnt[now] > 1) {
        lmt = min(lmt, (int)now.size());
        ans = 1;
        return;
    }
    if ((int)now.size() >= lmt) return;
    for (int i = 0; i < n; ++i) dfs(now + s[i]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];

    queue<string> q;
    q.push("");

    while (q.size()) {
        string now = q.front(); q.pop();
        ++cnt[now];
        // cerr << "now = " << now << ", cnt = " << cnt[now] << endl;
        if (cnt[now] > 1) {
            lmt = min(lmt, (int)now.size());
            ans = 1;
            continue;
        }
        if ((int)now.size() >= lmt) continue;
        for (int i = 0; i < n; ++i) q.push(now + s[i]);
    }

    // dfs("");


    if (ans) cout << lmt << endl;
    else cout << 0 << endl;
}
