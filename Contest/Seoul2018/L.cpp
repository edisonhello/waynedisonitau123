#include <bits/stdc++.h>
using namespace std;

#define left asdasdasd
const int maxn = 2000 + 5;
int d[maxn], wi[maxn], ready[maxn], last[maxn];
int left[maxn];
bool wk[maxn];
vector<int> sc[maxn];

int main() {
    int m, n, w, h;
    scanf("%d%d%d%d", &m, &n, &w, &h);
    for (int i = 0; i < m; ++i) scanf("%d", &wi[i]), left[i] = wi[i] / w;
    for (int i = 1; i <= n; ++i) scanf("%d", &d[i]);
    int work = 0;
    vector<int> v;
    for (int i = 1; i <= n + 1; ++i) {
        vector<int> kp;
        // printf("i = %d\n", i);
        for (int j = 0; j < (int)v.size(); ++j) {
            int x = v[j];
            last[x]++;
            if (last[x] == w) {
                --work;
                ready[x] = i + h;
                wk[x] = false;
                last[x] = 0;
            } else {
                kp.push_back(x);
            }
        }
        if (work > d[i]) {
            puts("-1");
            return 0;
        }
        vector<int> ok;
        for (int j = 0; j < m; ++j) {
            if (wk[j]) continue;
            if (ready[j] <= i && left[j] > 0) ok.push_back(j);
        }
        sort(ok.begin(), ok.end(), [&](int a, int b) { return left[a] > left[b]; });
        for (int j = 0; j < (int)ok.size(); ++j) {
            if (work == d[i]) break;
            int x = ok[j];
            --left[x];
            wk[x] = true;
            last[x] = 0;
            sc[x].push_back(i);
            kp.push_back(x);
            ++work;
        }
        v = kp;
        if (work != d[i]) {
            puts("-1");
            return 0;
        }
    }
   // puts("ga");
    for (int i = 0; i < m; ++i) {
        if (left[i] != 0) {
            puts("-1");
            return 0;
        }
    }
    if (v.size() > 0) {
        puts("-1");
        return 0;
    }
    puts("1");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < (int)sc[i].size(); ++j) printf("%d ", sc[i][j]);
        puts("");
    }
    return 0;
}
