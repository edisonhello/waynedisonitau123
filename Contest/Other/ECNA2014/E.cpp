#include <bits/stdc++.h>
using namespace std;

int Match(vector<vector<int>> W) {
    int N = W.size();
    vector<int> fl(N, -1);
    vector<int> fr(N, -1);
    vector<int> hr(N, 0);
    vector<int> hl(N);
    for (int i = 0; i < N; ++i) {
        hl[i] = *max_element(W[i].begin(), W[i].end());
    }

    constexpr int kInf = 1'000'000'000;

    auto Bfs = [&](int s) {
        vector<int> slk(N, kInf);
        vector<bool> vl(N, false), vr(N, false);
        vector<int> pre(N);
        queue<int> que;
        que.push(s);
        vr[s] = true;

        auto Check = [&](int x) -> bool {
            if (vl[x] = true, fl[x] != -1) {
                que.push(fl[x]);
                return vr[fl[x]] = true;
            }
            while (x != -1) {
                swap(x, fr[fl[x] = pre[x]]);
            }
            return false;
        };

        while (true) {
            int d;
            while (!que.empty()) {
                int y = que.front();
                que.pop();
                for (int x = 0; x < N; ++x) {
                    if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - W[x][y])) {
                        if (pre[x] = y, d) slk[x] = d;
                        else if (!Check(x)) return;
                    }
                }
            }
            d = kInf;
            for (int x = 0; x < N; ++x) {
                if (!vl[x] && d > slk[x]) d = slk[x];
            }
            for (int x = 0; x < N; ++x) {
                if (vl[x]) hl[x] += d;
                else slk[x] -= d;
                if (vr[x]) hr[x] -= d;
            }
            for (int x = 0; x < N; ++x) {
                if (!vl[x] && !slk[x] && !Check(x)) return;
            }
        }
    };

    for (int i = 0; i < N; ++i) Bfs(i);
    int res = 0;
    for (int i = 0; i < N; ++i) res += W[i][fl[i]];
    return res;
}

int Solve() {
    int N;
    cin >> N;
    vector<vector<int>> W(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> W[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            W[i][j] = W[j][i];
        }
        W[i][i] = 1'000'000'000;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            W[i][j] = -W[i][j];
        }
    }
    return -Match(W);
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        cout << "Case " << i + 1 << ": " << Solve() << "\n";
    }
}

