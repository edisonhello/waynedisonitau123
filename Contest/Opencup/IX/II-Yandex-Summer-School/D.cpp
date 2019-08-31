#include <bits/stdc++.h>
using namespace std;

string s;

int match[1000006];
bool bye[1000006];
char prevop[1000006], nextop[1000006];

pair<int, int> dfs(int L, int R) {
    // cerr << "in dfs " << L << " " << R << endl;
    if (L > R) return pair<int, int>(0, 0);
    if (L == R) return pair<int, int>(0, 1);
    if (match[L] == R && match[R] == L) {
        bye[L] = bye[R] = 1;
        return dfs(L + 1, R - 1);
    }
    int rt = 0, terms = 0;
    for (int i = L; i <= R; i = (match[i] ? match[i] + 1 : i + 1)) {
        // cerr << "i = " << i << " , match = " << match[i] << endl;
        if (match[i]) {
            assert(s[i] == '(');
            int pm, sterm;
            tie(pm, sterm) = dfs(i + 1, match[i] - 1);
            bool breaked = 0;
            char pop = s[i - 1], nop = s[match[i] + 1];
            // cerr << "i = " << i << " pop = " << pop << ", nop = " << nop << endl;
            if (i == 0 || pop == '+' || pop == '(') {
                // cerr << "pop is +" << endl;
                if (match[i] == (int)s.size() - 1 || nop == '+' || nop == '-' || nop == ')') {
                    breaked = 1;
                }
                else if (nop == '*' || nop == '/') {
                    if (!pm) {
                        breaked = 1;
                    }
                }
            } else if (pop == '-') {
                if (!pm) {
                    breaked = 1;
                }
            } else if (pop == '*') {
                if (!pm) {
                    breaked = 1;
                }
            } else {
                assert(pop == '/');
                // cerr << "sterm = " << sterm << endl;
                if (sterm == 1) {
                    breaked = 1;
                }
            }
            if (breaked) {
                rt += pm;
                terms += sterm;
                bye[i] = bye[match[i]] = 1;
            } else {
                ++terms;
            }
        } else if (s[i] == 'x') {
            ++terms;
        } else if (s[i] == '+' || s[i] == '-') {
            ++rt;
        }
    }
    return make_pair(rt, terms);
}

string meow() {
    int n = s.size();
    for (int i = 0; i < n; ++i) match[i] = prevop[i] = nextop[i] = bye[i] = 0;
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') st.push(i);
        else if (s[i] == ')') {
            match[st.top()] = i;
            match[i] = st.top();
            st.pop();
        } else if (s[i] != 'x') {
            // cerr << "prevop nextop " << i << " = " << s[i] << endl;
            prevop[i] = nextop[i] = s[i];
        }
    }
    prevop[0] = nextop[n - 1] = '+';
    for (int i = 1; i < n; ++i) if (!prevop[i]) prevop[i] = prevop[i - 1];
    for (int i = n - 2; i >= 0; --i) if (!nextop[i]) nextop[i] = nextop[i + 1];
    // for (int i = 0; i < n; ++i) cout << char(prevop[i]); cout << endl;
    // for (int i = 0; i < n; ++i) cout << char(nextop[i]); cout << endl;

    dfs(0, n - 1);
    string t;
    for (int i = 0; i < n; ++i) if (!bye[i]) t += s[i];
    return t;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        cin >> s;
        cout << meow() << '\n';
    }
}
