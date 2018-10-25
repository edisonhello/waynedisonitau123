#include<bits/stdc++.h>
using namespace std;

int hero[123];
int a[123];
int id[123];

namespace storage{
int _[3][123];
void backup(){
    for(int i=0;i<123;++i)_[0][i]=hero[i];
    for(int i=0;i<123;++i)_[1][i]=a[i];
    for(int i=0;i<123;++i)_[2][i]=id[i];
}
void reset(){
    for(int i=0;i<123;++i)hero[i]=_[0][i];
    for(int i=0;i<123;++i)a[i]=_[1][i];
    for(int i=0;i<123;++i)id[i]=_[2][i];
}
}

int main(){
    int n,m; cin>>n>>m;
    for(int i=0;i<m;++i){
        int x,h; cin>>x>>h;
        hero[x]=h;
        id[x]=i+1;
    }
    for(int i=1;i<=n;++i)cin>>a[i];
    storage::backup();
    for(int i=1;i<=n;++i){
        storage::reset();
        vector<int> goes;
        for(int j=i;j>=1;--j){
            if(id[j]){
                int v_h=hero[j];
                bool ok=1;
                for(int k=j;k<=i;++k){
                    v_h+=a[k];
                    if(v_h<0)ok=0;
                }
                // cout<<"hero "<<id[j]<<" have left "<<v_h<<endl;
                if(!ok)continue;
                goes.push_back(id[j]);
                id[j]=0;
                for(int k=j;k<=i;++k){
                    a[k]=0;
                    if(id[k]){
                        goes.push_back(id[k]);
                        id[k]=0;
                    }
                }
            }
        }
        for(int j=i;j<=n;++j){
            if(id[j]){
                int v_h=hero[j];
                bool ok=1;
                for(int k=j;k>=i;--k){
                    v_h+=a[k];
                    if(v_h<0)ok=0;
                }
                if(!ok)continue;
                goes.push_back(id[j]);
                id[j]=0;
                for(int k=j;k>=i;--k){
                    a[k]=0;
                    if(id[k]){
                        goes.push_back(id[k]);
                        id[k]=0;
                    }
                }
            }
        }
        for(int j=i;j>=1;--j){
            if(id[j]){
                int v_h=hero[j];
                bool ok=1;
                for(int k=j;k<=i;++k){
                    v_h+=a[k];
                    if(v_h<0)ok=0;
                }
                if(!ok)continue;
                goes.push_back(id[j]);
                id[j]=0;
                for(int k=j;k<=i;++k){
                    a[k]=0;
                    if(id[k]){
                        goes.push_back(id[k]);
                        id[k]=0;
                    }
                }
            }
        }
////        cout<<"finish at "<<i<<" goes: "<<goes.size()<<endl;
        if(goes.size()!=m)continue;
        cout<<i<<endl;
        for(int i:goes)cout<<i<<" "; cout<<endl;
        exit(0);
    }
    cout<<-1<<endl;
}
