#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
vector<pair<int, int>> g[maxn];
vector<tuple<int, long long, int>> ch[maxn];
long long ans[maxn];

void dfs(int x, int p) {
    for (const auto &e : g[x]) {
        int u = e.first, d = e.second;
        if (u == p) continue;
        dfs(u, x);
        long long best = 0;
        for (int i = 0; i < ch[u].size(); ++i) {
            best = max(best, get<1>(ch[u][i]) + (get<0>(ch[u][i]) - d) * 1ll * (get<0>(ch[u][i]) - d));
        }
        ch[x].emplace_back(d, best, u);
    }
}

long long a(tuple<int, long long, int> v) {
    return -2 * get<0>(v);
}

long long b(tuple<int, long long, int> v) {
    return get<1>(v) + get<0>(v) * 1ll * get<0>(v);
}

long long x(tuple<int, long long, int> v) {
    return get<0>(v);
}

int who(tuple<int, long long, int> v) {
    return get<2>(v);
}

vector<tuple<int, long long, int>> del[maxn];

using data = tuple<int, long long, int>;

bool kill(data i, data j, data k, int d) {
    long long ai = a(i), bi = b(i);
    long long aj = a(j), bj = b(j);
    long long ak = a(k), bk = b(k);
    if (ak == aj) {
        if (bk >= bj) return true;
        else return false;
    }
    if (d == 0) return 1.0 * (bk - bj) / (aj - ak) <= 1.0 * (bj - bi) / (ai - aj);
    else return 1.0 * (bk - bj) / (aj - ak) >= 1.0 * (bj - bi) / (ai - aj);

}

bool killl(data j, data k) {

    long long aj = a(j), bj = b(j);
    long long ak = a(k), bk = b(k);
    if (ak == aj) {
        if (bk >= bj) return true;
        else return false;
    }
    return false;
}

long long func(data i, data j) {
    return b(i) + a(i) * x(j) + get<0>(j) * 1ll * get<0>(j);
}

long long tmp[maxn];
data fr[maxn], nxt[maxn], prv[maxn];

void upd(data i, data j) {
    if (who(j) == -1) return;
    if (func(j, i) > tmp[who(i)]) {
        tmp[who(i)] = func(j, i);
        fr[who(i)] = j;
    }
}

/* long long solve(vector<tuple<int, long long, int>> v) {
    sort(v.begin(), v.end(), [&](const data &i, const data &j) { return a(i) == a(j) ? b(i) < b(j) : a(i) < a(j); });
    deque<tuple<int, long long, int>> dq;
    for (int i = 0; i < v.size(); ++i) {
        //printf("i = %d (%d, %lld, %d)\n", i, get<0>(v[i]), get<1>(v[i]), get<2>(v[i]));
        while (dq.size() && killl(dq.back(), v[i])) {

            del[who(v[i])].push_back(dq[dq.size() - 1]);
            // nxt[who(dq[dq.size() - 2])] = dq[dq.size() - 1];
            dq.pop_back();
         //   puts("pop");
        }
        while (dq.size() >= 2 && kill(dq[dq.size() - 2], dq[dq.size() - 1], v[i])) {
            del[who(v[i])].push_back(dq[dq.size() - 1]);
            nxt[who(dq[dq.size() - 2])] = dq[dq.size() - 1];
            dq.pop_back();
       //     puts("pop");
        }
        if (dq.size()) prv[who(v[i])] = dq.back();
        dq.push_back(v[i]);
    }
    sort(v.begin(), v.end(), [&](const data &i, const data &j) { return x(i) < x(j); });
    data last = make_tuple(-1, -1, -1);
    long long res = 0;
     puts("dqdqdqdq");
    for (auto i : dq) {
        printf("(%d, %lld, %d)\n", get<0>(i), get<1>(i), get<2>(i));
    } 
    for (int i = 0; i < v.size(); ++i) {
        while (dq.size() >= 2 && func(dq[1], v[i]) >= func(dq[0], v[i])) {
            last = dq[0];
            dq.pop_front();
        }
        if (who(dq[0]) != who(v[i])) upd(v[i], dq[0]);
        if (who(last) != -1 && who(last) != who(v[i])) upd(v[i], last);
        if (dq.size() > 1 && who(dq[1]) != who(v[i])) upd(v[i], dq[1]);
        if (who(nxt[who(dq[0])]) != -1 && who(nxt[who(dq[0])]) != who(v[i])) upd(v[i], nxt[who(dq[0])]);
        // if (who(prv[who(dq[0])]) != -1 && who(prv[who(dq[0])]) != who(v[i])) upd(v[i], prv[who(dq[0])]);
        for (auto u : del[who(v[i])]) {
            if (who(u) == who(v[i])) continue;
            upd(v[i], u);
            // upd(u, v[i]);
        }
    }
    return res;
}*/

