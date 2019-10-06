#include <bits/stdc++.h>
using namespace std;
 
string s;
bitset<55> app;
vector<int> ans;
int mx;
 
void dfs(int now) {
    if (now == s.size() && app.count() == mx) {
        for (int i : ans) cout << i << " ";
        cout << endl;
        exit(0);
    }
    int x = s[now] - '0';
    if (!app[x] && x && x <= mx) {
        app[x] = 1;
        ans.push_back(x);
        dfs(now + 1);
        ans.pop_back();
        app[x] = 0;
    }
    if (now + 1 < s.size()) {
        int y = (s[now] - '0') * 10 + (s[now + 1] - '0');
        if (!app[y] && y && y <= mx) {
            app[y] = 1;
            ans.push_back(y);
            dfs(now + 2);
            ans.pop_back();
            app[y] = 0;
        }
    }
}
 
int main() {
#ifdef ONLINE_JUDGE
#define FILENAME "joke"
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
#undef FILENAME
#endif
    cin >> s;
    int len = s.size();
    while (len) {
        ++mx;
        if (mx <= 9) len -= 1;
        else len -= 2;
    }
    dfs(0);
}
