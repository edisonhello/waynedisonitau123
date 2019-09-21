int z[maxn];
// z[i] = LCP of suffix i and suffix 0
void z_function(const string& s) {
    memset(z, 0, sizeof(z));
    z[0] = (int)s.length();
    int l = 0, r = 0;
    for (int i = 1; i < s.length(); ++i) {
        z[i] = max(0, min(z[i - l], r - i + 1));
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]]) {
            l = i; r = i + z[i];
            ++z[i];
        }
    }
}
