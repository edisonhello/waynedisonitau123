#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    int64_t p, q;

    Fraction() = default;

    template <typename T>
    Fraction(T x) : p(x), q(1) {}

    Fraction(int64_t p, int64_t q) : p(p), q(q) {}

    void Reduce() {
        int64_t g = __gcd(p, q);
        p /= g;
        q /= g;
    }

    Fraction operator+(const Fraction &rhs) const {
        return Fraction(p * rhs.q + q * rhs.p, rhs.p * rhs.q);
    }
    bool operator<(const Fraction &rhs) const {
        return p * rhs.q < q * rhs.p;
    }
    bool operator==(const Fraction &rhs) const {
        return p * rhs.q == q * rhs.p;
    }
};

int main() {
    int T = 0;
    int64_t l, s, d, n;
    while (cin >> l >> s >> d >> n) {
        if (l == 0 && s == 0 && d == 0 && n == 0) break;
        vector<int> loc(n), spd(n);
        d *= 4;
        l *= 4;
        for (int i = 0; i < n; ++i) {
            cin >> loc[i] >> spd[i];
            loc[i] *= 4;
        }
        int64_t res = 0;
        double dans = 0.0;
        bool first = true;
        while (true) {
            vector<pair<int64_t, int>> event;
            int same = 0;
            for (int i = 0; i < n; ++i) {
                // if (loc[i] > d) continue;
                if (loc[i] >= d) continue;
                if (spd[i] > s) {
                    if (loc[i] <= l) {
                        int64_t x = (max(int64_t(first ? 0 : 1), l - loc[i] - 4) + spd[i] - s - 1) / (spd[i] - s);
                        if (x * (spd[i] - s) <= l - loc[i]) {
                            event.emplace_back(x, i);
                        }
                    }
                }
                if (s > spd[i]) {
                    if (loc[i] >= l - 4) {
                        int64_t x = (max(int64_t(first ? 0 : 1), loc[i] - l) + s - spd[i] - 1) / (s - spd[i]);
                        if (x * (s - spd[i]) <= (loc[i] + 4 - l)) {
                            event.emplace_back(x, i);
                        }
                    }
                }
                if (s == spd[i] && loc[i] >= l - 4 && loc[i] <= l) ++same;
            }
            if (event.empty()) {
                dans = (res + static_cast<double>(d - l) / s) / 4;
                break;
            }
            sort(event.begin(), event.end());
            int64_t t = event[0].first;
            // cout << "t = " << t << endl;
            if (l + s * t > d) {
                dans = (res + static_cast<double>(d - l) / s) / 4;
                break;
            }
            res += t;
            l += s * t;
            for (int i = 0; i < n; ++i) {
                loc[i] += t * spd[i];
            }
            int64_t sum = (same + 1) * s;
            int cnt = same + 1;
            for (int i = 0; i < event.size(); ++i) {
                if (event[i].first == event[0].first) {
                    sum += spd[event[i].second];
                    cnt++;
                }
            }
            s = sum / cnt;
            first = false;
        }
        cout << fixed << setprecision(4) << "Case " << ++T << ": ";
        cout << "Anna reaches her destination at time " << dans << " at a speed of " << s << "\n";
    }
    return 0;
}