void dfs2(int x, int p, data ut) {
    if (who(ut) != -1) ch[x].push_back(ut);
    sort(ch[x].begin(), ch[x].end(), [&](const data &i, const data &j) { return a(i) == a(j) ? b(i) < b(j) : a(i) < a(j); });
    // sort(ch[x].begin(), ch[x].end(), []() {});
    deque<tuple<int, long long, int>> dq;
    for (int i = 0; i < (int)ch[x].size(); ++i) {
        // while (dq.size() >= 2 && func(dq[1], ch[x][i]) >= func(dq[0], ch[x][i])) dq.pop_front();
        if (dq.size()) upd(ch[x][i], dq[0]);
        while (dq.size() >= 2 && kill(dq[dq.size() - 2], dq[dq.size() - 1], ch[x][i], 0)) dq.pop_back();
    }
    dq.clear();
    for (int i = (int)ch[x].size() - 1; i >= 0; --i) {
        // while (dq.size() >= 2 && func(dq[1], ch[x][i]) >= func(dq[0], ch[x][i])) dq.pop_front();
        if (dq.size()) upd(ch[x][i], dq[0]);
        while (dq.size() >= 2 && kill(dq[dq.size() - 2], dq[dq.size() - 1], ch[x][i], 1)) dq.pop_back();
    }
    // ans[x] = solve(ch[x]);
    for (int i = 0; i < (int)ch[x].size(); ++i) ans[x] = max(ans[x], get<1>(ch[x][i]));
    for (const auto &e : g[x]) {
        int u = e.first, d = e.second;
        if (u == p) continue;
        data k = fr[u];
        assert(who(k) != u);
       // printf("u = %d k = (%d, %lld, %d)\n", u, get<0>(k), get<1>(k), get<2>(k));
       // printf("fr[%d] = %d\n", u, who(fr[u]));
       // printf("tmp[%d] = %lld\n", u, tmp[u]);
        if (who(k) == -1) {
            get<0>(k) = d;
            get<1>(k) = 0;
            get<2>(k) = x;
        } else {
            get<1>(k) += (d - get<0>(k)) * 1ll * (d - get<0>(k));
            get<0>(k) = d;
            get<2>(k) = x;
        }
        dfs2(u, x, k);
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y, d; scanf("%d%d%d", &x, &y, &d);
        --x, --y;
        g[x].emplace_back(y, d);
        g[y].emplace_back(x, d);
    }
    for (int i = 0; i < n; ++i) get<2>(fr[i]) = -1, get<2>(nxt[i]) = -1, get<2>(prv[i]) = -1;
    dfs(0, -1);
/*     for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)ch[i].size(); ++j) {
            printf("(%d, %lld, %d) ", get<0>(ch[i][j]), get<1>(ch[i][j]), get<2>(ch[i][j]));
        }
        puts("");
    } */
    dfs2(0, -1, data(0, 0, -1));
    for (int i = 0; i < n; ++i) printf("%lld\n", ans[i]);
}
