#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        string s; cin >> s;
        int k; cin >> k;
        function<string(string, int, int)> DfsMax = [&] (string s, int k, int now) {
            if (k == 0) return s;
            if (now >= s.size()) return s;
            int cur = now;
            for (int j = now + 1; j < s.size(); ++j) if (s[j] >= s[cur]) cur = j;
            string rt = s;
            if (s[cur] != s[now]) {
                for (int j = now + 1; j < s.size(); ++j) if (s[j] == s[cur]) {
                    swap(s[j], s[now]);
                    string t = DfsMax(s, k - 1, now + 1);
                    rt = max(rt, t);
                    swap(s[j], s[now]);
                }
            }
            rt = max(rt, DfsMax(s, k, now + 1));
            return rt;
        };
        auto GetMax = [&] (string s, int k) {
            string t = DfsMax(s, k, 0);
            return t;
        };
        function<string(string, int, int)> DfsMin = [&] (string s, int k, int now) {
            if (k == 0) return s;
            if (now >= s.size()) return s;
            int cur = now;
            for (int j = now + 1; j < s.size(); ++j) if (s[j] <= s[cur] && (now || s[j] != '0')) cur = j;
            string rt = s;
            if (s[cur] != s[now]) {
                for (int j = now + 1; j < s.size(); ++j) if (s[j] == s[cur]) {
                    swap(s[j], s[now]);
                    string t = DfsMin(s, k - 1, now + 1);
                    rt = min(rt, t);
                    swap(s[j], s[now]);
                }
            }
            rt = min(rt, DfsMin(s, k, now + 1));
            return rt;
        };
        auto GetMin = [&] (string s, int k) {
            string t = DfsMin(s, k, 0);
            return t;
        };
        cout << GetMin(s, k) << ' ' << GetMax(s, k) << endl;
    }
}

