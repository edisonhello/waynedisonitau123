#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")

#include<bits/stdc++.h>
using namespace std;
// #define int long long

const int mod=1000000007;

inline vector<int> operator*(const vector<int> &a,const vector<int> &b){
    // cout<<"pol pro asz, bsz: "<<a.size()<<" and "<<b.size()<<endl;
    vector<int> rt(a.size()+b.size()-1);
    for(int i=0;i<int(a.size());++i){
        auto res=rt.begin()+i;
        auto it=b.begin(),aa=a.begin()+i;
        int sz=int(b.size());
        for(int j=0;j<sz;++j){
            *res+=1ll*(*aa)*(*it)%mod;
            if(*res>=mod)*res-=mod;
            ++res, ++it;
        }

        /* for(int j=0;j<int(b.size());++j){
            rt[i+j]+=1ll*a[i]*b[j]%mod;
            if(rt[i+j]>=mod)rt[i+j]-=mod;
        } */
    }
    for(int i=int(rt.size())-1;i>=16;--i)rt[i-15]+=rt[i],rt[i-15]-=(rt[i-15]>=mod?mod:0);
    // for(int i=0;i<min(16,int(rt.size()));++i)if(rt[i]>=mod)rt[i]-=mod;
    if(rt.size()>16)rt.resize(16);
    return rt;
}

struct node{
    node *l,*r;
    vector<int> v;
    node():l(0),r(0),v(1,1){ }
} *root;

#define mid ((l+r)>>1)
vector<int> st[400005],sample[17];

void modify(int l,int r,int x,int di, int o = 0){
    if(l==r){
        st[o] =sample[di];
        return;
    }
    if(x<=mid)modify(l,mid,x,di, o * 2 + 1);
    else modify(mid+1,r,x,di, o * 2 + 2);
    st[o] = st[o * 2 + 1] * st[o * 2 + 2];
}

vector<int> query(int l,int r,int ql,int qr, int o = 0){
    if(qr<l || r<ql)return vector<int>(1,1);
    if(ql<=l&&r<=qr)return st[o];
    return query(l,mid,ql,qr, o * 2 + 1)*query(mid+1,r,ql,qr, o * 2 + 2);
}

int pw1021[17];
int fill1021(const vector<int> &pol){
    int rt=0;
    for(int i=0;i<int(pol.size());++i){
        rt+=1ll*pol[i]*pw1021[i]%mod;
        if(rt>=mod)rt-=mod;
    }
    return rt;
}

/* inline int gtx() {
    const int N = 4096;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread_unlocked(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}

template <typename T>
inline bool rit(T &x) {
    char c = 0;
    bool flag = false;
    while (c = gtx(), (c < '0' && c != '-' || c > '9')) if (c == -1) return false;
    if (c == '-') flag = true, x = 0;
    else x = c - '0';
    while (c = gtx(), (c >= '0' && c <= '9')) x = x * 10 + c - '0';
    if (flag) x = -x;
    return true;
}

char Getchar(){
    char c; do{
        c=gtx();
    }while(!((c>='0' && c<='9')||(c>='A' && c<='F')));
    return c;
} */

int32_t main(){
    ios_base::sync_with_stdio(0) ;cin.tie(0);
    int n,q; cin>>n>>q;
    string s; cin>>s; s="z"+s;
    for (int i = 0; i < 400005; ++i) st[i] = vector<int>(1, 1);
    for(int i=0;i<16;++i)sample[i]=vector<int>(i+1,0),sample[i][0]=sample[i][i]=1;
    sample[0][0]=2;
    pw1021[0]=1;
    for(int i=1;i<17;++i)pw1021[i]=1021ll*pw1021[i-1]%mod;
    for(int i=1;i<=n;++i){
        int di=-1;
        if(s[i]>='0' && s[i]<='9')di=s[i]-'0';
        else di=s[i]-'A'+10;
        modify(1,n,i,di);
    }
    while(q--){
        int com; cin>>com;
        if(com==1){
            int x; char c; cin>>x>>c;
            int di=-1;
            s[x]=c;
            if(s[x]>='0' && s[x]<='9')di=s[x]-'0';
            else di=s[x]-'A'+10;
            modify(1,n,x,di);
        }
        else{
            int l,r; cin>>l>>r;
            cout<<(fill1021(query(1,n,l,r))-1+mod)%mod<<'\n';
        }
    }
}
