#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(const string &s) {
    vector<int> f(s.size(), 0);
    int k = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        while (k > 0 && s[i] != s[k])
            k = f[k - 1];
        if (s[i] == s[k]) ++k;
        f[i] = k;
    }
    return f;
}

vector<int> search(const string &s, const string &t) {
    vector<int> f = kmp(t), res;
    int k = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        while (k > 0 && (k == (int)t.size() || s[i] != t[k]))
            k = f[k - 1];
        if (s[i] == t[k]) ++k;
        if (k == (int)t.size())
            res.push_back(i - (int)t.size() + 1);
    }
    return res;
}

const int maxn= 1e6 + 5;
bool v[maxn];

vector<vector<int>> get(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    vector<int> b;
    for (int i = 0; i < n; i += 2)
        b.push_back(a[i]);
    for (int i = 1; i < n; i += 2)
        b.push_back(a[i]);
    vector<vector<int>> res;
    for (int i = 0; i < n; ++i) {
        if (v[i]) continue;
        int j = i;
        vector<int> cyc;
        while (!v[j]) {
            cyc.push_back(j);
            v[j] = true;
            j = b[j];
        }
        res.push_back(cyc);
    }
    return res;
}

vector<int> match(const string &s, const string &t) {
    vector<int> res = search(s + s, t);
    while (res.size() > 0 && res.back() >= (int)s.size())
        res.pop_back();
    return res;
}

template <typename T> 
tuple<T, T, T> extgcd(T a, T b) {
    if (!b)
        return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = extgcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

long long crt(vector<int> mod, vector<int> a) {
    long long mult = mod[0];
    int n = (int)mod.size();
    // for (int i = 0; i < n; ++i) cout << mod[i] << ' '; cout << endl;
    // for (int i = 0; i < n; ++i) cout << a[i] << ' '; cout << endl;
    long long res = a[0];
    for (int i = 1; i < n; ++i) {
        long long d, x, y;
        tie(d, x, y) = extgcd(mult, (long long)mod[i]);
        if ((a[i] - res) % d)
            return -1;
        long long nmult = mult / __gcd(mult, 1ll * mod[i]) * mod[i];
        res += x * ((a[i] - res) / d) % nmult * mult % nmult;
        mult = nmult;
        ((res %= mult) += mult) %= mult;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t; cin >> s >> t;

    vector<vector<int>> cycle = get((int)s.size());
    /* for (int i = 0; i < (int)cycle.size(); ++i) {
        for (int j = 0; j < (int)cycle[i].size(); ++j)
            cout << cycle[i][j] << ' ';
        cout << endl;
    } */

    vector<vector<int>> shift;
    for (int i = 0; i < (int)cycle.size(); ++i) {
        string x = "", y = "";
        for (int j = 0; j < (int)cycle[i].size(); ++j) {
            x += s[cycle[i][j]];
            y += t[cycle[i][j]];
        }
        shift.push_back(match(x, y));
    }

    vector<int> mod, a;
    for (int i = 0; i < (int)shift.size(); ++i) {
        if (shift[i].empty()) {
            cout << "-1" << endl;
            return 0;
        }
        if ((int)shift[i].size() == 1) {
            mod.push_back((int)cycle[i].size());
            a.push_back(shift[i][0]);
        } else {
            assert(shift[i][0] < shift[i][1] - shift[i][0]);
            mod.push_back(shift[i][1] - shift[i][0]);
            a.push_back(shift[i][0]);
        }
    }

    long long ans = crt(mod, a);
    if (ans != -1) {
        for (int i = 0; i < (int)mod.size(); ++i)
            assert(ans % mod[i] == a[i]);
    }
    cout << ans << endl;
    return 0;
}
