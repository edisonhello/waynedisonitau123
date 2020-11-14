#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream &O, __int128 V) {
    string S = "";
    while (V > 0) {
        S += (char)(V % 10 + '0');
        V /= 10;
    }
    reverse(S.begin(), S.end());
    return O << S;
}

__int128 Cache[100][100][2][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;

    memset(Cache, -1, sizeof(Cache));

    auto Count = [&](int L, int C, bool Z, bool Ok = false) -> __int128 {
        if (Cache[L][C][Z][Ok] != -1) return Cache[L][C][Z][Ok];
        if (L > C && !Ok) return 0;
        if (Ok) {
            __int128 res = 0;
            for (int l = 1; l <= L; ++l) {
                __int128 v = C - 1;
                for (int i = 0; i < l - 1; ++i) v *= C - i - 1;
                res += v;
            }
            return Cache[L][C][Z][Ok] = res;
        }
        if (L == 0) return 1;
        __int128 res = 1;
        for (int i = 0; i < L; ++i) res *= C - i;
        return Cache[L][C][Z][Ok] = res;
    };

    auto CountDec = [&](string S) -> __int128 {
        vector<bool> used(10);
        bool Z = false;
        __int128 res = 0;
        // cerr << "CountDec S = " << S << endl;
        for (int i = 0; i < S.size(); ++i) {
            int D = S[i] - '0';
            for (int j = 0; j < D; ++j) {
                if (used[j]) continue;
                bool W = (Z || (j == 0));
                if (i == 0 && j == 0) res += Count(S.size() - 1 - i, 10 - i, W, true);
                else res += Count(S.size() - 1 - i, 10 - (i + 1), W);
            }
            if (used[D]) break;
            used[D] = true;
            Z |= (D == 0);
        }
        // cerr << "res = " << res << endl;
        return res;
    };

    auto CountHex = [&](string S) -> __int128 {
        vector<bool> used(16);
        bool Z = false;
        __int128 res = 0;
        for (int i = 0; i < S.size(); ++i) {
            int D = (isdigit(S[i]) ? S[i] - '0' : S[i] - 'a' + 10);
            for (int j = 0; j < D; ++j) {
                if (used[j]) continue;
                bool W = (Z || (j == 0));
                if (i == 0 && j == 0) res += Count(S.size() - 1 - i, 16 - i, W, true);
                else res += Count(S.size() - 1 - i, 16 - (i + 1), W);
            }
            if (used[D]) break;
            used[D] = true;
            Z |= (D == 0);
        }
        return res;
    };

    auto AddDec = [&](string S) {
        S.back()++;
        int ptr = S.size() - 1;
        bool PrePend = false;
        while (ptr >= 0 && S[ptr] > '9') {
            S[ptr] = '0';
            if (ptr == 0) PrePend = true;
            else S[ptr - 1]++;
            ptr--;
        }
        if (PrePend) S = "1" + S;
        return S;
    };



    auto AddHex = [&](string S) {
        auto Add = [&](char &c) {
            if (c == '9') c = 'a';
            else c++;
        };
        Add(S.back());
        int ptr = S.size() - 1;
        bool PrePend = false;
        while (ptr >= 0 && S[ptr] == 'g') {
            S[ptr] = '0';
            if (ptr == 0) PrePend = true;
            else Add(S[ptr - 1]);
            ptr--;
        }
        if (PrePend) S = "1" + S;
        return S;
    };

    auto ToDec = [&](__int128 V) -> string {
        if (V == 0) return "0";
        string S = "";
        while (V > 0) {
            S += (char)(V % 10 + '0');
            V /= 10;
        }
        reverse(S.begin(), S.end());
        return S;
    };

    auto ToHex = [&](__int128 V) -> string {
        if (V == 0) return "0";
        string S = "";
        while (V > 0) {
            if (V % 16 >= 10) S += (V % 16 - 10 + 'a');
            else S += (V % 16 + '0');
            V /= 16;
        }
        reverse(S.begin(), S.end());
        return S;
    };

    auto Trim = [&](string S) -> string {
        if (S == "0") return "0";
        int p = 0;
        while (S[p] == '0') p++;
        return S.substr(p);
    };

    while (T--) {
        string S;
        cin >> S;
        if (S[0] == 'd') {
            int t;
            cin >> t;
            if (t == 0) {
                string A, B;
                A = Trim(A);
                B = Trim(B);
                cin >> A >> B;
                __int128 res = CountDec(AddDec(B)) - CountDec(A);
                if (A == "0") res++;
                cout << static_cast<uint64_t>(res) << "\n";
            } else {
                uint64_t X = 0;
                cin >> X;
                if (X == 1) {
                    cout << "0\n";
                    continue;
                }
                __int128 ans = 0;
                for (int bit = 63; bit >= 0; --bit) {
                    if (CountDec(ToDec(ans + (1ULL << bit))) + 1 < X) ans += (1ULL << bit);
                }
                if (CountDec(ToDec(ans)) + 1 != X - 1) cout << "-\n";
                else cout << static_cast<uint64_t>(ans) << "\n";
            }
        } else {
            int t;
            cin >> t;
            if (t == 0) {
                string A, B;
                cin >> A >> B;
                A = Trim(A);
                B = Trim(B);
                __int128 res = CountHex(AddHex(B)) - CountHex(A);
                if (A == "0") res++;
                cout << ToHex(static_cast<uint64_t>(res)) << "\n";
            } else {
                string S;
                cin >> S;
                __int128 X = 0;
                for (int i = 0; i < S.size(); ++i) {
                    int D = (isdigit(S[i]) ? S[i] - '0' : S[i] - 'a' + 10);
                    X = X * 16 + D;
                }
                if (X == 1) {
                    cout << "0\n";
                    continue;
                }
                __int128 ans = 0;
                for (int bit = 63; bit >= 0; --bit) {
                    if (CountHex(ToHex(ans + (1ULL << bit))) + 1 < X) ans += (1ULL << bit);
                }
                if (CountHex(ToHex(ans)) + 1 != X - 1) cout << "-\n";
                else cout << ToHex(static_cast<uint64_t>(ans)) << "\n";
            }
        }
    }
}
