#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

const int size=3,len=3,lim=27;
int a[1444];
bitset<lim> u;

cc_hash_table<long long,int> mp;
// map<int, int> mp;

int poow(int m,int n){
    int r=1;
    while(n--){
        r*=m;
        if(r>2e5)return 2e5;
    }
    return r;
}


const int mod1 = 1e9 + 123, mod2 = 1e9 + 87;
int ch[10];
int hs1[1000000], hs2[1000000], pw1[1000000], pw2[1000000];

long long meow(int a, int b) {
    return a * 2000000000ll + b;
}

long long query(int l, int r) {
    int a, b;
    if (l == 0) a = hs1[r], b = hs2[r];
    else a = (hs1[r] - pw1[r - l + 1] * 1ll * hs1[l - 1] % mod1 + mod1) % mod1, b = (hs2[r] - pw2[r - l + 1] * 1ll * hs2[l - 1] % mod2 + mod2) % mod2;
    return meow(a, b);
}

int main(){
    pw1[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i < 1000000; ++i) pw1[i] = pw1[i - 1] * 131ll % mod1;
    for (int i = 1; i < 1000000; ++i) pw2[i] = pw2[i - 1] * 7902131ll % mod2;
    int n,m,k; cin>>n>>m>>k;
    for(int i=0;i<m;++i)cin>>ch[i];
    if(n==1){
        for(int i=0;i<k;++i)cout<<ch[i];
        cout<<endl;
        exit(0);
    }
    string tmp;
    for(int i=1;i<n;++i)tmp+=char('0'+m-1);
    for(int i=1;i<n;++i)tmp+='0';
    if(1) {
        // cout<<"tmp: "<<tmp<<endl;
        hs1[0] = tmp[0];
        hs2[0] = tmp[0];
        for (int i = 1; i < (int)tmp.size(); ++i) hs1[i] = (hs1[i - 1] * 131ll + tmp[i]) % mod1;
        for (int i = 1; i < (int)tmp.size(); ++i) hs2[i] = (hs2[i - 1] * 7902131ll + tmp[i]) % mod2;
        for (int i = 0; i + n - 1 < (int)tmp.size(); ++i) {
            long long ss = query(i, i + n - 2);
            mp[ss]=0;
        }
    }
    int len=min(k+n-1,poow(m,n));
    string ans;
    for(int i=1;i<n;++i)ans+='0';
    if (n > 1) {
        hs1[0] = ans[0];
        hs2[0] = ans[0];
        for (int i = 1; i < (int)ans.size(); ++i) hs1[i] = (hs1[i - 1] * 131ll + ans[i]) % mod1;
        for (int i = 1; i < (int)ans.size(); ++i) hs2[i] = (hs2[i - 1] * 7902131ll + ans[i]) % mod2;
    }
    while(int(ans.size())<len){
        long long ss = query(ans.size() - (n - 1), ans.size() - 1);
        if(mp.find(ss)==mp.end()){
            mp[ss] = 0;
            ans += '0';
            hs1[ans.size() - 1] = (hs1[ans.size() - 2] * 131ll + ans.back()) % mod1;
            hs2[ans.size() - 1] = (hs2[ans.size() - 2] * 7902131ll + ans.back()) % mod2;
        } else{
            int x=++mp[ss];
            if(x>=m){ans.pop_back();continue;}
            ans+=char(x+'0');
            hs1[ans.size() - 1] = (hs1[ans.size() - 2] * 131ll + ans.back()) % mod1;
            hs2[ans.size() - 1] = (hs2[ans.size() - 2] * 7902131ll + ans.back()) % mod2;
        }
        /* if(ans.size()==len){
            string tmp = ans + ans.substr(0, n - 1);
            for (int i = len; i < tmp.size(); ++i) {
                hs1[i] = (hs1[i - 1] * 131ll + tmp[i]) % mod1;
                hs2[i] = (hs2[i - 1] * 7902131ll + tmp[i]) % mod2;
            }
            set<long long> sss;
            bool ok = true;
            for (int i = 0; i + n <= tmp.size(); ++i) {
                long long ac = query(i, i + n - 1);
                if (sss.count(ac)) {
                    ok = false;
                    break;
                }
                sss.insert(ac);
            }
            if (!ok) {
                ans.pop_back();
            }
        } */
    }
    ans = ans+ans.substr(0,n-1);
    ans = ans.substr(0,k+n-1);
    for(char c:ans){
        cout<<ch[c-'0'];
    }
    cout<<endl;
}
