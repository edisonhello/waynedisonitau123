vector<int> kmp(const string &s) {
    vector<int> f(s.size(), 0);
    // f[i] = length of the longest prefix (excluding s[0:i]) such that it coincides with the suffix of s[0:i] of the same length
    // i + 1 - f[i] is the length of the smallest recurring period of s[0:i]
    int k = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        while (k > 0 && s[i] != s[k]) k = f[k - 1];
        if (s[i] == s[k]) ++k;
        f[i] = k;
    }
    return f;
}
vector<int> search(const string &s, const string &t) {
    // return 0-indexed occurrence of t in s
    vector<int> f = kmp(t), res;
    for (int i = 0, k = 0; i < (int)s.size(); ++i) {
        while (k > 0 && (k == (int)t.size() || s[i] != t[k])) k = f[k - 1];
        if (s[i] == t[k]) ++k;
        if (k == (int)t.size()) res.push_back(i - t.size() + 1);
    }
    return res;
}
