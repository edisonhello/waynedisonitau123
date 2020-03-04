#include <bits/stdc++.h>
using namespace std;

const int maxp = 300 + 5;
const int maxt = 2e5 + 5;
int n[maxp][maxp], P[maxt], R[maxt], l[maxp];

int main() {
    int p, r, t; scanf("%d%d%d", &p, &r, &t);
    for (int i = 0; i < r; ++i) scanf("%d", &l[i]);
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j)
            scanf("%d", &n[i][j]);
    }
    for (int i = 0; i < t; ++i) {
        scanf("%d%d", &P[i], &R[i]);
        --P[i], --R[i];
    }

    auto Deadlock = [&](int z) {
        vector<int> lt(l, l + r);
        vector<vector<int>> nt(p, vector<int>(r, 0));
        vector<vector<int>> tk(p, vector<int>(r, 0));
        vector<int> rel(p, r);
        vector<int> inq(p, 0);
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < r; ++j) {
                nt[i][j] = n[i][j];
                if (nt[i][j] == 0) rel[i]--;
            }
        }
        int fr = 0;
        for (int i = 0; i < z; ++i) {
            --lt[R[i]];
            --nt[P[i]][R[i]];
            ++tk[P[i]][R[i]];
            if (nt[P[i]][R[i]] == 0) --rel[P[i]];
            if (rel[P[i]] == 0) {
                inq[P[i]] = true;
                ++fr;
                for (int j = 0; j < r; ++j) lt[j] += tk[P[i]][j];
            }
        }
        while (fr < p) {
            vector<int> q;
            for (int i = 0; i < p; ++i) {
                if (inq[i]) continue;
                bool ok = true;
                for (int j = 0; j < r; ++j) 
                    ok &= nt[i][j] <= lt[j];
                if (ok) {
                    q.push_back(i);
                    inq[i] = 1;
                }
            }
            if (q.empty()) break;
            for (int u : q) {
                for (int i = 0; i < r; ++i) lt[i] += tk[u][i];
            }
            fr += q.size();
        }
        return fr == p;
    };

    int ans = 0;
    for (int d = 20; d >= 0; --d) {
        if (ans + (1 << d) <= t && Deadlock(ans + (1 << d))) ans += (1 << d);
    }
    if (ans == t) ans = -2;
    printf("%d\n", ans + 1);
    return 0;
}


