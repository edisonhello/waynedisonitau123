#include <bits/stdc++.h>
using namespace std;


int main() {
    int t, n; cin >> t >> n; 
    if (t == 1) { // Durilkin, pick digit
        int r, c; 
        int cnt = 0;
        while (true) {
            cout << 5 << endl; ++cnt;
            cin >> r >> c;
            if (c == 1) {
                while (cnt < 2 * n) {
                    cout << 9 << endl; ++cnt;
                }
                break;
            }
        }
    } else { // I put digit
        bool first = true;
        int op = 0, id = 2;
        while (true) {
            int d; cin >> d;
            if (first) {
                if (d == 4) {
                    cout << 1 << " " << 1 << endl;
                } else if (d == 5) {
                    cout << 2 << " " << 1 << endl;
                } else assert(0);
                first = false;
            } else {
                if (id > n && op == 1) break;
                if (id > n) id = 1, op = 1;
                if (d == 0) {
                    cout << (op ? 2 : 1) << " " << id << endl;
                    ++id;
                    if (id > n && op == 1) break;
                    if (id > n) id = 1, op = 1;
                } else if (d == 9) {
                    cout << (op ? 1 : 2) << " " << id << endl;
                    ++id;
                    if (id > n && op == 1) break;
                    if (id > n) id = 1, op = 1;
                }
            }
        }
    }
}
