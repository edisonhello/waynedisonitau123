#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
char s[maxn];
int cnt[maxn][maxn][2];
bool v[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("blind.in", "r", stdin);
    freopen("blind.out", "w", stdout);
#endif
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= n; ++j) {
            memset(v, false, sizeof(v));
            int x = i;
            vector<int> ord;
            while (!v[x]) {
                v[x] = true;
                ord.push_back(x);
                (x += j) %= n;
            }
            while (true) {
                int v = ord.back();
                ++cnt[i][j][s[v] - '0'];
                ord.pop_back();
                if (v == x) break;
            } 
        }
    }
    for (int i = 1; i <= n; ++i) {
        double ans = 0.0;
        for (int j = 1; j <= min(n, i + i); ++j) {
            vector<double> v;
            double sum = 0;
            int t0 = j, t1 = 0;
            for (int k = 0; k < j; ++k) {
                int all = cnt[k][j][0] + cnt[k][j][1];
                sum += 1.0 * cnt[k][j][0] / all;
                v.push_back(1.0 * (cnt[k][j][1] - cnt[k][j][0]) / all);
            }
            sort(v.begin(), v.end());
            while (t0 > i) {
                sum += v.back();
                v.pop_back();
                --t0, ++t1;
            }
            while (!v.empty() && t1 < i && v.back() > 0) {
                t1++;
                sum += v.back();
                v.pop_back();
            }
            ans = max(ans, sum / j);
        }
        printf("%.20lf\n", ans);
    }
    return 0;
}
