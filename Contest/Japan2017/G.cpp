#include<bits/stdc++.h>
using namespace std;

#define point pair<double,double>

point get(){
    string s; double ang,len;
    cin>>s>>ang>>len;
    if(s=="CD")ang+=60;
    if(s=="DB")ang+=120;
    ang=ang/360*2*acos(-1);
    return make_pair(cos(ang)*len,sin(ang)*len);
}

int fid(point p){
    // cout<<"orig: "<<p.first<<" "<<p.second<<endl;

    p.second/=(sqrt(3)/2);
    p.first-=p.second/2;
    
    // cout<<"trans: "<<p.first<<" "<<p.second<<endl;

    p.second-=floor(p.second/2)*2;
    p.first-=floor(p.first/2)*2;

    while(p.first<=0)p.first+=2;
    // cout<<"norm: "<<p.first<<" "<<p.second<<endl;

    double xy=p.first+p.second;
    // cout<<"xy: "<<xy<<endl;
    if(p.second>=0 && p.second<=1){
        if(p.first>=0 && p.first<=1){
            if(xy<=1)return 1;
            else return 0;
        }
        else{
            if(xy<=2)return 3;
            else return 2;
        }
    }
    else{
        if(p.first>=0 && p.first<=1){
            if(xy<=2)return 2;
            else return 3;
        }
        else{
            if(xy<=3)return 0;
            else return 1;
        }
    }
    assert(0);
}

int main(){
    point a=get(),b=get();
    cout<<(fid(a)==fid(b)?"YES":"NO")<<endl;
}
