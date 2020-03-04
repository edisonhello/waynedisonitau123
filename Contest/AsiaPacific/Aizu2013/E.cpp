#include <bits/stdc++.h>
using namespace std;

#define State array<array<int, 3>, 3>

State tran(int x) {
    State s;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
        s[i][j] = x % 9;
        x /= 9;
    }
    return s;
}
int tran(State s) {
    int x = 0, p = 1;
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
        x += p * s[i][j];
        p *= 9;
    }
    return x;
}

int go(int s, int t, int ch, int cv) {
    unordered_set<int> VIS;
    unordered_map<int, int> vis;
    vis[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    while (pq.size()) {
        int now = pq.top().second; 
        int co = pq.top().first;
        pq.pop();
        if (now == t) return co;
        if (VIS.count(now)) continue;
        VIS.insert(now);
        State snow = tran(now);
        // cout << "on state: x = " << now << endl;
        // for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cout << snow[i][j] << " \n"[j == 2];
        int x = -1, y = -1;
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (snow[i][j] == 0) x = i, y = j;
        auto insert = [&] (State s, int nc) {
            int x = tran(s);
            auto it = vis.find(x);
            // cout << "insert: x = " << x << endl;
            // for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cout << snow[i][j] << " \n"[j == 2];
            if (it == vis.end() || it->second > nc) {
                // cout << "emplace" << endl;
                vis[x] = nc;
                pq.emplace(nc, x);
            }
        };
        int i = x, j = y;
        if (i == 2) {
            swap(snow[0][j], snow[i][j]);
            insert(snow, co + cv);
            swap(snow[0][j], snow[i][j]);
        } else {
            swap(snow[i + 1][j], snow[i][j]);
            insert(snow, co + cv);
            swap(snow[i + 1][j], snow[i][j]);
        }
        if (i == 0) {
            swap(snow[i][j], snow[2][j]);
            insert(snow, co + cv);
            swap(snow[i][j], snow[2][j]);
        } else {
            swap(snow[i - 1][j], snow[i][j]);
            insert(snow, co + cv);
            swap(snow[i - 1][j], snow[i][j]);
        }
        if (j == 2) {
            swap(snow[i == 2 ? 0 : i + 1][0], snow[i][j]);
            insert(snow, co + ch);
            swap(snow[i == 2 ? 0 : i + 1][0], snow[i][j]);
        } else {
            swap(snow[i][j], snow[i][j + 1]);
            insert(snow, co + ch);
            swap(snow[i][j], snow[i][j + 1]);
        }
        if (j == 0) {
            swap(snow[i == 0 ? 2 : i - 1][2], snow[i][j]);
            insert(snow, co + ch);
            swap(snow[i == 0 ? 2 : i - 1][2], snow[i][j]);
        } else {
            swap(snow[i][j], snow[i][j - 1]);
            insert(snow, co + ch);
            swap(snow[i][j], snow[i][j - 1]);
        }
    }
    return -1;
}

int main() {
    int ch, cv; while (cin >> ch >> cv) {
        if (ch == 0 && cv == 0) break;
        State st;
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) 
            cin >> st[i][j];
        int s = tran(st);
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) 
            cin >> st[i][j];
        int t = tran(st);
        cout << go(s, t, ch, cv) << '\n';
    }
}
