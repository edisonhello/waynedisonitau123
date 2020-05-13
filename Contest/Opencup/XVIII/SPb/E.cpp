#include <bits/stdc++.h>
using namespace std;

// ostream &operator<<(ostream &s, __int128 w) {
//     vector<int> stk;
//     if (w == 0) {
//         return s << 0;
//     }
//     while (w > 0) {
//         stk.push_back(w % 10);
//         w /= 10;
//     }
//     while (!stk.empty()) {
//         s << stk.back();
//         stk.pop_back();
//     }
//     return s;
// }

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int64_t g = 0;
        for (int i = 2; i < s.size(); ++i) {
            g = g * 10 + (s[i] - '0');
        }
        pair<int64_t, int64_t> l{0, 1}, r{1, 1};

        auto Check = [&](int64_t a, int64_t b) {
            // cout << "a = " << a << " b = " << b << endl;
            __int128 v = (__int128)1000000000000000000 * a;
            __int128 w = v / b;
            // cout << "w = " << w << endl;
            if ((v % b) * 2 >= b) w++;
            return w == g ? 0 : w > g ? 1 : -1;
        };

        if (g == 0) {
            cout << 0 << " " << 1 << "\n";
            continue;
        }

        while (true) {
            pair<int64_t, int64_t> m{l.first + r.first, l.second + r.second};
            int b = Check(m.first, m.second);
            if (b == 0) {
                cout << m.first << " " << m.second << "\n";
                break;
            }
            // cout << "b = " << b << endl;
            if (b == -1) {
                int k = 1;
                for (int d = 30; d >= 0; --d) {
                    int nk = k + (1 << d);
                    pair<int64_t, int64_t> m{l.first + r.first * nk, l.second + r.second * nk};
                    if (Check(m.first, m.second) == -1) k = nk;
                }
                l.first += k * r.first;
                l.second += k * r.second;
            } else {
                int k = 1;
                for (int d = 30; d >= 0; --d) {
                    int nk = k + (1 << d);
                    pair<int64_t, int64_t> m{l.first * nk + r.first, l.second * nk + r.second};
                    if (Check(m.first, m.second) == 1) k = nk;
                }
                r.first += k * l.first;
                r.second += k * l.second;
            }
        }
    }
}

