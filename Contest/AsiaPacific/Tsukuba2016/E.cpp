#include <bits/stdc++.h>
using namespace std;

namespace parse {

bool ERROR;

int E(string &s, int l, int r);

int B(string &s, int l, int r) {
    if (ERROR) return 0;
    if (l > r) return 0;
    if (s[l] == '0') return B(s, l + 1, r);
    if (s[l] == '1') return B(s, l + 1, r);
    ERROR = true;
    return 0;
}

int N(string &s, int l, int r) {
    if (ERROR) return 0;
    if (l > r) { ERROR = true; return 0; }
    if (s[l] == '0') {
        if (l + 1 <= r) { ERROR = true; return 0; }
        return 0;
    } else if (s[l] == '1') {
        B(s, l + 1, r);
        if (ERROR) return 0;
        int i = l;
        int x = 0;
        while (i <= r) {
            x = x * 2 + s[i] - '0';
            ++i;
        }
        return x;
    }
    ERROR = true;
    return 0;
}

int F(string &s, int l, int r) {
    if (l > r) ERROR = true;
    if (ERROR) return 0;
    if (s[l] == '0' || s[l] == '1') return N(s, l, r);
    if (s[l] == '-') return -F(s, l + 1, r);
    if (s[l] == '(' && s[r] == ')') return E(s, l + 1, r - 1);
    ERROR = true;
    return 0;
}

int T(string &s, int l, int r) {
    if (ERROR) return 0;
    int level = 0;
    for (int i = r; i >= l; --i) {
        if (s[i] == ')') ++level;
        else if (s[i] == '(') --level;
        if (level) continue;

        if (s[i] == '*') {
            return T(s, l, i - 1) * F(s, i + 1, r);
        }
    }
    return F(s, l, r);
}

int E(string &s, int l, int r) {
    if (ERROR) return 0;
    int level = 0;
    for (int i = r; i >= l; --i) {
        if (s[i] == ')') ++level;
        else if (s[i] == '(') --level;
        if (level) continue;

        if (s[i] == '+') {
            return E(s, l, i - 1) + T(s, i + 1, r);
        } else if (s[i] == '-' && (s[i - 1] == '0' || s[i - 1] == '1' || s[i - 1] == ')')) {
            return E(s, l, i - 1) - T(s, i + 1, r);
        }
    }
    return T(s, l, r);
}

int main(string &s) {
    // cerr << "parse::main , s = " << s << endl;
    ERROR = false;

    int cntEQ = 0;
    int pos = -1;
    for (int i = 0; i < (int)s.size(); ++i) if (s[i] == '=') {
        pos = i;
        ++cntEQ;
    }

    if (cntEQ != 1) return 0;

    int res1 = E(s, 0, pos - 1);
    int res2 = E(s, pos + 1, s.size() - 1);

    // cerr << "parse::main , res = " << res1 << " " << res2 << ", error = " << ERROR << endl;

    if (res1 != res2) ERROR = true;

    return !ERROR;
}

}

int cnt;

char charset[] = {'0', '1', '+', '-', '*', '(', ')', '='};
bool used[8];

void dfs(string &s, int idx) {
    if (idx == s.size()) {
        cnt += parse::main(s);
        return;
    }
    if (isalpha(s[idx])) {
        string t = s;
        for (int i = 0; i < 8; ++i) if (!used[i]) {
            used[i] = 1;
            for (int z = idx; z < (int)s.size(); ++z) if (s[z] == s[idx]) t[z] = charset[i];
            dfs(t, idx + 1);
            used[i] = 0;
        }
    } else dfs(s, idx + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;

    dfs(s, 0);

    cout << cnt << endl;
}
