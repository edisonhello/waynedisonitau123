#include <bits/stdc++.h>
using namespace std;

bool isop(pair<int, int> p) {
    return p.first;
}

pair<int, int> meow(pair<int, int> op, pair<int, int> a, pair<int, int> b) {
    if (op.first == 1) return make_pair(0, a.second + b.second);
    if (op.first == 2) return make_pair(0, a.second - b.second);
    if (op.first == 3) return make_pair(0, a.second * b.second);
    assert(0);
    return make_pair(-1, -1);
}

void solve() {
    int n; cin >> n;
    vector<pair<int, int>> st;

    while (n--) {
        string s; cin >> s;
        if (s == "+") st.emplace_back(1, 0);
        else if (s == "-") st.emplace_back(2, 0);
        else if (s == "*") st.emplace_back(3, 0);
        else st.emplace_back(0, atoi(s.c_str()));

        while (st.size() > 2u) {
            int n = st.size();
            if (!isop(st[n - 3])) break;
            if (isop(st[n - 2])) break;
            if (isop(st[n - 1])) break;
            auto c = st.back(); st.pop_back();
            auto b = st.back(); st.pop_back();
            auto a = st.back(); st.pop_back();

            st.push_back(meow(a, b, c));
        }
    }

    assert(st.size() == 1u);
    cout << st[0].second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) solve();
}
