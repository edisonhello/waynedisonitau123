#include <bits/stdc++.h>
using namespace std;

int in16dig(int x) {
    int d = 0;
    while (x) {
        x /= 16;
        ++d;
    }
    return d;
}

string tohex(int x) {
    stack<char> s;
    while (x) {
        int c = x % 16;
        if (c < 10) s.push('0' + c);
        else s.push('A' + c - 10);
        x /= 16;
    }
    string ss;
    while (s.size()) {
        ss += s.top();
        s.pop();
    }
    return ss;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; while (cin >> s) {
        int n = s.size();
        vector<pair<char, int>> v;

        for (int i = 0, j; i < n; i = j) {
            for (j = i; j < n && s[i] == s[j]; ++j) ;
            v.emplace_back(s[i], j - i);
        }
        // cerr << "s n v " << s << ' ' << n << ' ' << v.size() << endl;

        bool output = false;
        auto Output = [&] (const vector<pair<char, int>> v) {
            output = true;
            for (auto &[ch, cnt] : v) {
                cout << ch;
                if (cnt == 1) continue;
                else cout << tohex(cnt);
            }
            cout << endl;
        };

        for (int i = 0; i < (int)v.size(); ++i) {
            auto [ch, cnt] = v[i];

            if (cnt > 1 && in16dig(cnt) == in16dig(cnt - 1)) continue;

            if (cnt == 1) {
                if (i == (int)v.size() - 1) {
                    v.erase(prev(v.end()));
                    Output(v);
                    break;
                } else {
                    if (v[i + 1].first < v[i].first) {
                        v.erase(v.begin() + i);
                        Output(v);
                        break;
                    }
                }
            }
        }

        if (!output) for (int i = (int)v.size() - 1; i >= 0; --i) {
            auto [ch, cnt] = v[i];

            if (cnt == 2) {
                --v[i].second;
                Output(v);
                break;
            }

            if (cnt > 1 && in16dig(cnt) == in16dig(cnt - 1)) continue;

            if (cnt == 1) {
                v.erase(v.begin() + i);
                Output(v);
                break;
            } else {
                --v[i].second;
                Output(v);
                break;
            }
        }

        if (!output) {
            --v[0].second;
            Output(v);
        }
    }
}

