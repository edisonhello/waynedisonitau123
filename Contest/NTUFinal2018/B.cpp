#include<bits/stdc++.h>
using namespace std;


int kmp(const string &s){
    vector<int> f(s.size(),0);
    int k=0;
    for(int i=1;i<int(s.size());++i){
        while(k>0 && s[i]!=s[k])k = f[k-1];
        if (s[i] == s[k]) ++k;
        f[i] = k;
    }
    // cout << "f: " ; for (int i : f) cout << i << " "; cout << endl;
    return f.back();
}

const int mod = 1e9 + 87;
int magic, pw[1000006];

int qry(const vector<int> &h, int l, int r) {
    if (l == 0) return h[r];
    return (h[r] - pw[r - l + 1] * 1ll * h[l - 1] % mod + mod) % mod;
}

vector<int> period(const string &s) {
    vector<int> h((int)s.size(), 0);
    h[0] = s[0];
    for (int i = 1; i < (int)s.size(); ++i) {
        h[i] = (h[i - 1] * 1ll * magic + s[i]) % mod;
    }
    vector<int> res((int)s.size() + 1, 0);
    for (int i = 1; i <= (int)s.size(); ++i) {
        bool ok = true;
        for (int j = i; j < (int)s.size() && ok; j += i) {
            int l = j, r = min(l + i - 1, (int)s.size() - 1);
            // cout << "i = " << i << " l =  " << l << " r = " << r << endl;
            if (qry(h, 0, r - l) != qry(h, l, r)) ok = false;
        }
        if (ok) res[i] = 1;
    }
    // cout << "s = " << s << endl;
    // cout << "period = ";
    // for (int i : res) cout << i << ' '; cout << endl;
    return res;
}

vector<int> vand(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < (int)b.size(); ++i) {
        if (a[i] && b[i]) a[i] = 1;
        else a[i] = 0;
    }
    return a;
}

string mp[1000006];

long long lcm(long long a, long long b) {
    return a / __gcd(a, b) * b;
}

vector<vector<vector<int>>> sp;
vector<vector<int>> cost;



int main() {
    srand(time(0));
    magic = rand() % 1000 + 1;
    pw[0] = 1;
    for (int i = 1; i < 1000006; ++i) pw[i] = pw[i - 1] * 1ll * magic % mod;
    // string s; while (cin >> s) cout << period(s) << endl;
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> mp[i];
    vector<int> hor, ver;
    for (int i = 0; i < n; ++i) {
        vector<int> x = period(mp[i]);
        if (hor.size() == 0) hor = x;
        else hor = vand(hor, x);
        // cout << "wei: "<< wei << endl;
    }
    for (int i = 0; i < m; ++i) {
        string s;
        for(int j = 0; j < n; ++j) s += mp[j][i];
        // cout << "new string: " << s << endl;
        // cout << hei << " " << period(s) << endl;
        vector<int> y = period(s);
        if (ver.size() == 0) ver = y;
        else ver = vand(ver, y);
    }
    int wei = 1, hei = 1;
    while (!hor[wei]) ++wei;
    while (!ver[hei]) ++hei;
    // cout << "wei = " << wei << " hei = " << hei << endl;
    cost.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> cost[i][j];
    int lg = 0;
    while ((1 << lg) < n) ++lg;
    // cout << "lg = " << lg << endl;
    sp.resize(m, vector<vector<int>>(lg + 1, vector<int>(n, 0)));
    for (int j = 0; j < m; ++j) for (int i = 0; i < n; ++i) sp[j][0][i] = cost[i][j];
    for (int j = 0; j < m; ++j) {
        for (int z = 1; z <= lg; ++z) {
            for (int i = 0; i + (1 << (z - 1)) < n; ++i) {
                sp[j][z][i] = max(sp[j][z - 1][i], sp[j][z - 1][i + (1 << (z - 1))]);
            }
        }
    }
    // cout << "builded" << endl;
    auto query = [&](int j, int l, int r) {
        int p = 31 - __builtin_clz(r - l + 1);
        return max(sp[j][p][l], sp[j][p][r - (1 << p) + 1]);
    };
    int mx = 1e9 + 87;
    for (int i = 0; i + hei - 1 < n; ++i) {
        // cout << "new line" << endl;
        deque<pair<int, int>> dq;
        for (int j = 0; j < wei; ++j) {
            int x = query(j, i, i + hei - 1);
            // cout << x << " " << j << " " << i << " " << i + hei - 1 << endl;
            while (dq.size() && dq.back().first <= x) dq.pop_back();
            dq.emplace_back(x, j);
        }
        // cout << "meow" << endl;
        mx = min(mx, dq.front().first);
        for (int j = wei; j < m; ++j) {
            int x = query(j, i, i + hei - 1);
            while (dq.size() && dq.back().first <= x) dq.pop_back();
            // cout << x << " " << j << " " << i << " " << i + hei - 1 << endl;
            dq.emplace_back(x, j);
            if (j - dq.front().second >= wei) dq.pop_front();
            mx = min(mx, dq.front().first);
        }
    }
    cout << 1ll * mx * (wei + 1) * (hei + 1) << endl;
}
