#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int N = s.size();
        vector<int> V;
        for (int i = N - 1; i >= 0; --i) V.push_back(s[i] - '0');
        V.push_back(0);
        for (int i = 0; i < N; ++i) V.push_back(s[i] - '0');
        V.push_back(0);
        for (int i = N - 1; i >= 0; --i) V.push_back(s[i] - '0');
        for (int bit = 0; bit < 20; ++bit) {
            if (N >> bit & 1) {
                vector<int> W(V.size());
                for (int i = 0; i < V.size(); ++i) {
                    if (V[i] == 0) continue;
                    if (i - (1 << bit) >= 0) W[i - (1 << bit)] ^= 1;
                    if (i + (1 << bit) < V.size()) W[i + (1 << bit)] ^= 1;
                }
                V = W;
            }
        }
        bool ok = true;
        for (int i = N + 1; i < N + N + 1; ++i) ok &= V[i] == 0;
        cout << (ok ? "DIES" : "LIVES") << "\n";
    }
}

