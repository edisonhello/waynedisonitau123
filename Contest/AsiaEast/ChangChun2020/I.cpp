#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % mod;
        b = 1ll * b * b % mod; n >>= 1;
    }
    return a;
}

int inv(int x) {
    return pw(x, mod - 2);
}

int X, invX;

int sz[100005];
int mxchi[100005];
vector<int> g[100005];

void predfs(int now, int pa) {
    for (int i : g[now]) if (i != pa) {
        predfs(i, now);
        sz[now] += sz[i];
        if (sz[i] > sz[mxchi[now]]) {
            mxchi[now] = i;
        }
    }
    ++sz[now];
}

int f[100005], tmpf[100005];
vector<int> dfs1_gives[100005];

int dfs1(int now, int pa) {
    if (pa && g[now].size() == 1u) {
        tmpf[now] = 1;

        return inv(X);
    }

    int give_mxsz = -1;
    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) {
            dfs1_gives[now].push_back(-1);
        } else {
            int r = dfs1(to, now);
            // cerr << "dfs1 at " << now << " to " << to << " receive " << r << endl;
            dfs1_gives[now].push_back(r);

            if (to == mxchi[now]) {
                tmpf[now] = r;
                give_mxsz = r;
            }
        }
    }

    int chsum = 0;
    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) continue;
        if (to == mxchi[now]) (chsum += tmpf[to]) >= mod ? chsum -= mod : 0;
        else (chsum += 1ll * tmpf[to] * inv(dfs1_gives[now][i]) % mod * give_mxsz % mod) >= mod ? chsum -= mod : 0;
    }


    int ret = tmpf[now] * 1ll * (int)g[now].size() % mod * inv(X) % mod + (mod - chsum);
    if (ret >= mod) ret -= mod;

    return ret;
}

void dfs1_2(int now, int pa, int mult) {
    // cerr << "dfs1_2 now pa mult " << now << ' ' << pa << ' ' << mult << endl;
    f[now] = tmpf[now] * 1ll * mult % mod;

    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) continue;

        // if (to == mxchi[now]) dfs1_2(to, now, mult);
        // else {
            int r = dfs1_gives[now][i];
            int nmult = 1ll * inv(r) * f[now] % mod;
            dfs1_2(to, now, nmult);
        // }
    }
}

int gg[100005];
pair<int, int> tmpg[100005];
vector<pair<int, int>> dfs2_gives[100005];

pair<int, int> dfs2(int now, int pa) {
    if (pa && g[now].size() == 1u) {
        tmpg[now] = make_pair(1, 0);
        
        // cerr << "now = " << now << " ret " << invX << "x + " << (int)((mod - f[now]) * 1ll * invX % mod) << endl;
        return make_pair(invX, (int)((mod - f[now]) * 1ll * invX % mod));
    }

    pair<int, int> mxch_give(-1, -1);
    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) {
            dfs2_gives[now].emplace_back(-1, -1);
        } else {
            auto r = dfs2(to, now);
            dfs2_gives[now].push_back(r);

            if (to == mxchi[now]) {
                tmpg[now] = r;
                mxch_give = r;
            }
        }
    }

    assert(mxch_give.first != -1);

    pair<int, int> chsum(0, 0);
    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) continue;
        if (to == mxchi[now]) {
            chsum.first += tmpg[to].first;
            chsum.second += tmpg[to].second;
        } else {
            auto [a, b] = mxch_give;
            auto [c, d] = dfs2_gives[now][i];
            auto [e, f] = tmpg[to];
            int g = 1ll * e * a % mod * inv(c) % mod;
            int h = (b + mod - d) * 1ll * inv(c) % mod * e % mod + f;
            if (h >= mod) h -= mod;
            chsum.first += g;
            chsum.second += h;
        }
        if (chsum.first >= mod) chsum.first -= mod;
        if (chsum.second >= mod) chsum.second -= mod;
    }

    auto ret = tmpg[now];
    // cerr << "Ret ini " << ret.first << ' ' << ret.second << endl;
    ret.second = (ret.second + mod - f[now]) % mod;
    // cerr << "Ret -f " << ret.first << ' ' << ret.second << endl;
    int mult = 1ll * g[now].size() * invX % mod;
    ret.first = ret.first * 1ll * mult % mod;
    ret.second = ret.second * 1ll * mult % mod;
    // cerr << "Ret *mul " << ret.first << ' ' << ret.second << endl;
    ret.first = (ret.first + mod - chsum.first) % mod;
    ret.second = (ret.second + mod - chsum.second) % mod;
    // cerr << "Ret -ch " << ret.first << ' ' << ret.second << endl;
    return ret;
}

