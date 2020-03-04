#include <bits/stdc++.h>
using namespace std;

string rotate(const string &s) {
    int n = (int)s.size();
    string t = s + s;
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && t[i + k] == t[j + k]) ++k;
        if (t[i + k] >= t[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) ++j;
    }
    int pos = i < n ? i : j;
    return t.substr(pos, n);
}

string solve(string s) {
    int n = (int)s.size();
    string t = "";
    t += s[0];
    bool ok = 0;
    for (int i = 1, j = 0; i < n; ++i) {
        // if (s[j] > s[0]) j = 0, ok = 1;
        if (s[j] == s[i] || ok) t += t[j++];
        else if (s[i] > t[j]) {
            ok = 1;
            t += s[j++];
        }
        else t += s[i], j = 0;
    }
    return t;
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    int t; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        string s; cin >> s;
        int n = (int)s.size();
        string t = solve(s);
        cout << "Case #" << tc << ": ";
        string r = rotate(t);
        if (t == r) {
            cout << t << endl;
            continue;
        }

        int j = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (t[i] != '0') {
                --t[i];
                j = i + 1;
                break;
            }
        }
        string p = "";
        for (int i = 0; i < n; ++i) {
            if (t[i] != '0') {
                p += t[i];
            } else {
                break;
            }
        }
        --p.back();
        int k = 0;
        while (j < n) {
            t[j] = p[k];
            ++k;
            if (k == p.size()) k = 0;
            ++j;
        }
        r = rotate(t);
        if (t == r) {
            cout << t << endl;
        } else {
            assert(t[n - 1] != '0');
            --t[n - 1];
            cout << t << endl;
        }
    }
    return 0;
}
