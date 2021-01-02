#include <bits/stdc++.h>
using namespace std;

int main() {
    int A, B;
    cin >> A >> B;
    vector<int> last;
    int N = A + B;
    vector<int> number((A + B) * 2);
    vector<int> weight((A + B) * 2);
    int p = 0;
    for (int i = 0; A > 0 || B > 0; ++i) {
        vector<int> seq;
        if (i == 0) {
            seq = {0};
        } else {
            for (int j : last) seq.push_back(j * 2);
            for (int j : last) seq.push_back(j * 2 + 1);
        }
        vector<int> nseq(seq.begin(), seq.end());
        if (B == 0) reverse(nseq.begin(), nseq.end());
        for (int u : nseq) {
            if (B > 0) {
                assert(p + u < number.size());
                number[p + u] = 2;
                B--;
            } else if (A > 0) {
                assert(p + u < number.size());
                number[p + u] = 1;
                A--;
            }
        }
        p += seq.size();
        last = seq;
    }

    vector<int> ID(N * 2);
    int C = 0;
    vector<int> node;

    auto Dfs = [&](auto dfs, int x) -> bool {
        weight[x] = number[x];
        node.push_back(x);
        ID[x] = C++;
        int Lw = 0, Rw = 0;
        if (x * 2 + 1 < number.size() && number[x * 2 + 1] > 0) {
            if (!dfs(dfs, x * 2 + 1)) return false;
            Lw = weight[x * 2 + 1];
        }
        if (x * 2 + 2 < number.size() && number[x * 2 + 2] > 0) {
            if (!dfs(dfs, x * 2 + 2)) return false;
            Rw = weight[x * 2 + 2];
        }
        if (abs(Lw - Rw) > 1) return false;
        weight[x] += Lw + Rw;
        return true;
    };

    if (!Dfs(Dfs, 0)) {
        cout << "-1\n";
        return 0;
    }

    for (int u : node) {
        cout << number[u];
        if (u * 2 + 1 < number.size() && number[u * 2 + 1] > 0) cout << " " << ID[u * 2 + 1] + 1;
        else cout << " " << 0;
        if (u * 2 + 2 < number.size() && number[u * 2 + 2] > 0) cout << " " << ID[u * 2 + 2] + 1;
        else cout << " " << 0;
        cout << "\n";
    }
}

