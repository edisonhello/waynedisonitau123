#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
int t[maxn], w[maxn];
long long s[4][maxn];
vector<int> v[4];

int main() {
    int n, a, b; scanf("%d%d%d", &n, &a, &b);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &t[i], &w[i]);
        v[t[i]].push_back(i);
    }

    for (int i = 1; i <= 3; ++i) {
        sort(v[i].begin(), v[i].end(), [&](int x, int y) {
            return w[x] < w[y];
        });
    }

    for (int j = 1; j <= 3; ++j) {
        for (int i = 1; i <= (int)v[j].size(); ++i)
            s[j][i] = s[j][i - 1] + w[v[j][i - 1]];
    }

    long long ans = 1e18;
    int fc = 0, fi = -1, fj = -1;
    for (int i = 0; i <= min(a, (int)v[1].size()); ++i) {
        for (int j = 0; j <= min(b, (int)v[2].size()); ++j) {
            long long sum = s[1][i] + s[2][j];
            int k = a + b - i - j;
            if (k <= (int)v[3].size()) {
                long long tans = sum + s[3][k];
                int cnt = a + b;
                if (cnt > fc || cnt == fc && tans < ans) {
                    fc = cnt;
                    ans = tans;
                    fi = i, fj = j;
                }
            } else {
                long long tans = sum + s[3][(int)v[3].size()];
                int cnt = i + j + (int)v[3].size();
                if (cnt > fc || cnt == fc && tans < ans) {
                    fc = cnt;
                    ans = tans;
                    fi = i, fj = j;
                }
            }
        }
    }
    printf("%d %lld\n", fc, ans);
    int z = min(a - fi, fc - fi - fj);
    int x = 0, y = 0, left = fc - fi - fj;
    for (int i = 0; i < fi; ++i)
        printf("%d %d\n", v[1][i] + 1, ++x);
    for (int i = 0; i < min(a - fi, fc - fi - fj); ++i)
        printf("%d %d\n", v[3][i] + 1, ++x), --left;
    for (int i = 0; i < fj; ++i) 
        printf("%d %d\n", v[2][i] + 1, ++y + a);
    for (int i = z, j = 0; j < left; ++i, ++j)
        printf("%d %d\n", v[3][i] + 1, ++y + a);
}
