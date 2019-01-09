#include<bits/stdc++.h>
using namespace std;


int main(){
#ifdef ONLINE_JUDGE
    freopen("jubilee.in", "r", stdin);
    freopen("jubilee.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while(cin>>n,n){
        if(n==3){
            cout<<"1"<<'\n';
            cout<<"1 1 1\n";
            cout<<"1 1 1\n";
        }
        else if(n==4){
            cout<<"2"<<'\n';
            cout<<"1 1 2 2\n";
            cout<<"1 2 1 2\n";
        }
        else if(n==5){
            cout<<"2"<<'\n';
            cout<<"1 1 2 2 2\n";
            cout<<"1 1 2 1 1\n";
        }
        else if(n==6){
            cout<<"2"<<'\n';
            cout<<"2 2 2 1 1 1\n";
            cout<<"1 2 1 2 1 2\n";
        }
        else if(n>=7){
            cout<<"3\n";
            vector<int> a;
            for(int i=1;i<=n;++i)a.push_back((i&1)+1);
            if(a.back()==a[0])a.back()=3;
            for(int i=0;i<n;++i)cout<<a[i]<<" "; cout<<'\n';
            for(int i=0;i<n;++i){
                int v[4]={0};
                v[a[i]]=1;
                v[a[(i+1)%n]]=1;
                for(int z=1;z<=3;++z)if(!v[z])cout<<z<<" ";
            }
            cout<<'\n';
        }
    }
}
