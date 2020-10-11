#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    while (cin >> S) {
        if (S == "0") break;
        int ptr = 0;
        vector<int> poly(1 << 8);
        poly[0] = 1;

        auto Mult = [&](const vector<int> &A, const vector<int> &B) {
            vector<int> res(1 << 8);
            for (int i = 0; i < (1 << 8); ++i) {
                for (int j = 0; j < (1 << 8); ++j) {
                    res[i ^ j] += A[i] * B[j];
                    res[i ^ j] %= 2;
                }
            }
            return res;
        };

        while (ptr < S.size()) {
            vector<int> coef(1 << 8);
            coef[0] = 1;
            coef[(1 << (S[ptr] - 'a'))] = 1;
            ptr++;
            if (ptr < S.size() && S[ptr] == '\'') {
                coef[0] = 0;
                ptr++;
            }
            ptr++;
            poly = Mult(poly, coef);
        }
        poly[0]++;
        poly[0] ^= 2;
        vector<int> term;
        for (int i = 0; i < (1 << 8); ++i) {
            if (poly[i] == 1) term.push_back(i);
        }
        sort(term.begin(), term.end(), [&](int X, int Y) {
            if (__builtin_popcount(X) != __builtin_popcount(Y))
                return __builtin_popcount(X) < __builtin_popcount(Y);
            string S = "", T = "";
            for (int i = 0; i < 8; ++i) {
                if (X >> i & 1) S += i + 'a';
                if (Y >> i & 1) T += i + 'a';
            }
            return S < T;
        });

        for (int i = 0; i < term.size(); ++i) {
            if (i > 0) cout << " + ";
            if (term[i] == 0) {
                cout << "1";
            } else {
                for (int j = 0; j < 8; ++j) {
                    if (term[i] >> j & 1) cout << (char)('a' + j);
                }
            }
        }
        cout << "\n";
    }
}
