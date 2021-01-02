#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;

    void norm() {
        int g = __gcd(x, y);
        x /= g;
        y /= g;
        if (x < 0) x = -x, y = -y;
        else if (x == 0 && y < 0) y = -y;
    }
};

P operator- (const P &a, const P &b) { return P{a.x - b.x, a.y - b.y}; }
bool operator< (const P &a, const P &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        map<P, vector<pair<P, P>>> mp;
        long long ans = n * 1ll * (n - 1) / 2;

        for (int i = 0; i < n; ++i) {
            P pa, pb;
            cin >> pa.x >> pa.y;
            cin >> pb.x >> pb.y;


            P g = pa - pb;
            g.norm();
            mp[g].emplace_back(pa, pb);
        }

        for (auto &[dir, lines] : mp) {
            map<long long, int> cnt;
            auto [a, b] = dir;
            for (auto &[pa, pb] : lines) {
                long long c = -1ll * b * pa.x + 1ll * a * pa.y;
                cnt[c]++;
            }

            int nn = lines.size();
            ans -= 1ll * nn * (nn - 1) / 2;
            for (auto [_, nnn] : cnt) {
                ans += 1ll * nnn * (nnn - 1) / 2;
            }
        }

        cout << ans << '\n';
    }
}

