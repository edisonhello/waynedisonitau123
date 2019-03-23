#include <bits/stdc++.h>
using namespace std;

struct answer {
    long long cnt[26];
    long long stop;
    answer() { memset(this, 0, sizeof(answer)); }
};

answer operator + (const answer &a, const answer &b) {
    answer rt;
    for (int i = 0; i < 26; ++i) {
        rt.cnt[i] = a.cnt[i] + b.cnt[i];
    }
    return rt;
}

string s; 

answer dfs(int l, int r, int k) {
    answer ret;
    ret.stop = 1;
    while (l <= r) {
        if (s[l] >= 'a' && s[l] <= 'z') {
            ++ret.cnt[s[l] - 'a'];
            ++l;
            if (s[l] == 'a') --k;
            if (k <= 0) return ret;
        } else {
            int dr = l;
            while (s[dr] >= '0' && s[dr] <= '9') ++dr; --dr;
            long long rep = stoi(s.substr(l, dr - l + 1));
            l = dr + 1; ++dr;
            int brack = 0;
            while (true) {
                if (s[dr] == '(') ++brack;
                else if (s[dr] == ')') --brack;
                if (brack == 0) break;
                ++dr;
            }
            answer rt = dfs(l + 1, dr - 1, k);
            if (rt.stop) {
                ret = ret + rt;
                ret.stop = 1;
                return ret;
            } else {
                if (
            }
        }
    }
}

int main() {
    cin >> s;
    int k; cin >> k;
    answer ans = dfs(0, s.size() - 1, k);
}
