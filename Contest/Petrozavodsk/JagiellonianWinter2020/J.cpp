#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int C = 1000000;
const long long CORD = 1000000000;

pair<vector<pair<int, int>>, vector<pair<int, int>>> xyz[C + 6], yxz[C + 6], zxy[C + 6];
vector<tuple<int, int, int>> tun;
vector<int> djs;

int F(int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { 
    // cerr << "Union " << x << ' ' << y << endl;
    djs[F(x)] = F(y); }

inline void rit(int &x) {
    char c; bool flag = 0;
    while (c = getchar(), (c < '0' && c != '-') || c > '9');
    c == '-' ? (flag = true, x = 0) : (x = c & 15);
    while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
    if (flag) x = -x;
}

void solve() {
    int n; rit(n);

    for (int i = 0; i <= C + 1; ++i) xyz[i].first.clear(), xyz[i].second.clear();
    for (int i = 0; i <= C + 1; ++i) yxz[i].first.clear(), yxz[i].second.clear();
    for (int i = 0; i <= C + 1; ++i) zxy[i].first.clear(), zxy[i].second.clear();
    tun.resize(n);
    djs.resize(n);

    for (int i = 0; i < n; ++i) {
        int x, y, z; rit(x), rit(y), rit(z);
        tun[i] = make_tuple(x, y, z);
    }

    sort(tun.begin(), tun.end()); tun.resize(unique(tun.begin(), tun.end()) - tun.begin());

    unordered_map<long long, int> tun_xy, tun_xz, tun_yz;
    for (int i = 0; i < (int)tun.size(); ++i) {
        auto [x, y, z] = tun[i];
        // cerr << "tun " << i << " x y z " << x << ' ' << y << ' ' << z << endl;

        if (x == -1) {
            yxz[y].first.emplace_back(i, z);
            zxy[z].first.emplace_back(i, y);
            tun_yz[y * CORD + z] = i;
        } else if (y == -1) {
            xyz[x].first.emplace_back(i, z);
            zxy[z].second.emplace_back(i, x);
            tun_xz[x * CORD + z] = i;
        } else {
            xyz[x].second.emplace_back(i, y);
            yxz[y].second.emplace_back(i, x);
            tun_xy[x * CORD + y] = i;
        }
    }

    auto _second_cmp = [&] (const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    };

    iota(djs.begin(), djs.end(), 0);
    for (int i = 1; i <= C; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (xyz[i + j].first.size() && xyz[i].second.size()) {
                U(xyz[i + j].first[0].first, xyz[i].second[0].first);
                for (int k = 1; k < (int)xyz[i + j].first.size(); ++k) 
                    U(xyz[i + j].first[k - 1].first, xyz[i + j].first[k].first);
                for (int k = 1; k < (int)xyz[i].second.size(); ++k) 
                    U(xyz[i].second[k - 1].first, xyz[i].second[k].first);
            }
            if (xyz[i].first.size() && xyz[i + j].second.size()) {
                U(xyz[i].first[0].first, xyz[i + j].second[0].first);
                for (int k = 1; k < (int)xyz[i].first.size(); ++k) 
                    U(xyz[i].first[k - 1].first, xyz[i].first[k].first);
                for (int k = 1; k < (int)xyz[i + j].second.size(); ++k) 
                    U(xyz[i + j].second[k - 1].first, xyz[i + j].second[k].first);
            }
            if (yxz[i + j].first.size() && yxz[i].second.size()) {
                U(yxz[i + j].first[0].first, yxz[i].second[0].first);
                for (int k = 1; k < (int)yxz[i + j].first.size(); ++k) 
                    U(yxz[i + j].first[k - 1].first, yxz[i + j].first[k].first);
                for (int k = 1; k < (int)yxz[i].second.size(); ++k) 
                    U(yxz[i].second[k - 1].first, yxz[i].second[k].first);
            }
            if (yxz[i].first.size() && yxz[i + j].second.size()) {
                U(yxz[i].first[0].first, yxz[i + j].second[0].first);
                for (int k = 1; k < (int)yxz[i].first.size(); ++k) 
                    U(yxz[i].first[k - 1].first, yxz[i].first[k].first);
                for (int k = 1; k < (int)yxz[i + j].second.size(); ++k) 
                    U(yxz[i + j].second[k - 1].first, yxz[i + j].second[k].first);
            }
            if (zxy[i + j].first.size() && zxy[i].second.size()) {
                U(zxy[i + j].first[0].first, zxy[i].second[0].first);
                for (int k = 1; k < (int)zxy[i + j].first.size(); ++k) 
                    U(zxy[i + j].first[k - 1].first, zxy[i + j].first[k].first);
                for (int k = 1; k < (int)zxy[i].second.size(); ++k) 
                    U(zxy[i].second[k - 1].first, zxy[i].second[k].first);
            }
            if (zxy[i].first.size() && zxy[i + j].second.size()) {
                U(zxy[i].first[0].first, zxy[i + j].second[0].first);
                for (int k = 1; k < (int)zxy[i].first.size(); ++k) 
                    U(zxy[i].first[k - 1].first, zxy[i].first[k].first);
                for (int k = 1; k < (int)zxy[i + j].second.size(); ++k) 
                    U(zxy[i + j].second[k - 1].first, zxy[i + j].second[k].first);
            }
        }

        sort(xyz[i].first.begin(), xyz[i].first.end(), _second_cmp);
        for (int j = 1; j < (int)xyz[i].first.size(); ++j) 
            if (xyz[i].first[j - 1].second + 1 == xyz[i].first[j].second)
                U(xyz[i].first[j - 1].first, xyz[i].first[j].first);
        sort(xyz[i].second.begin(), xyz[i].second.end(), _second_cmp);
        for (int j = 1; j < (int)xyz[i].second.size(); ++j) 
            if (xyz[i].second[j - 1].second + 1 == xyz[i].second[j].second)
                U(xyz[i].second[j - 1].first, xyz[i].second[j].first);

        sort(yxz[i].first.begin(), yxz[i].first.end(), _second_cmp);
        for (int j = 1; j < (int)yxz[i].first.size(); ++j) 
            if (yxz[i].first[j - 1].second + 1 == yxz[i].first[j].second)
                U(yxz[i].first[j - 1].first, yxz[i].first[j].first);
        sort(yxz[i].second.begin(), yxz[i].second.end(), _second_cmp);
        for (int j = 1; j < (int)yxz[i].second.size(); ++j) 
            if (yxz[i].second[j - 1].second + 1 == yxz[i].second[j].second)
                U(yxz[i].second[j - 1].first, yxz[i].second[j].first);

        sort(zxy[i].first.begin(), zxy[i].first.end(), _second_cmp);
        for (int j = 1; j < (int)zxy[i].first.size(); ++j) 
            if (zxy[i].first[j - 1].second + 1 == zxy[i].first[j].second)
                U(zxy[i].first[j - 1].first, zxy[i].first[j].first);
        sort(zxy[i].second.begin(), zxy[i].second.end(), _second_cmp);
        for (int j = 1; j < (int)zxy[i].second.size(); ++j) 
            if (zxy[i].second[j - 1].second + 1 == zxy[i].second[j].second)
                U(zxy[i].second[j - 1].first, zxy[i].second[j].first);
    }

    auto GetId = [&] (int x, int y, int z) {
        int o = -1;
        { auto it = tun_xy.find(x * CORD + y);
        if (it != tun_xy.end()) o = it->second; }
        { auto it = tun_xz.find(x * CORD + z);
        if (it != tun_xz.end()) o = it->second; }
        { auto it = tun_yz.find(y * CORD + z);
        if (it != tun_yz.end()) o = it->second; }

        assert(o != -1);
        return o;
    };

    int q; rit(q); while (q--) {
        int x1, y1, z1, x2, y2, z2; rit(x1), rit(y1), rit(z1), rit(x2), rit(y2), rit(z2);
        int sid = GetId(x1, y1, z1), tid = GetId(x2, y2, z2);
        // cerr << "sid tid " << sid << ' ' << tid << endl;
        
        if (F(sid) == F(tid)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; rit(t); while (t--) {
        solve();
    }
}

