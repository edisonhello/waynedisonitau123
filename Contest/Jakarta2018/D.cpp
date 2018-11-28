#include<bits/stdc++.h>
using namespace std;

string s[505];

int main(){
    int n,m; cin>>n>>m;
    for(int i=0;i<n;++i)cin>>s[i];
    if(n>2 && m>2){
        int c=0;
        for(int i=1;i<n-1;++i)for(int j=1;j<m-1;++j)if(s[i][j]=='.')++c;
        bool side=0;
        for(int i=0;i<n;++i)for(int j=0;j<m;++j){
            int z=0;
            z+=i==0;
            z+=j==0;
            z+=i+1==n;
            z+=j+1==m;
            if(z==1 && s[i][j]=='#')side=1;
        }
        if(!side)++c;
        cout<<c<<endl;
        exit(0);
    }
    if(n<=2){
        int c=0;
        for(int j=1;j<m-1;++j){
            bool ha=0;
            for(int i=0;i<n;++i){
                if(s[i][j]=='#')ha=1;
            }
            if(!ha)++c;
        }
        cout<<c<<endl;
        exit(0);
    }
    if(m<=2){
        int c=0;
        for(int i=1;i<n-1;++i){
            bool ha=0;
            for(int j=0;j<m;++j){
                if(s[i][j]=='#')ha=1;
            }
            if(!ha)++c;
        }
        cout<<c<<endl;
        exit(0);
    }
}
