#include <bits/stdc++.h>
using namespace std;

namespace sfx {

const int kN = 1'000'000;
bool t[kN];
int hi[kN], rv[kN], _s[kN], sa[kN], c[kN], x[kN], p[kN], q[kN];

void Pre(int *sa, int *c, int n, int z) {
    memset(sa, 0, sizeof(int) * n);
    memcpy(x, c, sizeof(int) * z);
}

void Induce(int *sa, int *c, int *s, bool *t, int n, int z) {
    memcpy(x + 1, c, sizeof(int) * (z - 1));
    for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
    memcpy(x, c, sizeof(int) * z);
    for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
}

void Solve(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
    bool uniq = t[n - 1] = true;
    int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
    memset(c, 0, sizeof(int) * z);
    for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
    for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
    if (uniq) {
        for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
        return;
    }
    for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
    Pre(sa, c, n, z);
    for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
    Induce(sa, c, s, t, n, z);
    for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
        bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
        ns[q[last = sa[i]]] = nmxz += neq;
    }
    Solve(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
    Pre(sa, c, n, z);
    for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
    Induce(sa, c, s, t, n, z);
}

void Build(const string &s) {
    for (int i = 0; i < s.size(); ++i) _s[i] = s[i];
    _s[s.size()] = 0;
    Solve(_s, sa, p, q, t, c, s.size() + 1, 256);
    for (int i = 0; i < s.size(); ++i) sa[i] = sa[i + 1];
    for (int i = 0; i < s.size(); ++i) rv[sa[i]] = i;
    int ind = 0;
    hi[0] = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (!rv[i]) {
            ind = 0;
            continue;
        }
        while (i + ind < s.size() && s[i + ind] == s[sa[rv[i] - 1] + ind]) ++ind;
        hi[rv[i]] = ind ? ind-- : 0;
    }
}

} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s; cin >> s;
    sfx::Build(s);
    vector<pair<int, int>> mg;
    int n = s.size();
    for (int i = 1; i < n; ++i) mg.emplace_back(sfx::hi[i], i);
    sort(mg.begin(), mg.end(), greater<pair<int, int>>());
    
    vector<int> uf(n), dist(n, n + 1);
    vector<set<int>> pos(n);
    for (int i = 0; i < n; ++i) {
        uf[i] = i;
        pos[i].insert(i);
    }

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    int a = 1, b = 1;

    auto Merge = [&](int x, int y, int w) {
        if ((x = Find(x)) == (y = Find(y))) return;
        if (pos[x].size() > pos[y].size()) swap(x, y);
        dist[y] = min(dist[y], dist[x]);
        uf[x] = y;
        int dt = 1e9;
        for (int i : pos[x]) {
            auto it = pos[y].lower_bound(i);
            if (it != pos[y].end()) dt = min(dt, *it - i);
            if (it != pos[y].begin()) dt = min(dt, i - *prev(it));
        }
        for (int i : pos[x]) pos[y].insert(i);
        int c = w + dt, d = dt;
        if (1LL * a * d < 1LL * c * b) {
            a = c;
            b = d;
        }
    };

    for (int lcp = n, i = 0; lcp >= 0; --lcp) {
        while (i < mg.size() && mg[i].first >= lcp) {
            Merge(sfx::sa[mg[i].second - 1], sfx::sa[mg[i].second], mg[i].first);
            i++;
        }
    }
    int g = __gcd(a, b);
    a /= g, b /= g;
    cout << a << '/' << b << endl;
}

