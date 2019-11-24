#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<long long, long long>

int sgn(int x) {
    if (x == 0) return x;
    if (x > 0) return 1;
    return -1;
}

pair<int, int> ps[2000];
pii operator - (pii a, pii b) { return pii(a.first - b.first, a.second - b.second); }
int operator ^ (pii a, pii b) { return a.first * b.second - a.second * b.first; }

#define crx(a, b, c) ((b - a) ^ (c - a))

vector<pii> convex(vector<pii> ps) {
    vector<pii> p;
    sort(ps.begin(), ps.end(), [&] (const pii &a, const pii &b) { return a.first == b.first ? a.second < b.second : a.first < b.first; });
    for (int i = 0; i < (int)ps.size(); ++i) {
        while (p.size() >= 2 && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    int t = p.size();
    for (int i = (int)ps.size() - 2; i >= 0; --i) {
        while ((int)p.size() > t && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    p.pop_back();
    return p;
}

int calc(int a, int b, int c) {
    return abs((ps[b] - ps[a]) ^ (ps[c] - ps[a]));
}

int calc(int a, int b, int c, int d) {
    vector<pii> pp{ps[a], ps[b], ps[c], ps[d]};
    vector<pii> tb = convex(pp);
    int sum = 0;
    for (int i = 0; i < (int)tb.size(); ++i) {
        int j = (i + 1) % tb.size();
        sum += tb[i] ^ tb[j];
    }

    cerr << "pp = " << ps[a] << ' ' << ps[b] << ' ' << ps[c] << ' ' << ps[d] << endl;
    cerr << "sum = " << sum << endl;
    return abs(sum);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) cin >> ps[i].first >> ps[i].second;
        int ans = 0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) for (int k = j + 1; k < n; ++k) for (int l = k + 1; l < n; ++l) {
            ans = max(ans, calc(i, j, k, l));
        }
        
        if (ans % 2 == 0) cout << ans / 2 << endl;
        else cout << ans / 2 << ".5" << endl;
    }
}
