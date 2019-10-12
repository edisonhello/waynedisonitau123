#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int ed[maxn][maxn], a[maxn], deg[maxn];
vector<int> euler;

void dfs(int x, int k) {
    for (int i = 0; i < k; ++i) {
        if (ed[x][i] > 0) {
            --ed[x][i];
            --ed[i][x];
            dfs(i, k);
        }
    }
    euler.push_back(x);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("achromatic.in", "r", stdin);
    freopen("achromatic.out", "w", stdout);
#endif
    int n; scanf("%d", &n);
    int kz = -1;
    for (int k = 2; ; ++k) {
        int need = (k & 1) ? k * (k - 1) / 2 : k * (k - 1) / 2 + k / 2;
        if (need > n) break;

        if (need <= n) {
            int edge = 0;
            for (int i = 0; i < k; ++i) deg[i] = 0;
            for (int i = 0; i < k; ++i) {
                for (int j = i + 1; j < k; ++j) {
                    ed[i][j] = 1;
                    ed[j][i] = 1;
                    edge++;
                }
            }
            if (k % 2 == 0) {
                for (int i = 0; i < k; i += 2) {
                    ed[i][i + 1] += 1;
                    ed[i + 1][i] += 1;
                    edge++;
                }
            }
            bool fl = false;
            if ((n - edge) % 2 == 0) {
                ed[0][1] += (n - edge);
                ed[1][0] += (n - edge);
            } else {
                if ((n - edge) == 1) {
                    if (k & 1) fl = true;
                    else {
                        if (k < 4) fl = true;
                        else {
                            ed[2][3]--;
                            ed[3][2]--;
                            ed[1][2]++;
                            ed[2][1]++;
                            ed[1][3]++;
                            ed[3][1]++;
                        }
                    }
                }
                else if (k < 3) fl = true;
                else {
                    ed[0][1]++, ed[1][0]++;
                    ed[0][2]++, ed[2][0]++;
                    ed[1][2]++, ed[2][1]++;
                    edge += 3;
                    ed[0][1] += (n - edge);
                    ed[1][0] += (n - edge);
                }
            }
            if (fl) continue;
            euler.clear();
            dfs(0, k);
            kz = k;
        }
    }

    printf("%d\n", kz);
    for (int i = 0; i < n; ++i)
        printf("%d ", euler[i] + 1);
    puts("");
}
