#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
int x[maxn], y[maxn];
double ang[maxn];
long long dp[maxn][maxn][6];
bool in[maxn];

int dot(int x, int y, int a, int b) {
    return x * a + y * b;
}

int cross(int x, int y, int a, int b) {
    return x * b - y * a;
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) 
                dp[i][j][1] = 1;
        }
    }

    for (int p = 2; p <= 5; ++p) {
        for (int i = 0; i < n; ++i) {
            vector<int> v;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    v.push_back(j);
                    ang[j] = atan2(y[i] - y[j], x[i] - x[j]);
                }
            }

            if (p % 2 == 0) {
            } else {
                sort(v.begin(), v.end(), [&](int a, int b) {
                    return ang[a] < ang[b];
                });
            }
            memset(in, false, sizeof(in));

            // printf("i = %d\n", i);

            if (p % 2 == 0) {
                sort(v.begin(), v.end(), [&](int a, int b) {
                    return ang[a] < ang[b];
                });
                // for (int j = 0; j < (int)v.size(); ++j)
                //     printf("%d ", v[j]);
                // puts("");
                long long sum = 0;
                deque<int> dq;
                /* for (int k = (int)v.size() - 1; k > 0; --k) {
                    int j = 0;
                    if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 &&
                        cross(x[v[k]] - x[i], y[v[k]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) < 0) {
                        printf("push k = %d\n", v[k]);
                        sum += dp[i][v[k]][p - 1];
                        in[v[k]] = true;
                        dq.push_back(k);
                    }
                } */
                for (int j = 0, k = 0; j < (int)v.size(); ++j) {
                    // printf("v[j] = %d\n", v[j]);
                    while (!in[v[k]] && (k == j || 
                           dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 &&
                           cross(x[v[k]] - x[i], y[v[k]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) < 0)) {

                        // printf("push k = %d\n", v[k]);
                        sum += dp[i][v[k]][p - 1];
                        in[v[k]] = true;
                        dq.push_back(k);
                        k = (k + 1) % (int)v.size();
                    }
                    while (dq.size()) {
                        if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[dq[0]]] - x[i], y[v[dq[0]]] - y[i]) <= 0 ||
                            cross(x[v[dq[0]]] - x[i], y[v[dq[0]]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) >= 0) {
                            in[v[dq[0]]] = false;
                            sum -= dp[i][v[dq[0]]][p - 1];
                            // printf("pop k = %d\n", v[dq[0]]);
                            dq.pop_front();
                        } else {
                            break;
                        }
                    }
                    // printf("inside: ");
                    // for (int k = 0; k < n; ++k) if (in[k]) printf("%d ", k); puts("");
                    // printf("sum = %lld\n", sum - (in[v[j]] ? dp[i][v[j]][p - 1] : 0));
                    dp[v[j]][i][p] = sum - (in[v[j]] ? dp[i][v[j]][p - 1] : 0);
                }
                /* for (int j = 0; j < (int)v.size(); ++j) {
                    for (int k = 0; k < (int)v.size(); ++k) {
                        if (v[k] == v[j]) continue;
                        if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 && 
                            cross(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) < 0) 
                            dp[v[k]][i][p] += dp[i][v[j]][p - 1];
                    }
                } */
            } else {
                sort(v.begin(), v.end(), [&](int a, int b) {
                    return ang[a] > ang[b];
                });
                // for (int j = 0; j < (int)v.size(); ++j)
                //     printf("%d ", v[j]);
                // puts("");
                long long sum = 0;
                deque<int> dq;
                /* for (int k = (int)v.size() - 1; k > 0; --k) {
                    int j = 0;
                    if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 &&
                        cross(x[v[k]] - x[i], y[v[k]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) < 0) {
                        printf("push k = %d\n", v[k]);
                        sum += dp[i][v[k]][p - 1];
                        in[v[k]] = true;
                        dq.push_back(k);
                    }
                } */
                for (int j = 0, k = 0; j < (int)v.size(); ++j) {
                    // printf("v[j] = %d\n", v[j]);
                    while (!in[v[k]] && (k == j || 
                           dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 &&
                           cross(x[v[k]] - x[i], y[v[k]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) > 0)) {

                        // printf("push k = %d\n", v[k]);
                        sum += dp[i][v[k]][p - 1];
                        in[v[k]] = true;
                        dq.push_back(k);
                        k = (k + 1) % (int)v.size();
                    }
                    while (dq.size()) {
                        if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[dq[0]]] - x[i], y[v[dq[0]]] - y[i]) <= 0 ||
                            cross(x[v[dq[0]]] - x[i], y[v[dq[0]]] - y[i], x[v[j]] - x[i], y[v[j]] - y[i]) <= 0) {
                            in[v[dq[0]]] = false;
                            sum -= dp[i][v[dq[0]]][p - 1];
                            // printf("pop k = %d\n", v[dq[0]]);
                            dq.pop_front();
                        } else {
                            break;
                        }
                    }
                    //printf("inside: ");
                    //for (int k = 0; k < n; ++k) if (in[k]) printf("%d ", k); puts("");
                    //printf("sum = %lld\n", sum - (in[v[j]] ? dp[i][v[j]][p - 1] : 0));
                    dp[v[j]][i][p] = sum - (in[v[j]] ? dp[i][v[j]][p - 1] : 0);
                }
                /* for (int j = 0; j < (int)v.size(); ++j) {
                    for (int k = 0; k < (int)v.size(); ++k) {
                        if (v[k] == v[j]) continue;
                        if (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0 && 
                            cross(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0) 
                            dp[v[k]][i][p] += dp[i][v[j]][p - 1];
                    }
                } */
            }

            /* long long sum = 0;
            for (int j = 0, k = 0; j < (int)v.size(); ++j) {
                while (dot(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]) > 0) {
                    int c = cross(x[v[j]] - x[i], y[v[j]] - y[i], x[v[k]] - x[i], y[v[k]] - y[i]);
                    if (p % 2 == 1 && c < 0 ||
                        p % 2 == 0 && c > 0) break;

                    sum += dp[i][k][p - 1];
                    printf("v[j] = %d v[k] = %d\n", v[j], v[k]);
                    k = (k + 1) % (int)v.size();
                    if (k == j) break;
                }

                dp[v[j]][i][p] += sum;
                sum -= dp[i][v[j]][p - 1];
            } */
            // for (int j = 0; j < n; ++j) 
                // printf("dp[%d][%d][%d] = %lld\n", i, j, p - 1, dp[i][j][p - 1]);
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans += dp[i][j][5];
            // printf("dp[%d][%d][%d] = %lld\n", i, j, 5, dp[i][j][5]);
        }
    }
    printf("%lld\n", ans / 2);
    return 0;
}
