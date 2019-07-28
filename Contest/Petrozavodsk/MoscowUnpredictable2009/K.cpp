#include <bits/stdc++.h>
using namespace std;

uint64_t mhash(string s) {
    uint64_t res = 0, pp = 1;
    for (char c : s) res = (res + pp * c) % 1000000009, pp = pp * 131 % 1000000007;
    for (char c : s) res = (res << 10) ^ (res >> 12) ^ (c * pp);
    // cerr << "hash " << s << " get " << res << endl;
    return res;
}

unordered_map<uint64_t, int> word_type; // -1 for verb, 0 for single noun, 1 for plural noun

int get_number(string s) {
    static map<string, int> mp = {
        {"ma", 0},
        {"si", 0},
        {"saw", 0},
        {"llahs", 0},
        {"era", 1},
        {"erew", 1},
        {"lliw", 2}
    };
    if (mp.count(s)) return mp[s];
    else return -1;
}

int is_single_noun(string s) {
    static map<string, int> mp = {
        {"i", 0},
        {"eh", 0},
        {"ehs", 0},
        {"ti", 0},
        {"yeht", 1},
        {"ew", 1},
        {"uoy", 1}
    };
    if (mp.count(s)) return mp[s] == 0;
    uint64_t h = mhash(s);
    auto it = word_type.find(h);
    if (it == word_type.end()) return 0;
    else return it->second == 0;
}
int is_plural_noun(string s) {
    static map<string, int> mp = {
        {"i", 0},
        {"eh", 0},
        {"ehs", 0},
        {"ti", 0},
        {"yeht", 1},
        {"ew", 1},
        {"uoy", 1}
    };
    if (mp.count(s)) return mp[s] == 1;
    uint64_t h = mhash(s);
    auto it = word_type.find(h);
    if (it == word_type.end()) return 0;
    else return it->second == 1;
}
int is_verb(string s) {
    uint64_t h = mhash(s);
    auto it = word_type.find(h);
    if (it == word_type.end()) return 0;
    else return it->second == -1;
}

string to_plural(string s) {
    auto start_by = [&] (string t) {
        if (t.size() > s.size()) return false;
        return s.substr(0, t.size()) == t;
    };
    if (start_by("s") || start_by("ss") || start_by("hs") || start_by("hc") || start_by("hct") || start_by("x") || start_by("o")) return "se" + s;
    if (start_by("y") && s.size() > 1u && s[1] != 'a' && s[1] != 'e' && s[1] != 'i' && s[1] != 'o' && s[1] != 'y') {
        s[0] = 'i';
        return "se" + s;
    }
    if (start_by("f")) {
        s[0] = 'v';
        return "se" + s;
    }
    if (start_by("ef")) {
        s[1] = 'v';
        return "s" + s;
    }
    return "s" + s;
}

void affirmative(vector<string> &v) {
    // cerr << "affirmative" << endl;
    int number = get_number(v[1]);
    if (number == -1) return cout << "No" << '\n', void();
    int ok = 0;
    // cerr << "number = " << number << endl;
    if (number == 0 || number == 2) {
        if (is_single_noun(v[0]) && is_verb(v[2])) ++ok;
    } 
    if (number == 1 || number == 2) {
        if (is_plural_noun(v[0]) && is_verb(v[2])) ++ok;
    }
    if (ok) cout << "Yes" << '\n';
    else cout << "No" << '\n';
}

void negative(vector<string> &v) {
    // cerr << "negative" << endl;
    int number = get_number(v[1]);
    if (number == -1 || v[2] != "oy") return cout << "No" << '\n', void();
    int ok = 0;
    if (number == 0 || number == 2) {
        if (is_single_noun(v[0]) && is_verb(v[3])) ++ok;
    } 
    if (number == 1 || number == 2) {
        if (is_plural_noun(v[0]) && is_verb(v[3])) ++ok;
    }
    if (ok) cout << "Yes" << '\n';
    else cout << "No" << '\n';
}

void interrogative(vector<string> &v) {
    // cerr << "interrogative" << endl;
    if (v.size() != 3u && v.size() != 4u) return cout << "No" << '\n', void();
    int number = get_number(v[0]);
    if (number == -1) return cout << "No" << '\n', void();
    int ok = 0;
    if (v.size() == 3u) {
        if (number == 0 || number == 2) {
            if (is_single_noun(v[1]) && is_verb(v[2])) ++ok;
        }
        if (number == 1 || number == 2) {
            if (is_plural_noun(v[1]) && is_verb(v[2])) ++ok;
        }
    } else {
        if (number == 0 || number == 2) {
            if (is_single_noun(v[1]) && is_verb(v[3]) && v[2] == "oy") ++ok;
        } 
        if (number == 1 || number == 2) {
            if (is_plural_noun(v[1]) && is_verb(v[3]) && v[2] == "oy") ++ok;
        }
    }
    if (ok) cout << "Yes" << '\n';
    else cout << "No" << '\n';
}

void solve(string s) {
    // cerr << "solve: " << s << endl;
    vector<string> v;
    string cur;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (isalpha(s[i])) cur += s[i];
        else if (cur != "") v.push_back(cur), cur = "";
    }
    char end = s.back();
    // cerr << "end = " << end << endl;
    // cerr << "v = ["; for (auto s : v) cerr << s << ", "; cerr << "]" << endl;
    if (end == '?') interrogative(v);
    else if (v.size() == 3u) affirmative(v);
    else if (v.size() == 4u) negative(v);
    else cout << "No" << '\n';
}

int main() {
    freopen("language.in", "r", stdin);
    freopen("language.out", "w", stdout);
    int n, m; cin >> n >> m;
    while (n--) {
        string s; cin >> s;
        word_type[mhash(s)] = 0;
        word_type[mhash(to_plural(s))] = 1;
    }
    while (m--) {
        string s;  cin >> s;
        word_type[mhash(s)] = -1;
    }
    string cur;
    char c;
    while ((c = getchar()) != -1) {
        if (c == '.' || c == '!' || c == '?') {
            cur += c;
            solve(cur);
            cur = "";
        } else cur += c;
    }
}
