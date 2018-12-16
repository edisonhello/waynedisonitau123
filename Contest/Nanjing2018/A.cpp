#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k; cin>>n>>k;
    if(n==0){
        cout<<"Austin"<<endl;
    }
    else if(k==1 && n%2==0){
        cout<<"Austin"<<endl;
    }
    else cout<<"Adrien"<<endl;
}
