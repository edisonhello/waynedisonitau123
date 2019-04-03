#include <bits/stdc++.h>
using namespace std;

vector<int> ord;
vector<int> sa, sb;
int n, s, aptr, bptr, aleft[15], bleft[15];

int dfs(int now) {
    if (now == int(ord.size())) return 0;
    int id = ord[now];
    if (id <= n) { // player 1
        int mx = INT_MIN;
        if (aleft[id]) {
            --aleft[id];
            int get = sa[aptr++];
            mx = max(mx, get + dfs(now + 1));
            ++aleft[id];
            --aptr;
        }
        if (bleft[id]) {
            --bleft[id];
            int get = sb[bptr++];
            mx = max(mx, get + dfs(now + 1));
            ++bleft[id];
            --bptr;
        }
        return mx;
    } else {
        int mn = INT_MAX;
        if (aleft[id]) {
            --aleft[id];
            int get = sa[aptr++];
            mn = min(mn, -get + dfs(now + 1));
            ++aleft[id];
            --aptr;
        }
        if (bleft[id]) {
            --bleft[id];
            int get = sb[bptr++];
            mn = min(mn, -get + dfs(now + 1));
            ++bleft[id];
            --bptr;
        }
        return mn;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s;
    for (int i = 0; i < 2 * n * (s + 1); ++i) {
        int t; cin >> t;
        ord.push_back(t);
    }
    int sas; cin >> sas; while (sas--) {
        int t; cin >> t;
        sa.push_back(t);
    }
    int sbs; cin >> sbs; while (sbs--) {
        int t; cin >> t;
        sb.push_back(t);
    }
    sort(sa.begin(), sa.end(), greater<int>());
    sort(sb.begin(), sb.end(), greater<int>());
    sa.resize(2 * n * s);
    sb.resize(2 * n);
    for (int i = 1; i <= 2 * n; ++i) aleft[i] = s, bleft[i] = 1;
    
    cout << dfs(0) << endl;
}
