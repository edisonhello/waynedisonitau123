#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("abbreviation.in", "r", stdin);
    freopen("abbreviation.out", "w", stdout);
    string S;

    auto Check = [&](const string &T) {
        if (T.size() == 1) return false;
        if (!(T[0] >= 'A' && T[0] <= 'Z')) return false;
        for (int i = 1; i < T.size(); ++i) {
            if (!(T[i] >= 'a' && T[i] <= 'z')) return false;
        }
        return true;
    };

    while (getline(cin, S)) {
        int ptr = 0;
        vector<string> abbr;
        vector<string> strs;
        while (ptr < S.size()) {
            if (isalpha(S[ptr])) {
                string T = "";
                while (ptr < S.size() && isalpha(S[ptr])) {
                    T += S[ptr];
                    ptr++;
                }
                strs.push_back(T);
            } else {
                strs.push_back(string(1, S[ptr++]));
            }
        }
        for (int i = 0, j = 0; i < strs.size(); i = j) {
            j = i;
            if (Check(strs[i])) {
                bool F = true;
                vector<string> V;
                while (j < strs.size()) {
                    if (!Check(strs[j])) break;
                    V.push_back(strs[j]);
                    j++;
                    if (j == strs.size() || strs[j] != " ") break;
                    j++;
                }
                if (j > 0 && strs[j - 1] == " ") j--;
                if (V.size() > 1) {
                    for (auto &T : V) cout << T[0];
                    cout << " (";
                    for (int k = 0; k < V.size(); ++k) {
                        cout << V[k];
                        if (k + 1 < V.size()) cout << " ";
                    }
                    cout << ")";
                } else {
                    cout << V[0];
                }
            } else {
                cout << strs[i];
                j = i + 1;
            }
        }
        cout << "\n";
    }
}

