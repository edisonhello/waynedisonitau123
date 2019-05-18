#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
char s[maxn];
int n;
// vector<int> pos[maxn];
vector<pair<int, int>> seg;
vector<int> prv[maxn];
long long dp[maxn];
bool isleft[maxn];

/* void solve(int l, int r) {
    stack<int> st;
    int n = strlen(s);
    for (int i = l; i <= r; ++i) {
        if (st.size() && s[st.top()] == s[i]) {
            seg.emplace_back(st.top(), i);
            st.pop();
        } else {
            st.push(i);
        }
    }
} */

int to[maxn];

int fly(int x) {
    // cout << "fly: " << x << endl;
    // if (x == to[x]) return x;
    // else return to[x] = fly(to[x]);
    return to[x];
}

void go(int x) {
    // cout << "go from " << x << endl;
    stack<int> st;
    while (x < n) {
        // cout << "now x = " << x << endl;
        if (st.size() && s[x] == s[st.top()]) {
            seg.emplace_back(st.top(), x);
            // cout << "seg: " << st.top() << " to " << x << endl;
            to[st.top()] = x;
            // cout << "to[" << st.top() << "] = " << x << endl;
            // cout << "assign " << "to[" << st.top() <<"] as " << x << endl;
            st.pop();
        } else {
            // cout << "now fly(" << x << ") = " << fly(x) << endl;
            if (fly(x) != x) {
                x = fly(x);
            } else {
                st.push(x);
                isleft[x] = 1;
            }
        }
        ++x;
        // cout << "next x = " << x << endl;
    }
    while (st.size()) {
        // cout << "st left " << st.top() << endl;
        to[st.top()] = n;
        st.pop();
    }
}

int main() {
    scanf("%s", s);
    n = strlen(s);
    /* for (int i = 0; i < n; ++i) {
        pos[s[i] - 'a'].push_back(i);
    }
    solve(0, n - 1);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j + 1 < (int)pos[i].size(); ++j) {
            solve(pos[i][j], pos[i][j + 1]);
        }
    } */
    for (int i = 0; i < maxn; ++i) to[i] = i;
    for (int i = 0; i < n; ++i) {
        if (isleft[i]) continue;
        go(i);
    }
    for (int i = 0; i < (int)seg.size(); ++i) {
        prv[seg[i].second].push_back(seg[i].first);
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        sort(prv[i].begin(), prv[i].end());
        prv[i].resize(unique(prv[i].begin(), prv[i].end()) - prv[i].begin());
        for (int j = 0; j < (int)prv[i].size(); ++j) {
            dp[i] += dp[prv[i][j] - 1] + 1;
        }
        ans += dp[i];
    }
    printf("%lld\n", ans);
    return 0;
}
