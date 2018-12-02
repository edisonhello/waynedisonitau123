#include<bits/stdc++.h>
using namespace std;

void out(vector<tuple<int,int,int>> &v){
    cout<<v.size()<<endl;
    for(auto p:v){
        int a,b,c; tie(a,b,c)=p;
        cout<<a<<" "<<b<<" "<<c<<'\n';
    }
    exit(0);
}

int main(){
    int a,b,c; cin>>a>>b>>c;
    if(a>=b && a>=c){
        if(a<=b*c && a>=max(b,c)){
            vector<tuple<int,int,int>> ans;
            for(int x=1;x<=b;++x){
                for(int y=1;y<=c;++y){
                    int p=0;
                    p=(x==y || min(x,y)==min(b,c) && max(x,y)>min(b,c));
                    if(p==1)ans.emplace_back(x,y,0);
                }
            }
            for(int x=1;x<=b;++x){
                for(int y=1;y<=c;++y){
                    if(ans.size()>=a)break;
                    int p=0;
                    p=(x==y || min(x,y)==min(b,c) && max(x,y)>min(b,c));
                    if(p!=1)ans.emplace_back(x,y,0);
                }
            }
            out(ans);
        }
    }
    if(b>=a && b>=c){
        if(b<=a*c && b>=max(a,c)){
            vector<tuple<int,int,int>> ans;
            for(int x=1;x<=a;++x){
                for(int z=1;z<=c;++z){
                    int p=0;
                    p=(x==z || min(x,z)==min(a,c) && max(x,z)>min(a,c));
                    if(p==1)ans.emplace_back(x,0,z);
                }
            }
            for(int x=1;x<=a;++x){
                for(int z=1;z<=c;++z){
                    if(ans.size()>=b)break;
                    int p=0;
                    p=(x==z || min(x,z)==min(a,c) && max(x,z)>min(a,c));
                    if(p!=1)ans.emplace_back(x,0,z);
                }
            }
            out(ans);
        }
    }
    if(c>=a && c>=b){
        if(c<=a*b && c>=max(a,b)){
            vector<tuple<int,int,int>> ans;
            for(int y=1;y<=a;++y){
                for(int z=1;z<=b;++z){
                    int p=0;
                    p=(y==z || min(y,z)==min(a,b) && max(y,z)>min(a,b));
                    if(p==1)ans.emplace_back(0,y,z);
                }
            }
            for(int y=1;y<=a;++y){
                for(int z=1;z<=b;++z){
                    if(ans.size()>=c)break;
                    int p=0;
                    p=(y==z || min(y,z)==min(a,b) && max(y,z)>min(a,b));
                    if(p!=1)ans.emplace_back(0,y,z);
                }
            }
            out(ans);
        }
    }
    cout<<-1<<endl;
}
