#include <bits/stdc++.h>
using namespace std;

struct answer {
    long long cnt[26];
    answer() { memset(this, 0, sizeof(answer)); }
} store[100005];

answer operator + (const answer &a, const answer &b) {
    answer rt;
    for (int i = 0; i < 26; ++i) {
        rt.cnt[i] = a.cnt[i] + b.cnt[i];
        if (a.cnt[i] == -1 || b.cnt[i] == -1 || rt.cnt[i] > 1000000000000) rt.cnt[i] = -1;
    }
    return rt;
}

string s; 

answer dfs(int l, int r) {
    // cerr << "dfs " << l << " " << r << endl;
    int ol = l;
    answer ret;
    while (l <= r) {
        if (s[l] >= 'a' && s[l] <= 'z') {
            if (ret.cnt[s[l] - 'a'] == -1);
            else {
                ++ret.cnt[s[l] - 'a'];
                if (ret.cnt[s[l] - 'a'] > 1000000000000) ret.cnt[s[l] - 'a'] = -1;
            }
            ++l;
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
            answer rt = dfs(l + 1, dr - 1);
            for (int i = 0; i < 26; ++i) {
                if (rt.cnt[i] == -1) continue;
                rt.cnt[i] *= rep;
                if (rt.cnt[i] > 1000000000000) rt.cnt[i] = -1;
            }
            ret = ret + rt;
            l = dr + 1;
        }
    }
    return store[ol] = ret;
}

answer dfs2(int l, int r, int &k) {
    // cerr << "dfs2 " << l << " " << r << " , k = " << k << endl;
    answer now = store[l];
    if (now.cnt[0] != -1 && now.cnt[0] < k) {
        k -= now.cnt[0];
        // cerr << "return " << now.cnt[0] << " " << now.cnt[1] << " " << now.cnt[2] << endl;
        return now;
    }
    answer ret;
    while (l <= r && k > 0) {
        if (s[l] >= 'a' && s[l] <= 'z') {
            ++ret.cnt[s[l] - 'a'];
            if (s[l] == 'a') --k;
            ++l;
        } else {
            int ool = l;
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
            int beforek = k;
            answer rt = dfs2(l + 1, dr - 1, k);
            int usek = beforek - k;
            int runtime = min(k / usek, int(rep) - 1);
            bool nojump = false;
            if (runtime * usek == k && runtime > 0) { --runtime; nojump = true; }
            // cerr << l + 1 << " to " << dr - 1 << " can run " << runtime << " times" << endl;
            // cerr << "k left " << k << " , usek = " << usek << endl;
            k -= runtime * usek;
            answer tt;
            for (int i = 0; i < 26; ++i) {
                tt.cnt[i] = rt.cnt[i] * (runtime + 1);
                if (tt.cnt[i] < 0 || tt.cnt[i] > 1000000000000) tt.cnt[i] = -1;
            }
            ret = ret + tt;
            if (nojump) l = ool;
            else l = dr + 1;
        }
    }
    // cerr << "return " << now.cnt[0] << " " << now.cnt[1] << " " << now.cnt[2] << endl;
    return ret;
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("az.in", "r", stdin);
    freopen("az.out", "w", stdout);
#endif
    cin >> s;
    int k; cin >> k;
    dfs(0, s.size() - 1);
    answer ans = dfs2(0, s.size() - 1, k);
    for (int i = 0; i < 26; ++i) {
        if (ans.cnt[i]) {
            cout << char(i + 'a') << " " << ans.cnt[i] << endl;
        }
    }
}
