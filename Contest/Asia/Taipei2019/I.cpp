#include <bits/stdc++.h>
using namespace std;

int givcnt[1005];
int nowcnt[1005];
int n;
vector<vector<int>> ans;
vector<int> cand;

void dfs(int idx, vector<int> &now) {
    if (now.size() > n) return;
    if (now.size() == n) {
        ans.push_back(now);
        return;
    }
    if (idx >= (int)cand.size()) { return; }

    // cout << "dfs " << idx << " now = "; for (int i : now) cout << i << ' '; cout << endl;

    // cout << "try take " << cand[idx] << endl;
    for (int j : now) {
        ++nowcnt[abs(cand[idx] - j)];
    }
    bool ok = 1;
    for (int j : now) {
        if (nowcnt[abs(cand[idx] - j)] > givcnt[abs(cand[idx] - j)]) ok = 0;
        // cout << "ok checking j = " << j << " , ok " << ok << endl;
    }
    if (ok) {
        now.push_back(cand[idx]);
        dfs(idx + 1, now);
        now.pop_back();
    }
    for (int j : now) {
        --nowcnt[abs(cand[idx] - j)];
    }

    dfs(idx + 1, now);

}

int main() {
    cin >> n; 
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int t; cin >> t; 
        ++givcnt[t];
        cand.push_back(t);
    }

    cand.resize(unique(cand.begin(), cand.end()) - cand.begin());

    // cout << "cand: "; for (int i : cand) cout << i << ' '; cout << endl;

    vector<int> now = {0, cand.back()};
    ++nowcnt[cand.back()];
    cand.pop_back();

    dfs(0, now);

    cout << ans.size() << endl;
    for (auto &v : ans) {
        for (int i = 0; i < (int)v.size(); ++i) {
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << '\n';
    }
}
