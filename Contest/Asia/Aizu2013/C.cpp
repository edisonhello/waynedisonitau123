#include <bits/stdc++.h>
using namespace std;

const int maxn = 305;
int l[maxn], t[maxn], r[maxn], b[maxn], fa[maxn * maxn];
vector<int> v[maxn][maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    int n; 
    while (scanf("%d", &n) != EOF) {
        if (!n) break;
        vector<int> xds, yds;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d%d", &l[i], &t[i], &r[i], &b[i]);
            xds.push_back(l[i] - 1);
            xds.push_back(l[i]);
            xds.push_back(l[i] + 1);
            xds.push_back(r[i] - 1);
            xds.push_back(r[i]);
            xds.push_back(r[i] + 1);
            yds.push_back(b[i] - 1);
            yds.push_back(b[i]);
            yds.push_back(b[i] + 1);
            yds.push_back(t[i] - 1);
            yds.push_back(t[i]);
            yds.push_back(t[i] + 1);
        }

        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j)
                v[i][j].clear();
        }

        sort(xds.begin(), xds.end());
        sort(yds.begin(), yds.end());
        xds.resize(unique(xds.begin(), xds.end()) - xds.begin());
        yds.resize(unique(yds.begin(), yds.end()) - yds.begin());
        for (int i = 0; i < n; ++i) {
            l[i] = lower_bound(xds.begin(), xds.end(), l[i]) - xds.begin() + 1;
            r[i] = lower_bound(xds.begin(), xds.end(), r[i] - 1) - xds.begin() + 1;
            b[i] = lower_bound(yds.begin(), yds.end(), b[i]) - yds.begin() + 1;
            t[i] = lower_bound(yds.begin(), yds.end(), t[i] - 1) - yds.begin() + 1;
            for (int x = l[i]; x <= r[i]; ++x) {
                for (int y = b[i]; y <= t[i]; ++y)
                    v[x][y].push_back(i);
            }
        }
        for (int i = 0; i < maxn * maxn; ++i) fa[i] = i;
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) {
                if (i > 0 && v[i][j] == v[i - 1][j]) merge(i * maxn + j, (i - 1) * maxn + j);
                if (j > 0 && v[i][j] == v[i][j - 1]) merge(i * maxn + j, i * maxn + (j - 1));
            }
        }
        int ans = 0;
        for (int i = 0; i < maxn * maxn; ++i) ans += find(i) == i;
        printf("%d\n", ans);
    }
    return 0;
}
