#include <bits/stdc++.h>
using namespace std;
#define int long long

int play(priority_queue<int, vector<int>, less<int>> p1, priority_queue<int, vector<int>, less<int>> p2) {
    while (p1.size() && p2.size()) {
        if (p1.top() < p2.top()) {
            if (p1.size() > 1u) {
                int a = p1.top(); p1.pop();
                a += p1.top(); p1.pop();
                if (a < p2.top()) return 2;
                p1.push(a);
            } else return 2;
        } else {
            return 2;
        }

        if (p2.top() < p1.top()) {
            if (p2.size() > 1u) {
                int a = p2.top(); p2.pop();
                a += p2.top(); p2.pop();
                if (a < p1.top()) return 1;
                p2.push(a);
            } else return 1;
        } else {
            return 1;
        }
    }
    if (p1.empty()) return 2;
    if (p2.empty()) return 1;
    while (true); 
    return 0;
}


int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, ts = 0; while (cin >> n >> m) {
        cout << "Case " << (++ts) << ": ";
        priority_queue<int, vector<int>, less<int>> p1, p2;
        for (int i = 0; i < n; ++i) {
            int t; cin >> t;
            p1.push(t);
        }
        for (int i = 0; i < m; ++i) {
            int t; cin >> t;
            p2.push(t);
        }

        if (p1.top() > p2.top()) {
            int tmp = p2.top();
            p2.pop();
            int res1 = play(p2, p1);
            p2.push(tmp);
            if (p1.size() >= 2u) {
                int tmp1 = p1.top(); p1.pop();
                int tmp2 = p1.top(); p1.pop();
                p1.push(tmp1 + tmp2);
                int res2 = play(p2, p1);

                if (res1 == 2 || res2 == 2) cout << "Takeover Incorporated\n";
                else cout << "Buyout Limited\n";
            } else {
                if (res1 == 2) cout << "Takeover Incorporated\n";
                else cout << "Buyout Limited\n";
            }
        } else {
            int res = play(p1, p2);

            if (res == 1) cout << "Takeover Incorporated\n";
            else cout << "Buyout Limited\n";
        }
    }
}

