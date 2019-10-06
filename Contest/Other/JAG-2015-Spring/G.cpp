#include <bits/stdc++.h>
using namespace std;

const int maxn = 16;
char st[maxn][maxn];
bool v[1 << maxn][maxn][6];
int n, k, mask[maxn];
vector<int> dp[1 << maxn][maxn][6];

vector<int> i2v(int z) {
    if (n - k == 1) {
        assert(z == 0);
        return {0};
    }
    if (n - k == 2) {
        assert(z < 2);
        if (z == 0) return {0, 1};
        else return {1, 0};
    }
    if (n - k == 3) {
        assert(z < 6);
        if (z == 0) return {0, 1, 2};
        if (z == 1) return {0, 2, 1};
        if (z == 2) return {1, 0, 2};
        if (z == 3) return {1, 2, 0};
        if (z == 4) return {2, 0, 1};
        if (z == 5) return {2, 1, 0};
    }
    assert(false);
}

int v2i(vector<int> v) {
    // cout << "v2i" << endl;
    // for (int i : v) cout << i << ' '; cout << endl;
    if (n - k == 1) {
        if (v == vector<int>{0}) return 0;
    }
    if (n - k == 2) {
        if (v == vector<int>{0, 1}) return 0;
        if (v == vector<int>{1, 0}) return 1;
    }
    if (n - k == 3) {
        if (v == vector<int>{0, 1, 2}) return 0;
        if (v == vector<int>{0, 2, 1}) return 1;
        if (v == vector<int>{1, 0, 2}) return 2;
        if (v == vector<int>{1, 2, 0}) return 3;
        if (v == vector<int>{2, 0, 1}) return 4;
        if (v == vector<int>{2, 1, 0}) return 5;
    }
    assert(false);
}

vector<int> dfs(int s, int z, int p) {
    if (s == (1 << n) - 1) {
        return {};
    }
    if (v[s][z][p]) return dp[s][z][p];
    vector<int> ord;
    for (int i = 0; i < k; ++i) ord.push_back(st[z][i] - 'A');
    reverse(ord.begin(), ord.end());
    int d = ((1 << n) - 1) ^ mask[z];
    vector<int> rem;
    for (int i = 0; i < n; ++i) {
        if (d >> i & 1) rem.push_back(i);
    }
    vector<int> perm = i2v(p);
    for (int i = 0; i < n - k; ++i) ord.push_back(rem[perm[i]]);
    // printf("s = %d z = %d p = %d\n", s, z, p);
    // for (int i : ord) printf("%d ", i); puts("");
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[ord[i]] = i;

    dp[s][z][p] = {10000000};

    for (int i = 0; i < n; ++i) {
        if ((s >> i & 1) == 1) continue;
        bool ok = true;
        for (int j = 1; j < k; ++j) {
            ok &= pos[st[i][j] - 'A'] > pos[st[i][j - 1] - 'A'];
        }
        if (ok) {
            vector<int> vv;
            for (int j = 0; j < n; ++j) {
                if ((mask[i] >> ord[j] & 1) == 0) vv.push_back(ord[j]);
            }
            sort(vv.begin(), vv.end());
            vector<int> vvv;
            for (int j = 0; j < n; ++j) {
                if ((mask[i] >> ord[j] & 1) == 0)
                    vvv.push_back(lower_bound(vv.begin(), vv.end(), ord[j]) - vv.begin());
            }
            int np = v2i(vvv);
            vector<int> d = dfs(s ^ (1 << i), i, np);
            if (!d.empty() && d[0] > 100) continue;
            vector<int> dd = {i};
            dd.insert(dd.end(), d.begin(), d.end());
            if (dd < dp[s][z][p]) {
                dp[s][z][p] = dd;
            }
        }
    }
    v[s][z][p] = true;
    return dp[s][z][p];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%s", st[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) mask[i] |= (1 << (st[i][j] - 'A'));
    }

    int jie = n - k == 1 ? 1 : n - k == 2 ? 2 : 6;
    vector<int> ans = {10000000};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < jie; ++j) {
            vector<int> d = dfs(1 << i, i, j);
            if (d[0] > 100) continue;
            vector<int> dd = {i};
            dd.insert(dd.end(), d.begin(), d.end());
            if (dd < ans) ans = dd;
        }
    }
    for (int i : ans) printf("%c", 'A' + i);
    puts("");
}
