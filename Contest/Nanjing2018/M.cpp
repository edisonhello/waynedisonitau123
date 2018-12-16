#pragma GCC optimize("O3")
#pragma GCC target("avx")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 5;
int sa[maxn], tmp[2][maxn], c[maxn], hi[maxn], rev[maxn];
int ip[maxn];
bool del[maxn];

namespace DC3{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#define SG(v,i) ((i)>=int(v.size())?0:v[i])
    inline bool smaller(int a, int b, vector<int> &r){
        if(SG(r,a+0) != SG(r,b+0)) return SG(r,a+0)<SG(r,b+0);
        if(SG(r,a+1) != SG(r,b+1)) return SG(r,a+1)<SG(r,b+1);
        return SG(r,a+2)<SG(r,b+2);
    }
    
    int cc[2000005];
    inline vector<int> sort(vector<int> &r, int o, vector<int> &ix, int m){
        vector<int> rt(ix.size());
        for(int z=0;z<o;++z) r.push_back(0);
        for(int i=0;i<=m;++i) cc[i] = 0;
        for(int i=0;i<ix.size();++i) ++cc[r[ix[i]+o]];
        for(int i=0;i<=m;++i) cc[i+1] += cc[i];
        for(int i=ix.size()-1;i>=0;--i) rt[--cc[r[ix[i]+o]]] = ix[i];
        for(int z=0;z<o;++z) r.pop_back();
        return rt;
    }

    vector<int> dc3(vector<int> &v, int n, int m){
        int c1 = (n+1)/3;
        vector<int> i12;
        for(int i=0;i<n;++i){
            if(i%3==0)continue;
            i12.push_back(i);
        }
        i12 = sort(v, 2, i12, m);
        i12 = sort(v, 1, i12, m);
        i12 = sort(v, 0, i12, m);

        int nr = 1;
        vector<int> r12(i12.size());
#define GRI(x) ((x)/3 + ((x)%3==2?c1:0))
        r12[GRI(i12[0])] = 1;
        for(int i=1;i<i12.size();++i){
            if(smaller(i12[i-1], i12[i], v)) r12[GRI(i12[i])] = ++nr;
            else r12[GRI(i12[i])] = nr;
        }

#define GEI(x) ((x)<c1?(x)*3+1:(x-c1)*3+2)
        if(nr != i12.size()){
            i12 = dc3(r12, i12.size(), nr);
            
            for(int i=0;i<i12.size();++i) r12[i12[i]] = i+1;
            for(int &i: i12) i = GEI(i);
        }

        vector<int> i0;
        if(n%3==1) i0.push_back(n-1);
        for(int i=0;i<i12.size();++i) if(i12[i]%3 == 1) i0.push_back(i12[i]-1);
        i0 = sort(v, 0, i0, m);

        vector<int> ret(v.size());
        int ptr12=0, ptr0=0, ptr=0;
        while(ptr12<i12.size() && ptr0<i0.size()){
            if(i12[ptr12]%3 == 1){
                if([&](int i, int j) -> bool{
                    if(SG(v,i) != SG(v,j)) return SG(v,i)<SG(v,j);
                    return SG(r12,GRI(i+1))<SG(r12,GRI(j+1));
                }(i12[ptr12], i0[ptr0]))ret[ptr++] = i12[ptr12++];
                else ret[ptr++] = i0[ptr0++];
            }
            else{
                if([&](int i, int j) -> bool{
                    if(SG(v,i+0) != SG(v,j+0)) return SG(v,i+0)<SG(v,j+0);
                    if(SG(v,i+1) != SG(v,j+1)) return SG(v,i+1)<SG(v,j+1);
                    return SG(r12,GRI(i+2))<SG(r12,GRI(j+2));
                }(i12[ptr12], i0[ptr0]))ret[ptr++] = i12[ptr12++];
                else ret[ptr++] = i0[ptr0++];
            }
        }
        while(ptr12<i12.size()) ret[ptr++] = i12[ptr12++];
        while(ptr0<i0.size()) ret[ptr++] = i0[ptr0++];

        return ret;
    }
    vector<int> build(string str){
        vector<int> val(str.size()+1, 0);
        for(int i=0;i<str.size();++i) val[i] = str[i];
        return dc3(val, val.size(), 256);
    }
#pragma GCC diagnostic pop
}

