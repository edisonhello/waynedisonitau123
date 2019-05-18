#include <bits/stdc++.h>
using namespace std;

vector<pair<string, int>> op;

string meow(int x) {
    stack<int> st;
    st.push(x);
    for (auto &p : op) {
        string s; int x; tie(s, x) = p;
        if (s == "NUM") {
            st.push(x);
        } else if (s == "POP") {
            if (st.empty()) {
                return "ERROR";
            } else st.pop();
        } else if (s == "INV") {
            if (st.empty()) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                st.push(-x);
            }
        } else if (s == "DUP") {
            if (st.empty()) {
                return "ERROR";
            } else {
                st.push(st.top());
            }
        } else if (s == "SWP") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                st.push(x); st.push(y);
            }
        } else if (s == "ADD") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                if (abs(x + y) > 1000000000) return "ERROR";
                st.push(x + y);
            }
        } else if (s == "SUB") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                if (abs(y - x) > 1000000000) return "ERROR";
                st.push(y - x);
            }
        } else if (s == "MUL") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                if (abs(1ll * x * y) > 1000000000) return "ERROR";
                st.push(x * y);
            }
        } else if (s == "DIV") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                if (x == 0) return "ERROR";
                st.push(abs(y) / abs(x) * (int(x < 0) + int(y < 0) == 1 ? -1 : 1));
            }
        } else if (s == "MOD") {
            if (st.size() < 2u) {
                return "ERROR";
            } else {
                int x = st.top(); st.pop();
                int y = st.top(); st.pop();
                if (x == 0) return "ERROR";
                st.push(abs(y) % abs(x) * (y < 0 ? -1 : 1));
            }
        } 
    }
    if (st.size() != 1u) return "ERROR";
    stringstream ss; ss << st.top();
    string r; ss >> r; return r;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string s; while (cin >> s) {
        if (s == "QUIT") break;
        op.clear();
        while (true) {
            if (s == "END") break;
            if (s == "NUM") {
                int x; cin >> x;
                op.emplace_back(s, x);
            } else {
                op.emplace_back(s, -1);
            }
            cin >> s;
            if (s == "END") break;
        }
        int n; cin >> n; while (n--) {
            int t; cin >> t;
            cout << meow(t) << '\n';
        }
        cout << '\n';
    }
}
