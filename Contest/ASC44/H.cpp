#include<bits/stdc++.h>
using namespace std;

string ans[105];

struct ob{
    int u,v,i;
    vector<int> e;
    ob(int u=0,int v=0,int i=0):u(u),v(v),i(i){ e.clear(); }
} a[105];

/* auto cmp=[&](const ob *&a,const ob *&b){
    return make_pair(a->u,a->i)<make_pair(b->u,b->i);
}; */

struct cmp {
    bool operator()(const ob *a, const ob *b) const {
        return make_pair(a->u,a->i)<make_pair(b->u,b->i);
    }
};

set<ob*,cmp> st[205];

int main(){
#ifdef ONLINE_JUDGE
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
#endif
    int n; while(cin>>n,n){
        for(int i=0;i<205;++i)st[i].clear();
        for(int i=0;i<n;++i){
            cin>>a[i].u>>a[i].v;
            a[i].i=i;
            a[i].e.clear();
            a[i].e.push_back(i);
            ans[i]="";
            st[a[i].u+a[i].v].insert(&a[i]);
        }
        bool no=0;
        for(int i=204;i>=1;--i){
            if(st[i].size()&1){
                no=1;
                break;
            }
            while(st[i].size()){
                ob *fi=*st[i].begin(); st[i].erase(st[i].begin());
                ob tmp(fi->u+1,0,-1);
                auto it=st[i].lower_bound(&tmp);
                if(it==st[i].end()){ no=1; break; }
                ob *se=*it; st[i].erase(it);
                if(se->u!=fi->u+1){ no=1; break; }
                for(int z:fi->e)ans[z]+="1";
                for(int z:se->e)ans[z]+="0";
                for(int z:se->e)fi->e.push_back(z);
                --fi->v;
                st[fi->u+fi->v].insert(fi);
            }
        }
        if(st[0].size()!=1u){
            no=1;
        }
        if(no){
            cout<<"No"<<endl;
            continue;
        }
        cout<<"Yes"<<endl;
        for(int i=0;i<n;++i)reverse(ans[i].begin(),ans[i].end());
        for(int i=0;i<n;++i)cout<<ans[i]<<"\n";
    }
}
