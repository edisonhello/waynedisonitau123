#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x1(n), x2(n), y1(n), y2(n);
    constexpr int kC = 1'000'000'000 + 500;
    vector<int> dx = {0, -kC, kC}, dy = {0, -kC, kC};
    for (int i = 0; i < n; ++i) {
        cin >> x1[i] >> y1[i];
        int w, h;
        cin >> w >> h;
        x2[i] = x1[i] + w;
        y2[i] = y1[i] + h;
        dx.push_back(x1[i]);
        dx.push_back(x2[i]);
        dy.push_back(y1[i]);
        dy.push_back(y2[i]);
    }
    sort(dx.begin(), dx.end());
    sort(dy.begin(), dy.end());
    dy.resize(unique(dy.begin(), dy.end()) - dy.begin());
    dx.resize(unique(dx.begin(), dx.end()) - dx.begin());
    for (int i = 0; i < n; ++i) {
        x1[i] = lower_bound(dx.begin(), dx.end(), x1[i]) - dx.begin();
        x2[i] = lower_bound(dx.begin(), dx.end(), x2[i]) - dx.begin();
        y1[i] = lower_bound(dy.begin(), dy.end(), y1[i]) - dy.begin();
        y2[i] = lower_bound(dy.begin(), dy.end(), y2[i]) - dy.begin();
    }
    const int kZx = lower_bound(dx.begin(), dx.end(), 0) - dx.begin();
    const int kZy = lower_bound(dy.begin(), dy.end(), 0) - dy.begin();
    const int kW = dx.size();
    const int kH = dy.size();
    vector<vector<pair<int, int>>> add(kW), del(kW);
    for (int i = 0; i < n; ++i) {
        add[x1[i]].emplace_back(y1[i], y2[i]);
        del[x2[i]].emplace_back(y1[i], y2[i]);
    }
    vector<int> cover(kH);
    vector<vector<bool>> color(kW, vector<bool>(kH));
    for (int i = 0; i < kW; ++i) {
        for (auto &u : del[i]) {
            for (int j = u.first; j < u.second; ++j) cover[j]--;
        }
        for (auto &u : add[i]) {
            for (int j = u.first; j < u.second; ++j) cover[j]++;
        }
        for (int j = 0; j < kH; ++j) {
            color[i][j] = cover[j] > 0;
        }
    }
    enum Color { BLACK = 0, WHITE = 1 };
    vector<pair<double, pair<Color, int>>> event;

    constexpr double kInf = 1E15;

    auto GetDist = [&](int x, int y) {
        double a = kInf, b = -kInf;
        for (int xd = 0; xd < 2; ++xd) {
            for (int yd = 0; yd < 2; ++yd) {
                int cx = dx[x + xd];
                int cy = dy[y + yd];
                double dist = hypot(cx, cy);
                a = min(a, dist);
                b = max(b, dist);
            }
        } 
        if (x <= kZx && x + 1 >= kZx && y <= kZy && y + 1 >= kZy) {
            a = 0.0;
        } else if (x <= kZx && x + 1 >= kZx) {
            if (y > kZy) {
                a = min(a, 1.0 * abs(dy[y]));
            }
            if (y + 1 < kZy) {
                a = min(a, 1.0 * abs(dy[y + 1]));
            }
        } else if (y <= kZy && y + 1 >= kZy) {
            if (x > kZx) {
                a = min(a, 1.0 * abs(dx[x]));
            }
            if (x + 1 < kZx) {
                a = min(a, 1.0 * abs(dx[x + 1]));
            }
        }
        return make_pair(a, b);
    };

    for (int i = 0; i + 1 < kW; ++i) {
        for (int j = 0; j + 1 < kH; ++j) {
            double a, b;
            tie(a, b) = GetDist(i, j);
            assert(a <= b);
            // cout << "i = " << i << " j = " << j << " color[i][j] = " << color[i][j] << endl;
            // cout << "a = " << a << " b = " << b << endl;
            if (color[i][j]) {
                event.emplace_back(a, make_pair(BLACK, +1));
                event.emplace_back(b, make_pair(BLACK, -1));
            } else {
                event.emplace_back(a, make_pair(WHITE, +1));
                event.emplace_back(b, make_pair(WHITE, -1));
            }
        }
    }
    sort(event.begin(), event.end());
    double prv = 0.0;
    vector<int> cnt(2);
    int status = 0;
    constexpr double kEps = 1E-9;
    double black = 0.0, gray = 0.0;
    for (auto &e : event) {
        // cout << "status = " << status << endl;
        double pos = e.first;
        if (status == 1) black += pos * pos - prv * prv; 
        else if (status == 3) gray += pos * pos - prv * prv;
        if (e.second.second == -1) {
            if (--cnt[e.second.first] == 0) {
                status ^= (1 << e.second.first);
            } 
        } else {
            if (cnt[e.second.first]++ == 0) {
                status ^= (1 << e.second.first);
            }
        }
        prv = pos;
    }
    constexpr double kPi = acos(-1);
    cout << fixed << setprecision(12) << black * kPi << "\n" << gray * kPi << "\n";
    return 0;
}

