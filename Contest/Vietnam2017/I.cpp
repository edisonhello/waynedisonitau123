#include<bits/stdc++.h>
using namespace std;


int main(){
    set<string> st;
    int n; cin>>n; while(n--){
        string s,t; cin>>s>>t;
        if(st.size()>=12u || st.find(s)!=st.end())continue;
        st.insert(s);
        cout<<s<<" "<<t<<endl;
    }
}


