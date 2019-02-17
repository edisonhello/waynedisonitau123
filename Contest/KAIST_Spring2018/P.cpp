#include<bits/stdc++.h>
using namespace std;

int a[22][22],hi[22];
deque<int> las[22];

queue<tuple<int,int,int,int>> ans;

int main(){
    int n,m,k; cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
            if(!a[i][j])hi[j]=n-i;
        }
    }
    for(int i=1;i<=m;++i){
        if((hi[i]&1)==0)continue;
        int j=i;
        for(;j<=m;++j){
            if((hi[j]&1)==0)break;
        }
        --j;
        // cout<<"ij: "<<i<<" "<<j<<endl;
        if(i==j){
            if(j==n){
                set<int> st;
                st.insert(1);
                st.insert(2);
                st.insert(3);
                st.erase(a[n][i]);
                if(i>2 && (hi[i-2]&1))st.erase(a[n][i-2]);
                int fill=*st.begin();
                ans.emplace(0,i-1,fill,a[n][i]);
                ans.emplace(0,i-1,fill,fill);
                ans.emplace(0,i-1,fill,fill);
            }
            else{
                set<int> st;
                st.insert(1);
                st.insert(2);
                st.erase(a[n][i]);
                int fill=*st.begin();
                ans.emplace(0,i,a[n][i],fill);
                ans.emplace(0,i,fill,fill);
                ans.emplace(0,i,fill,fill);
            }
        }
        else if(((j-i+1)&1)==0){ // 2,2,2
            ans.emplace(0,i,a[n][i],a[n][i+1]);
            ++i;
        }
        else if(j==n){ // use front
            set<int> st;
            st.insert(1);
            st.insert(2);
            st.insert(3);
            st.erase(a[n][i]);
            if(i>2 && (hi[i-2]&1))st.erase(a[n][i-2]);
            int fill=*st.begin();
            ans.emplace(0,i-1,fill,a[n][i]);
            ans.emplace(0,i-1,fill,fill);
            ans.emplace(0,i-1,fill,fill);
        }
        else{ // use back
            ans.emplace(0,i,a[n][i],a[n][i+1]);
            ++i;
        }
    }
    for(int i=1;i<=m;++i){
        for(int j=n;j>=1;--j){
            if(a[j][i]==0)break;
            las[i].push_back(a[j][i]);
        }
        if(las[i].size()&1)las[i].pop_front();
    }
    for(int i=1;i<=m;++i){
        while(las[i].size()){
            int a=las[i].front(); las[i].pop_front();
            int b=las[i].front(); las[i].pop_front();
            ans.emplace(1,i,b,a);
        }
    }
    cout<<ans.size()<<endl;
    while(ans.size()){
        int a,b,c,d;
        tie(a,b,c,d)=ans.front(); ans.pop();
        cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    }
}
