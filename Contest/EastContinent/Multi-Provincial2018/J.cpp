#include <bits/stdc++.h>
using namespace std;

bool near(double a, double b) {
    return abs(a - b) < 1e-9;
}

struct point {
    long long x, y;
    double abs() { return hypot(x, y); }
};
point operator-(const point a, const point b) { return point{a.x - b.x, a.y - b.y}; }
long long operator*(const point a, const point b) { return a.x * b.x + a.y * b.y; }
long long operator^(const point a, const point b) { return a.x * b.y - a.y * b.x; }

bool line(point a, point b, point c) {
    return ((b - a) ^ (c - b)) == 0;
}

const int maxn = 1e6 + 5;
int fw[maxn], dp[maxn];
vector<tuple<int, int, int>> seg[maxn];

void add(int p, int b, int v) {
    for (int i = p; i <= b; i += i & -i)
        fw[i] = max(fw[i], v);
}

int query(int p) {
    int res = 0;
    for (int i = p; i > 0; i -= i & -i)
        res = max(res, fw[i]);
    return res;
}

vector<int> lis(vector<pair<int, int>> &v, int b) {
    // cout << "in lis" << endl;
    int n = (int)v.size();
    if (n == 0) return {};
    for (int i = 0; i <= b; ++i) fw[i] = 0;
    // cout << "b = " << b << endl;
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 1 + query(b - v[i].second - 1);
        // printf("dp[%d] = %d\n", i, dp[i]);
        add(b - v[i].second, b, dp[i]);
    }
    for (int i = 0; i <= n; ++i) {
        seg[i].clear();
    }
    for (int i = 0; i < n; ++i) seg[dp[i]].emplace_back(v[i].first, v[i].second, i);
    int z = 0, f = 1e9, pp = -1, qq = -1;
    for (int i = 0; i < n; ++i) z = max(z, dp[i]);
    // cout << "input = " << endl;
    // for (int i = 0; i < n; ++i) cout << "(" << v[i].first << ", " << v[i].second << ") ";
    // cout << endl;
    // cout << "z = " << z << endl;
    for (int i = 0; i < n; ++i) {
        if (dp[i] == z) {
            if (v[i].first < f) {
                f = v[i].first;
                pp = v[i].second;
                qq = i;
            }
        }
    }
    // cout << "hey" << endl;
    // cout << "f = " << f << endl;
    vector<int> res = {f};
    for (int i = z - 1; i >= 1; --i) {
        int ff = 1e9, ppp = -1, qqq = -1;
        for (int j = 0; j < (int)seg[i].size(); ++j) {
            if (get<1>(seg[i][j]) > pp && get<2>(seg[i][j]) > qq) {
                if (get<0>(seg[i][j]) < ff) {
                    ff = get<0>(seg[i][j]);
                    ppp = get<1>(seg[i][j]);
                    qqq = get<2>(seg[i][j]);
                }
            }
        }
        res.push_back(ff);
        f = ff;
        pp = ppp;
        qq = qqq;
    }
    // cout << "out lis" << endl;
    // reverse(res.begin(), res.end());
    return res;
}

int main() {
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        point a, b; cin >> a.x >> a.y >> b.x >> b.y;
        int n; cin >> n;
        vector<point> ps(n);
        for (point &p : ps) cin >> p.x >> p.y;
        vector<pair<int, int>> pv(n, pair<int, int>(0, 0));
        vector<double> angle(n);
        vector<int> pos, neg;
        for (int i = 0; i < n; ++i) {
            // cout << "Cross: " << ((b - a) ^ (ps[i] - a)) << endl;
            if (((b - a) ^ (ps[i] - a)) > 0) pos.push_back(i);
            if (((b - a) ^ (ps[i] - a)) < 0) neg.push_back(i);
        }
        // cout << "pos: "; for (int i : pos) cout << i << " "; cout << endl;
        // cout << "neg: "; for (int i : neg) cout << i << " "; cout << endl;

        for (int i = 0; i < n; ++i) angle[i] = acos((ps[i] - a) * (b - a) / (ps[i] - a).abs() / (b - a).abs());
        sort(pos.begin(), pos.end(), [&] (const int &i, const int &j) -> bool {
            return angle[i] < angle[j];
        });
        sort(neg.begin(), neg.end(), [&] (const int &i, const int &j) -> bool {
            return angle[i] < angle[j];
        });
        for (int i = 0, j = 0; i < (int)pos.size(); ++i) { if(i && !line(a, ps[pos[i-1]], ps[pos[i]])) ++j; pv[pos[i]].first = j; }
        for (int i = 0, j = 0; i < (int)neg.size(); ++i) { if(i && !line(a, ps[neg[i-1]], ps[neg[i]])) ++j; pv[neg[i]].first = j; } 

        for (int i = 0; i < n; ++i) angle[i] = acos((ps[i] - b) * (a - b) / (ps[i] - b).abs() / (a - b).abs());
        sort(pos.begin(), pos.end(), [&] (const int &i, const int &j) -> bool {
            return angle[i] < angle[j];
        });
        sort(neg.begin(), neg.end(), [&] (const int &i, const int &j) -> bool {
            return angle[i] < angle[j];
        });
        for (int i = 0, j = 0; i < (int)pos.size(); ++i) { if(i && !line(b, ps[pos[i-1]], ps[pos[i]])) ++j; pv[pos[i]].second = j; }
        for (int i = 0, j = 0; i < (int)neg.size(); ++i) { if(i && !line(b, ps[neg[i-1]], ps[neg[i]])) ++j; pv[neg[i]].second = j; } 
        
        sort(pos.begin(), pos.end(), [&] (const int &i, const int &j) -> bool {
            if (pv[i].first == pv[j].first) return pv[i].second > pv[j].second;
            return pv[i].first < pv[j].first;
        });
        sort(neg.begin(), neg.end(), [&] (const int &i, const int &j) -> bool {
            if (pv[i].first == pv[j].first) return pv[i].second > pv[j].second;
            return pv[i].first < pv[j].first;
        });

        vector<pair<int, int>> pos_info, neg_info;
        for (int i : pos) pos_info.emplace_back(i, pv[i].second);
        for (int i : neg) neg_info.emplace_back(i, pv[i].second);
        reverse(pos_info.begin(), pos_info.end());
        reverse(neg_info.begin(), neg_info.end());
        for (auto &i : pos_info) i.second = 2 * n - i.second - 1;
        for (auto &i : neg_info) i.second = 2 * n - i.second - 1;
        vector<int> posans = lis(pos_info, 2 * n), negans = lis(neg_info, 2 * n);
        if (negans.size() > posans.size()) swap(posans, negans);
        else if (negans.size() == posans.size() && negans < posans) swap(posans, negans);
        cout << posans.size() << endl;
        for (int i : posans) cout << i + 1 << "\n";
    }
}
