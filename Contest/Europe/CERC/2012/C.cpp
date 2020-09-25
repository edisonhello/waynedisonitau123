#include <bits/stdc++.h>
using namespace std;

vector<string> ss = {
    "H", "He",
    "Li", "Be", "B", "C", "N", "O",   "F",   "Ne",
        "Na",  "Mg",                                          "Al",  "Si",  "P",   "S",   "Cl",  "Ar",
        "K",  "Ca",  "Sc",  "Ti",  "V",  "Cr",  "Mn",  "Fe",  "Co",  "Ni",  "Cu",  "Zn",  "Ga",  "Ge",  "As",  "Se",  "Br",  "Kr",
        "Rb",  "Sr",  "Y",   "Zr",  "Nb",  "Mo",  "Tc",  "Ru",  "Rh",  "Pd",  "Ag",  "Cd",  "In",  "Sn",  "Sb",  "Te",  "I",  "Xe",
        "Cs",  "Ba",  "*",   "Hf",  "Ta",  "W",  "Re",  "Os",  "Ir",  "Pt",  "Au",  "Hg",  "Tl",  "Pb",  "Bi",  "Po",  "At",  "Rn",
        "Fr",  "Ra",  "**",  "Rf",  "Db",  "Sg",  "Bh",  "Hs",  "Mt",  "Ds",  "Rg",  "Cn",  "  ",  "Fl",  "  ",  "Lv",
    "La",  "Ce",  "Pr",  "Nd",  "Pm",  "Sm",  "Eu",  "Gd",  "Tb",  "Dy",  "Ho",  "Er",  "Tm",  "Yb",  "Lu",
    "Ac",  "Th",  "Pa",  "U",  "Np",  "Pu",  "Am",  "Cm",  "Bk",  "Cf",  "Es",  "Fm",  "Md",  "No",  "Lr"
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    set<string> st;
    for (string s : ss) {
        for (char &c : s) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        }
        st.insert(s);
    }
    int t; cin >> t; while (t--) {
        string s; cin >> s;
        int n = s.size();
        s = " " + s;
        vector<int> dp(s.size(), 0);
        dp[0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = max(1, i - 2); j <= i; ++j) {
                string sss = s.substr(j, i - j + 1);
                if (st.count(sss)) dp[i] |= dp[j - 1];
            }
            // cerr << "dp " << i << " = " << dp[i] << endl;
        }
        cout << (dp.back() ? "YES" : "NO") << '\n';

    }
}

