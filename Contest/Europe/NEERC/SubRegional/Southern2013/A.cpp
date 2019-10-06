#include <bits/stdc++.h>
#define left asd
using namespace std;

const int maxn = 600 + 5;
int t[maxn], a[maxn], b[maxn], c[maxn];
int p[maxn][maxn], q[maxn][maxn], cnt[maxn], z[maxn], x[maxn], take[maxn];
int left[maxn];
vector<vector<int>> segs[maxn];
vector<vector<int>> segss[maxn];
vector<int> v[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d", &t[i], &a[i], &b[i]);
        --t[i];
        v[t[i]].push_back(i);
        c[i] = b[i] - max(a[i], 0);
    }

    for (int i = 0; i < n; ++i) {
        if (v[i].empty()) continue;
        sort(v[i].begin(), v[i].end(), [&](int x, int y) {
            return c[x] > c[y];
        });

        // printf("head = %d\n", v[i][0]);
        p[i][1] = b[v[i][0]];
        for (int j = 1; j < (int)v[i].size(); ++j) {
            if (a[v[i][j]] > 0)
                p[i][1] += a[v[i][j]];
        }
        for (int j = 2; j <= (int)v[i].size(); ++j)
            p[i][j] = p[i][j - 1] + c[v[i][j - 1]];

        // printf("p[%d] = ", i);
        // for (int j = 1; j <= (int)v[i].size(); ++j) printf("%d ", p[i][j]); puts("");
    }

    int ans = -1e9, fi = -1;
    for (int i = 0; i < n; ++i) {
        int f = t[i];
        int sum = b[i];
        for (int j = 0; j < (int)v[f].size(); ++j) {
            if (v[f][j] != i && a[v[f][j]] > 0)
                sum += a[v[f][j]];
        }

        fill(z, z + n, 1);
        z[f] = 2;
        if (sum > ans) {
            fi = i;
            ans = sum;
            for (int j = 0; j < n; ++j) x[j] = z[j];
        }
        int pt = 0;
        for (int seg = 1; ; ++seg) {
            int r = -1e9, ch = -1;
            for (int j = 0; j < n; ++j) {
                if (z[j] > (int)v[j].size()) continue;
                if (j == f) {
                    if (pt < (int)v[f].size() && v[f][pt] == i) ++pt;
                    if (pt < (int)v[f].size()) {
                        if (z[f] * 2 > (seg + 2)) continue;
                        if (c[v[f][pt]] > r) {
                            r = c[v[f][pt]];
                            ch = j;
                        }
                    }
                } else {
                    int cost = p[j][z[j]] - p[j][z[j] - 1];
                    if (z[j] * 2 > seg + 2) continue;
                    if (cost > r) {
                        r = cost;
                        ch = j;
                    }
                }
            }
            if (ch == -1) break;
            sum += r;
            if (f == ch) ++pt;
            ++z[ch];
            if (sum > ans) {
                fi = i;
                ans = sum;
                for (int j = 0; j < n; ++j) x[j] = z[j];
            }
        }
    }
    if (ans <= 0) {
        printf("%d %d\n", 0, 0);
        return 0;
    }
    // printf("ans = %d\n", ans);
    vector<int> vv = {fi}; 
    int f = t[fi];
    for (int j = 0; j < (int)v[f].size(); ++j) {
        if (v[f][j] != fi && a[v[f][j]] > 0)
            vv.push_back(v[f][j]);
    }
    segs[f].push_back(vv);

    // for (int i = 0; i < n; ++i) 
    //    printf("%d ", x[i]);
    // puts("");

    int pt = 0;
    for (int i = 2; i < x[f]; ++i) {
        if (pt < (int)v[f].size() && v[f][pt] == fi) ++pt;
        take[v[f][pt]] = i - 1;
        segs[f].push_back({v[f][pt]});
        pt++;
    }
    // puts("here");
    for (int i = 0; i < n; ++i) {
        if (i == f) continue;
        if (v[i].empty()) continue;
        if (x[i] == 1) continue;
        vector<int> vv = {v[i][0]};
        for (int j = 1; j < (int)v[i].size(); ++j) {
            if (a[v[i][j]] > 0)
                vv.push_back(v[i][j]);
        }
        segs[i].push_back(vv);
        for (int j = 2; j < x[i]; ++j) {
            take[v[i][j - 1]] = j - 1; 
            segs[i].push_back({v[i][j - 1]});
        }
    }
    // puts("here");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)segs[i].size(); ++j) {
            vector<int> vvv;
            for (int k = 0; k < (int)segs[i][j].size(); ++k) {
                if (take[segs[i][j][k]] == j) {
                    // printf("push %d\n", segs[i][j][k]);
                    vvv.push_back(segs[i][j][k]);
                }
            }
            segss[i].push_back(vvv);
        }
    }
    // puts("here");

    vector<int> anss;
    for (int i = 0; i < n; ++i) left[i] = (int)segss[i].size();
    int last = -1;
    while (true) {
        int ch = -1;
        for (int i = 0; i < n; ++i) {
            if (left[i] == 0) continue;
            if (last == i) continue;
            if (ch == -1 || left[i] > left[ch]) ch = i;
        }
        if (ch == -1) break;
        left[ch]--;
        for (int i = 0; i < (int)segss[ch][left[ch]].size(); ++i)
            anss.push_back(segss[ch][left[ch]][i]);
        last = ch;
    }

    printf("%d %d\n", ans, (int)anss.size());
    for (int i = 0; i < (int)anss.size(); ++i) printf("%d ", anss[i] + 1);
    puts("");
    return 0;
}