void build(const string &s) {
    vector<int> _sa = DC3::build(s);
    for (int i = 0; i < (int)s.size(); ++i) sa[i] = _sa[i + 1];
    for (int i = 0; i < (int)s.size(); ++i) rev[sa[i]] = i;
    int ind = 0;
    hi[0] = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (!rev[i]) {
            ind = 0;
            continue;
        }
        while (i + ind < (int)s.size() && s[i + ind] == s[sa[rev[i] - 1] + ind]) ++ind;
        hi[rev[i]] = ind ? ind-- : 0;
    }
}

int z[maxn];

void manacher(const string &s) {
    string t = ".";
    for (int i = 0; i < (int)s.size(); ++i) t += s[i], t += '.';
    int l = 0, r = 0;
    for (int i = 1; i < (int)t.size(); ++i) {
        z[i] = (r > i ? min(z[2 * l - i], r - i) : 1);
        while (i - z[i] >= 0 && i + z[i] < (int)t.size() && t[i - z[i]] == t[i + z[i]]) ++z[i];
        if (i + z[i] > r) r = i + z[i], l = i;
    }
}

int pal[maxn];
int fr[maxn], ba[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, t; cin >> s >> t;
    int n = (int)s.size(), m = (int)t.size();
    string p = s;
    reverse(p.begin(), p.end());
    manacher(p);
    // for (int i = 0; i < 2 * n - 1; ++i) cout << z[i] << ' '; cout << endl;
    for (int i = 1; i < 2 * n - 1; ++i) {
        int l = i / 2;
        int r = l + z[i] / 2;
        // cout << "i = " << i << "l = " << l << " r = " << r << endl;
        ++pal[l], --pal[r];
    }
    for (int i = 1; i < n; ++i) pal[i] += pal[i - 1];
    build(p + t);
    long long sum = 0;
    long long ans = 0;
    for (int i = 0; i < n - 1; ++i) sum += pal[i];
    // cout << "pal: "; for (int i = 0; i < n; ++i) cout << pal[i] << ' '; cout << endl;
    int l = 0, r = n + m - 1;
    // for (int i = 0; i < n + m; ++i) cout << sa[i] << ' '; cout << endl;
    // for (int i = 0; i < n + m; ++i) cout << hi[i] << ' '; cout << endl;
    fr[rev[n]] = 1e9;
    for (int i = rev[n] - 1; i >= 0; --i) fr[i] = min(fr[i + 1], hi[i + 1]);
    ba[rev[n]] = 1e9;
    for (int i = rev[n] + 1; i < n + m; ++i) ba[i] = min(ba[i - 1], hi[i]);
    int j = n - 1;
    for (int i = 0; i < m; ++i) {
        // cout << "sum before = " << sum << endl;
        while (l < rev[n] && fr[l] <= i) {
            if (del[sa[l]]) {
                ++l;
                continue;
            }
            // cout << "delete: " << sa[l] << endl;
            if (sa[l] < n && sa[l] > 0) sum -= pal[sa[l] - 1];
            del[sa[l]] = true;
            ++l;
        }
        while (r > rev[n] && ba[r] <= i) {
            if (del[sa[r]]) {
                --r;
                continue;
            }
            // cout << "delete: " << sa[r] << endl;
            if (sa[r] < n && sa[r] > 0) sum -= pal[sa[r] - 1];
            del[sa[r]] = true;
            --r;
        }
        while (j >= 0 && n - j <= i) {
            // cout << "delete: " << v.back() << endl;
            if (!del[j] && j > 0) sum -= pal[j - 1];
            del[j] = true;
            --j;
        }
        // cout << "l = " << l << " r = " << r << endl;
        // cout << "i = " << i << " sum = " << sum << endl;
        ans += sum;
    }
    cout << ans << endl;
}
