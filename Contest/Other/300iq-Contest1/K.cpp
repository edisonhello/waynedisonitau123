#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 998244353;

vector<vector<int>> Multiply(vector<vector<int>> a, vector<vector<int>> b) {
    vector<vector<int>> res(12, vector<int>(12));
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            for (int k = 0; k < 12; ++k) {
                res[i][j] += 1LL * a[i][k] * b[k][j] % kMod;
                if (res[i][j] >= kMod) res[i][j] -= kMod;
            }
        }
    }
    return res;
}

int main() {
    vector<int> p(4);
    iota(p.begin(), p.end(), 0);
    map<vector<int>, int> id;
    vector<vector<int>> a4;
    do {
        int inv = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < i; ++j) {
                inv += p[j] > p[i];
            }
        } 
        if (inv % 2 == 0) {
            int r = id.size();
            a4.push_back(p);
            id[p] = r;
        }
    } while (next_permutation(p.begin(), p.end()));

    assert(a4.size() == 12);

    auto Mult = [&](vector<int> a, vector<int> b) {
        vector<int> c(4);
        for (int i = 0; i < 4; ++i) c[i] = b[a[i]];
        return c;
    };

    vector<vector<int>> mult(12, vector<int>(12, -1));

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            vector<int> c = Mult(a4[i], a4[j]);
            assert(id.find(c) != id.end());
            mult[i][j] = id[c];
        }
    }

    int a = id[{1, 0, 3, 2}];
    int b = id[{1, 2, 0, 3}];

    int len[12] = {0};
    for (int i = 1; i < 12; ++i) len[i] = 100;
    for (int i = 1; i <= 4; ++i) {
        for (int s = 0; s < (1 << i); ++s) {
            int v = 0;
            for (int j = 0; j < i; ++j) {
                if (s >> j & 1) v = mult[v][a];
                else v = mult[v][b];
            }
            len[v] = min(len[v], i);
        }
    }

    int n, x;
    string s;
    cin >> n >> s >> x;
    int v = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') v = mult[v][a];
        else v = mult[v][b];
    }
    vector<vector<int>> mat(12, vector<int>(12));
    for (int i = 0; i < 12; ++i) {
        mat[mult[i][a]][i]++;
        mat[mult[i][b]][i]++;
    }

    // if (x < len[v]) {
    //     cout << 0 << endl;
    //     return 0;
    // }
    int res = x;

    auto fpow = [&](auto a, int n) {
        vector<vector<int>> res(12, vector<int>(12));
        for (int i = 0; i < 12; ++i) res[i][i] = 1;
        while (n > 0) {
            if (n & 1) res = Multiply(res, a);
            a = Multiply(a, a);
            n >>= 1;
        }
        return res;
    };

    mat = fpow(mat, res);
    cout << mat[v][0] << endl;
}

