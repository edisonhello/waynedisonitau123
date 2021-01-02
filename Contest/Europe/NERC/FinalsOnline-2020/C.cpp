#include <bits/stdc++.h>
using namespace std;

vector<int> g[25];

vector<int> dfs(int now) {
    if (g[now].empty()) {
        return vector<int>{now};
    }

    vector<vector<int>> chs;
    for (int i : g[now]) chs.push_back(dfs(i));

    vector<int> rt = chs[0];
    for (int i = 1; i < (int)chs.size(); ++i) {
        vector<int> nnow = rt;
        int st = 0;
        for (int j : chs[i]) {
            nnow.push_back(j);
            st ^= 1;
            if (st & 1) {
                for (int i = rt.size() - 1; i >= 0; --i) nnow.push_back(rt[i]);
            } else {
                for (int i : rt) nnow.push_back(i);
            }
        }
        rt.swap(nnow);
    }
    rt.insert(rt.begin(), now);

    return rt;
}

int main() {
    int n; 
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        int p; cin >> p;
        g[p].push_back(i);
    }

    auto ans = dfs(1);

    ans.erase(ans.begin());

    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
}

