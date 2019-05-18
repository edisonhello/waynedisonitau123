#include <bits/stdc++.h>
using namespace std;

int n, k;

struct point {
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
    double abs() { return hypot(x, y); }
} ins[1005], ous[1005];
bool intubao[1005], reach[1005][1005];
double dist[1005][1005], dp[2005];

point operator - (const point &a, const point &b) { return point(a.x - b.x, a.y - b.y); }
long long operator * (const point &a, const point &b) { return 1ll * a.x * b.x + 1ll * a.y * b.y; }
long long operator ^ (const point &a, const point &b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

bool operator == (const point &a, const point &b) {
    return a.x == b.x && a.y == b.y;
}
bool operator < (const point &a, const point &b) {
    return a.x == b.x ? a.y > b.y : a.x < b.x;
}

ostream& operator << (ostream &o, point a) {
    o << "(" << a.x << ", " << a.y << ")";
    return o;
}

long long cross(point a, point b, point c) {
    return (c - b) ^ (a - b);
}

vector<point> make_tubao(vector<point> ps) {
    sort(ps.begin(), ps.end());
    // cerr << "ps: ["; for (point p : ps) cerr << "(" << p.x << ", " << p.y << ") "; cerr << endl;
    vector<point> tb;
    for (point p : ps) {
        while (tb.size() > 1u && cross(tb[tb.size() - 2], tb.back(), p) >= 0) tb.pop_back();
        tb.push_back(p);
    }
    int tmp = tb.size();
    reverse(ps.begin(), ps.end());
    for (point p : ps) {
        while (tb.size() > tmp && cross(tb[tb.size() - 2], tb.back(), p) >= 0) tb.pop_back();
        tb.push_back(p);
    }
    tb.pop_back();
    reverse(tb.begin(), tb.end()); // return a counter clock wise tubao
    // cerr << "get tubao: ["; for (point p : tb) cerr << "(" << p.x << ", " << p.y << ") "; cerr << endl;
    return tb;
}

bool possible() {
    vector<point> outside, total;
    for (int i = 0; i < n; ++i) {
        outside.push_back(ous[i]);
        total.push_back(ous[i]);
    }
    for (int i = 0; i < k; ++i) {
        total.push_back(ins[i]);
    }
    return make_tubao(outside) == make_tubao(total);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("mines.in", "r", stdin);
    freopen("mines.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> ous[i].x >> ous[i].y;
    }
    for (int i = 0; i < k; ++i) {
        cin >> ins[i].x >> ins[i].y;
    }
    if (!possible()) {
        cout << -1 << endl;
        exit(0);
    }
    vector<point> inside;
    for (int i = 0; i < k; ++i) inside.push_back(ins[i]);
    vector<point> tubao = make_tubao(inside);
    for (int i = 0; i < n; ++i) {
        point p = ous[i];
        bool outside = false;
        for (int j = 0; j < int(tubao.size()); ++j) {
            int nxj = (j + 1) % tubao.size();
            if (((tubao[nxj] - p) ^ (tubao[j] - p)) < 0) outside = true;
        }
        if (!outside && tubao.size() > 1u) intubao[i] = true;
    }
    auto in_two_side = [] (const point a, const point b, const point c, const point d) -> bool {
        // cerr << "in_two_side of " << a << " " << b << " " << c << " " << d << " , res : " << ((c - a) ^ (b - a)) * ((d - a) ^ (b - a)) << endl;
        return ((c - a) ^ (b - a)) * ((d - a) ^ (b - a)) < 0;
    };
    auto in_two_side0 = [] (const point a, const point b, const point c, const point d) -> bool {
        // cerr << "in_two_side0 of " << a << " " << b << " " << c << " " << d << " , res : " << (((c - a) ^ (b - a)) * ((d - a) ^ (b - a)) == 0) << endl;
        return ((c - a) ^ (b - a)) * ((d - a) ^ (b - a)) == 0;
    };
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dist[i][j] = 1e9;
    for (int i = 0; i < n; ++i) if (!intubao[i]) {
        for (int j = i + 1; j < n; ++j) if (!intubao[j]) {
            bool cross = false;
            int end_point_intersect = 0;
            for (int z = 0; z < int(tubao.size()); ++z) {
                int nxz = (z + 1) % tubao.size();
                if (in_two_side(ous[i], ous[j], tubao[z], tubao[nxz]) && in_two_side(tubao[z], tubao[nxz], ous[i], ous[j])) {
                    cross = true;
                } else if (in_two_side0(ous[i], ous[j], tubao[z], tubao[nxz]) || in_two_side0(tubao[z], tubao[nxz], ous[i], ous[j])) ++end_point_intersect;
            }
            if (end_point_intersect > 3) cross = true;
            reach[i][j] = reach[j][i] = !cross;
            dist[i][j] = dist[j][i] = hypot(ous[i].x - ous[j].x, ous[i].y - ous[j].y);
            // cout << i << " " << j << " reach " << reach[i][j] << endl;
        // }
    }
    double cenx = 0, ceny = 0;
    for (int i = 0; i < int(tubao.size()); ++i) cenx += tubao[i].x, ceny += tubao[i].y;
    cenx /= tubao.size(); ceny /= tubao.size();
    // cerr << "cen: " << cenx << " " << ceny << endl;
    vector<int> o;
    for (int i = 0; i < n; ++i) o.push_back(i);
    sort(o.begin(), o.end(), [&] (const int &a, const int &b) -> bool { return atan2(ous[a].y - ceny, ous[a].x - cenx) < atan2(ous[b].y - ceny, ous[b].x - cenx); });
    // cerr << "o: "; for (int i : o) cerr << i << " "; cerr << endl;
    // cerr << "o point: "; for (int i : o) cerr << ous[i] << " "; cerr << endl;
    vector<int> len(o.size(), 0);
    for (int i = 0; i < n; ++i) {
        point p = ous[o[i]];
        point ref = tubao[0];
        // cout << "p ref: " << p << " " << ref << endl;
        double min_deg = 1e9;
        for (point tbp : tubao) {
            min_deg = min(min_deg, asin(double((ref - p) ^ (tbp - p)) / (ref - p).abs() / (tbp - p).abs()));
        }
        // cerr << "mindeg: " << min_deg << endl;
        while (len[i] < n) {
            if (intubao[o[(len[i] + 1 + i) % n]]) {
                ++len[i];
                continue;
            }
            point nxtp = ous[o[(len[i] + 1 + i) % n]];
            // cerr << "deg to " << nxtp << " is " << asin(((ref - p) ^ (nxtp - p)) / ref.abs() / nxtp.abs()) << endl;
            if (asin(double((ref - p) ^ (nxtp - p)) / (ref - p).abs() / (nxtp - p).abs()) > min_deg + 1e-6) break;
            ++len[i];
        }
        // cerr << "len of " << p << " is " << len[i] << endl;
    }
    double mn = 1e9;
    for (int i = 0; i < n; ++i) if (!intubao[i]) {
        for (int i = 0; i <= n; ++i) dp[i] = 1e9;
        dp[0] = 0;
        for (int j = 0; j < n; ++j) {
            int now = o[(i + j) % n];
            for (int k = 1; k <= len[(i + j) % n]; ++k) {
                int to = o[(i + j + k) % n];
                int t = (j + k) % n == 0 ? n : (j + k) % n;
                if (!reach[now][to]) break;
                dp[t] = min(dp[t], dp[j] + dist[now][to]);
            }
        }
        // cerr << "update answer : " << dp[n] << endl;
        mn = min(mn, dp[n]);
    }
    cout << fixed << setprecision(12) << mn << endl;
    
}
