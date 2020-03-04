#include <bits/stdc++.h>
using namespace std;

const int kN = 1000;
const int kMagic = 2;
const int kDist = 10;
int n, cnt[kN], a[kN];
vector<int> cd;

void Dfs(int p, int t) {
    if (t == n) {
        for (int i = 0; i < n; ++i) printf("%d ", a[i]);
        puts("");
        return;
    }
    if (p >= cd.size()) return;
    bool ok = true;
    for (int i = 0; i < t; ++i) {
        if (--cnt[abs(cd[p] - a[i])] < 0) ok = false;
    }
    if (ok) {
        a[t] = cd[p];
        Dfs(p + 1, t + 1);
    }
    for (int i = 0; i < t; ++i) ++cnt[abs(cd[p] - a[i])];
    int cc = 0;
    for (int i = p + 1; i < cd.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < t; ++j) {
            if (--cnt[abs(cd[i] - a[j])] < 0) ok = false;
        }
        if (ok) {
            a[t] = cd[i];
            Dfs(i + 1, t + 1);
            ++cc;
        }
        for (int j = 0; j < t; ++j) {
            ++cnt[abs(cd[i] - a[j])];
        }
        if (cc >= kMagic) break;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int t; scanf("%d", &t);
        cnt[t]++;
        cd.push_back(t);
    }
    cd.resize(unique(cd.begin(), cd.end()) - cd.begin());
    // reverse(cd.begin(), cd.end());
    a[0] = 0;
    Dfs(0, 1);
}
