#include <bits/stdc++.h>
using namespace std;

struct point {
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    bool operator<(const point &p) const {
        if (y == p.y) return x < p.x;
        return y < p.y;
    }
};

vector<point> p[3];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, c; cin >> x >> y >> c;
        --c;
        p[c].emplace_back(x, y);
    }
    sort(p[0].begin(), p[0].end());
    sort(p[1].begin(), p[1].end());
    reverse(p[1].begin(), p[1].end());
    point q(-3000, p[0][0].y - 0.2);
    vector<point> ans;
    ans.push_back(q);
    for (int i = 0; i < p[0].size(); ) {
        int j = i;
        if (i) {
            ans.emplace_back(-2999, p[0][i].y - 0.2);
        }
        while (j < p[0].size() && p[0][j].y == p[0][i].y) ++j;
        int to = p[0][j - 1].x;
        ans.emplace_back(p[0][j - 1].x + 0.1, p[0][j - 1].y - 0.2);
        for (int k = j - 1; k >= i; --k) {
            if (k != j - 1) {
                ans.emplace_back(p[0][k].x + 0.1, p[0][i].y - 0.1); 
            }
            ans.emplace_back(p[0][k].x + 0.1, p[0][i].y + 0.01);
            ans.emplace_back(p[0][k].x - 0.1, p[0][i].y + 0.01);
            ans.emplace_back(p[0][k].x - 0.1, p[0][i].y - 0.1);
        }
        if (j != p[0].size()) ans.emplace_back(-2999, p[0][i].y - 0.1);
        else ans.emplace_back(-3000, p[0][i].y - 0.1);
        i = j;
    }
    cout << ans.size() << endl;
    for (auto p : ans) cout << p.x << ' ' << p.y << endl;
    ans.clear();
    q = point(3000, p[1][0].y + 0.2);
    ans.push_back(q);
    for (int i = 0; i < p[1].size(); ) {
        int j = i;
        if (i) ans.emplace_back(2999, p[1][i].y + 0.2);
        while (j < p[1].size() && p[1][j].y == p[1][i].y) ++j;
        ans.emplace_back(p[1][j - 1].x - 0.1, p[1][j - 1].y + 0.2);
        for (int k = j - 1; k >= i; --k) {
            if (k != j - 1) ans.emplace_back(p[1][k].x - 0.1, p[1][k].y + 0.1);
            ans.emplace_back(p[1][k].x - 0.1, p[1][k].y - 0.01);
            ans.emplace_back(p[1][k].x + 0.1, p[1][k].y - 0.01);
            ans.emplace_back(p[1][k].x + 0.1, p[1][k].y + 0.1);
        }
        if (j != p[1].size()) ans.emplace_back(2999, p[1][i].y + 0.1);
        else ans.emplace_back(3000, p[1][i].y + 0.1);
        i = j;
    }
    cout << ans.size() << endl;
    for (auto p : ans) cout << p.x << ' ' << p.y << endl;
}
