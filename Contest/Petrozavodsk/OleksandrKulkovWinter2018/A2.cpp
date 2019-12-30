#include <bits/stdc++.h>
using namespace std;

int f[3];
set<int> to[3], ito[4];

int mex(int a, int b) {
    if (a == 0 || b == 0) {
        if (a == 1 || b == 1) {
            return 2;
        }
        return 1;
    }
    return 0;
}

void solve() {
    {
        for (int i = 0; i < 3; ++i) to[i].clear();
        for (int i = 0; i < 4; ++i) ito[i].clear();
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
            int k = mex(i, j);
            int ii = f[i], jj = f[j];
            int kk = ii ^ jj;
            to[k].insert(kk);
            ito[kk].insert(k);
        }
        bool no = 0;
        for (int i = 0; i < 4; ++i) if (ito[i].size() > 1u) no = 1;
        if (!no) {
            for (int i = 0; i < 3; ++i) cout << f[i] << ' ';
            cout << " use XOR" << endl;
        }
    }
    {
        for (int i = 0; i < 3; ++i) to[i].clear();
        for (int i = 0; i < 4; ++i) ito[i].clear();
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
            int k = mex(i, j);
            int ii = f[i], jj = f[j];
            int kk = ii & jj;
            to[k].insert(kk);
            ito[kk].insert(k);
        }
        bool no = 0;
        for (int i = 0; i < 4; ++i) if (ito[i].size() > 1u) no = 1;
        if (!no) {
            for (int i = 0; i < 3; ++i) cout << f[i] << ' ';
            cout << " use AND" << endl;
        }
    }
    {
        for (int i = 0; i < 3; ++i) to[i].clear();
        for (int i = 0; i < 4; ++i) ito[i].clear();
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
            int k = mex(i, j);
            int ii = f[i], jj = f[j];
            int kk = ii | jj;
            to[k].insert(kk);
            ito[kk].insert(k);
        }
        bool no = 0;
        for (int i = 0; i < 4; ++i) if (ito[i].size() > 1u) no = 1;
        if (!no) {
            for (int i = 0; i < 3; ++i) cout << f[i] << ' ';
            cout << " use OR" << endl;
        }
    }
}

void dfs_map(int now) {
    if (now == 3) {
        solve();
        return;
    }
    for (int i = 0; i < 4; ++i) {
        f[now] = i;
        dfs_map(now + 1);
    }
}

int main() {
    dfs_map(0);
}
