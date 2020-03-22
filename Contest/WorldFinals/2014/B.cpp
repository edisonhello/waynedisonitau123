#include <bits/stdc++.h>
using namespace std;

constexpr int64_t kInf = 1'000'000'000'000'000;

struct Line {
    int64_t a, b;

    int64_t Eval(int64_t x) const { return a * x + b; }
};

bool Check(Line l1, Line l2, Line l3) {
    return (l1.b - l2.b) * (l3.a - l2.a) >= (l2.b - l3.b) * (l2.a - l1.a);
    // return (l1.b - l2.b) / (l2.a - l1.a) >= (l2.b - l3.b) / (l3.a - l2.a);
}

vector<int64_t> BuildKnapsack(const vector<tuple<int, int, int>> &dis, int w) {
    vector<int64_t> dp(w + 1, -kInf);
    dp[0] = 0;
    for (int i = 0; i < dis.size(); ++i) {
        vector<int64_t> nxt(w + 1, -kInf);
        int wi = get<0>(dis[i]);
        int ti = get<1>(dis[i]);
        int dt = get<2>(dis[i]);
        vector<vector<int64_t>> rd(wi);
        for (int j = 0; j <= w; ++j) {
            rd[j % wi].push_back(dp[j]);
        }
        for (int j = 0; j < wi; ++j) {
            deque<Line> dq;
            for (int p = 0; p < rd[j].size(); ++p) {
                if (rd[j][p] != -kInf) {
                    Line ins{2 * p * dt, 2 * rd[j][p] - 2LL * p * ti - (1LL * p * p + p) * dt};
                    while (dq.size() >= 2) {
                        Line l1 = dq[dq.size() - 1];
                        Line l2 = dq[dq.size() - 2];
                        if (Check(l2, l1, ins)) dq.pop_back();
                        else break;
                    }
                    dq.push_back(ins);
                }
                if (!dq.empty()) {
                    while (dq.size() >= 2 && dq[1].Eval(p) >= dq[0].Eval(p)) dq.pop_front();
                    int64_t v = dq[0].Eval(p);
                    int64_t res = v + (-1LL * p * p + p) * dt + 2LL * p * ti;
                    assert(res % 2 == 0);
                    nxt[p * wi + j] = res / 2;
                }
                // int64_t res = -kInf;
                // for (int k = 0; k <= p; ++k) {
                //     if (rd[j][k] == -kInf) continue;
                //     res = max(res, rd[j][k] - (p - k) * (p - k - 1) / 2 * dt + (p - k) * ti);
                // }
                // nxt[p * wi + j] = res;
            }
        }

        // for (int k = 0; k <= w; ++k) {
        //     for (int j = 0; j * wi <= w; ++j) {
        //         if (k >= j * wi) {
        //             if (dp[k - j * wi] == -kInf) continue;
        //             nxt[k] = max(nxt[k], dp[k - j * wi] - j * (j - 1) / 2 * dt + j * t);
        //         }
        //     }
        // }
        dp = nxt;
    }
    return dp;
}

int main() {
    int d, w;
    cin >> d >> w;
    vector<tuple<int, int, int>> dis;
    vector<pair<int, int>> cont;
    int kv = -1;
    for (int i = 0; i < d; ++i) {
        char type;
        cin >> type;
        if (type == 'D') {
            int w, t, dt;
            cin >> w >> t >> dt;
            dis.emplace_back(w, t, dt);
        } else {
            int t, dt;
            cin >> t >> dt;
            if (dt == 0) {
                kv = max(kv, t);
            } else {
                cont.emplace_back(t, dt);
            }
        }
    }
    auto dp = BuildKnapsack(dis, w);
    // for (int i = 0; i <= w; ++i) cout << dp[i] << " ";
    // cout << endl;
    // return 0;
    if (kv == -1 && cont.empty() && dp[w] == -kInf) {
        cout << "impossible\n";
        return 0;
    }
    if (kv == -1 && cont.empty()) {
        cout << dp[w] << endl;
        return 0;
    }
    constexpr int kIter = 80;
    double res = -1e18;
    for (int i = 0; i <= w; ++i) {
        if (dp[i] == -kInf) continue;
        // cout << "i = " << i << " dp[i] = " << dp[i] << endl;
        if (kv == -1) {
            double l = -1e9, r = 1e9;
            for (int it = 0; it < kIter; ++it) {
                double lambda = 0.5 * (l + r);
                double wsum = 0.0;
                for (int j = 0; j < cont.size(); ++j) {
                    double x = (cont[j].first - lambda) / cont[j].second;
                    if (x < 0) x = 0;
                    wsum += x;
                }
                if (wsum >= w - i) l = lambda;
                else r = lambda;
            }
            double sum = dp[i];
            double lambda = 0.5 * (l + r);
            for (int j = 0; j < cont.size(); ++j) {
                double x = (cont[j].first - lambda) / cont[j].second;
                if (x < 0) x = 0;
                sum += x * cont[j].first - x * x / 2 * cont[j].second;
            }
            res = max(res, sum);
        } else {
            double l = kv, r = 1e9;
            for (int it = 0; it < kIter; ++it) {
                double lambda = 0.5 * (l + r);
                double wsum = 0.0;
                bool ok = true;
                int kv = -1;
                for (int j = 0; j < cont.size(); ++j) {
                    double x = (cont[j].first - lambda) / cont[j].second;
                    if (x < 0) x = 0;
                    wsum += x;
                }
                if (wsum >= w - i) l = lambda;
                else r = lambda;
            }
            double lambda = 0.5 * (l + r);
            double wsum = 0.0;
            double sum = dp[i];
            for (int j = 0; j < cont.size(); ++j) {
                double x = (cont[j].first - lambda) / cont[j].second;
                if (x < 0) x = 0;
                wsum += x;
                sum += x * cont[j].first - x * x / 2 * cont[j].second;
            }
            double left = w - i - wsum;
            sum += left * kv;
            res = max(res, sum);
        }
    }
    cout << fixed << setprecision(9) << res << "\n";
}

