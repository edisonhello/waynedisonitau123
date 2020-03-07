#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> s(n);
    vector<vector<set<int>>> nd(26, vector<set<int>>(2));
    vector<vector<set<int>>> vd(26, vector<set<int>>(2));
    vector<int> wh;
    vector<int> ch;
    vector<int> sg;
    vector<int> ed(n);
    int sz = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < 4; ++j) {
            char a = s[i][j * 2];
            char b = s[i][j * 2 + 1];
            if (a == '0') continue;
            if (b == '+') {
                ed[i].push_back(sz);
                wh.push_back(i);
                ch.push_back(a - 'A');
                sg.push_back(0);
                nd[a - 'A'][0].insert(sz++);
            } else {
                wh.push_back(i);
                ed[i].push_back(sz);
                ch.push_back(a - 'A');
                sg.push_back(1);
                nd[a - 'A'][1].insert(sz++);
            }
        }
    }
    vector<bool> vis(sz);

    function<void(int, int)> Dfs = [&](int x, int p) {
        vis[x] = true;
        for (int i = 0; i < ed[wh[x]].size(); ++i) {
            if (ed[wh[x]][i] == p) continue;
            if (ed[wh[x][i]] == x) continue;
            if (vis[wh[x][i]]) {
                puts("unbounded");
                exit(0);
            }
            Dfs(ed[wh[x][i]], x);
        }
    };

    for (int i = 0; i < sz; ++i) {
        if (vis[i]) continue;
        Dfs(i, -1);
    }
}