void dfs2_2(int now, int pa, int xsol) {
    gg[now] = (tmpg[now].first * 1ll * xsol + tmpg[now].second) % mod;

    for (int i = 0; i < (int)g[now].size(); ++i) {
        int to = g[now][i];
        if (to == pa) continue;

        // if (to == mxchi[now]) dfs2_2(to, now, xsol);
        // else {
            auto r = dfs2_gives[now][i];
            int nsol = (mod + gg[now] - r.second) * 1ll * inv(r.first) % mod;
            dfs2_2(to, now, nsol);
        // }
    }
}

int main() {
    int n, k, px, qx; cin >> n >> k >> px >> qx;
    X = 1ll * px * inv(qx) % mod;
    invX = inv(X);


    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    predfs(k, 0);

    dfs1(k, 0);
    // for (int i = 1; i <= n; ++i) {
    //     cerr << "dfs1 gives of " << i << ": ";
    //     for (int j : dfs1_gives[i]) cerr << j << ' ';
    //     cerr << endl;
    // }
    f[k] = 1;
    for (int i = 0; i < (int)g[k].size(); ++i) {
        dfs1_2(g[k][i], k, inv(dfs1_gives[k][i]));
    }

    // cerr << "f: ";
    // for (int i = 1; i <= n; ++i) {
    //     cerr << f[i] << ' ';
    // }
    // cerr << endl;

    dfs2(k, 0);
    // for (int i = 1; i <= n; ++i) {
        // cerr << "dfs2 gives of " << i << ": ";
        // for (auto j : dfs2_gives[i]) cerr << "(" << j.first << ", " << j.second << ") ";
        // cerr << endl;
    // }
    gg[k] = 0;
    for (int i = 0; i < (int)g[k].size(); ++i) {
        auto r = dfs2_gives[k][i];
        int sol = (mod - r.second) * 1ll * inv(r.first) % mod;
        dfs2_2(g[k][i], k, sol);
    }

    // cerr << "g: ";
    // for (int i = 1; i <= n; ++i) {
    //     cerr << gg[i] << ' ';
    // }
    // cerr << endl;

    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum ^= 1ll * gg[i] * i % mod;
    }

    cout << sum << endl;


    // for (int i = 1; i <= n; ++i) {
    //     if (i == k) continue;
    //     int fsum = 0;
    //     for (int j : g[i]) {
    //         fsum += f[j];
    //         fsum %= mod;
    //     }
    //     fsum = fsum * 1ll * X % mod * inv(g[i].size()) % mod;
    //     // cerr << "i = " << i << " fsum = " << fsum << " and f[i] = " << f[i] << endl;
    //     assert(fsum == f[i]);
    // }

    // for (int i = 1; i <= n; ++i) {
    //     if (i == k) continue;
    //     int gsum = 0;
    //     for (int j : g[i]) {
    //         gsum += gg[j];
    //         gsum %= mod;
    //     }
    //     gsum = gsum * 1ll * X % mod * inv(g[i].size()) % mod;
    //     gsum += f[i];
    //     gsum %= mod;
    //     // cerr << "i = " << i << " gsum = " << gsum << " and gg[i] = " << gg[i] << endl;
    //     assert(gsum == gg[i]);
    // }
}

