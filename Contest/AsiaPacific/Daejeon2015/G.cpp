#include<bits/stdc++.h>
using namespace std;

struct point{
    int x,y;
    point(int x=0,int y=0):x(x),y(y){}
    point norm(){
        if(x)return point(x>0?1:-1,0);
        else return point(0,y>0?1:-1);
    }
};

ostream& operator<<(ostream &o,const point &p){
    o<<"("<<p.x<<","<<p.y<<")";
    return o;
}

bool operator<(const point &x,const point &y){
    return x.x==y.x?x.y>y.y:x.x<y.x;
}

point operator+(const point &a,const point &b){
    return point{a.x+b.x,a.y+b.y};
}
point operator-(const point &a,const point &b){
    return point{a.x-b.x,a.y-b.y};
}
point operator*(const point &p,const int x){
    return point(p.x*x,p.y*x);
}
long long operator^(const point &a,const point &b){
    return 1ll*a.x*b.y-1ll*a.y*b.x;
}
double dist(const point &a,const point &b){
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

struct Q{
    point p;
    int x,l;
};
bool operator<(const Q &a,const Q &b){ return tie(a.x,a.l)>tie(b.x,b.l); }
vector<Q> qs;

point pt[100005];

/* void print(stack<point> st){
    cout<<"[";
    while(st.size()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<"]";
} */

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin>>t; while(t--){
        int n; cin>>n;
        for(int i=0;i<n;++i)cin>>pt[i].x>>pt[i].y;

        int m; cin>>m;
        qs.resize(m);
        for(Q &q:qs){
            int p,k; cin>>p>>k;
            int pp=(p+1);
            if(pp>=n)pp-=n;
            point way=(pt[pp]-pt[p]).norm();
            q.p=pt[p]+way*k;
            q.x=p; q.l=k;
            // cout<<pt[p]<<" "<<pt[pp]<<endl;
            // cout<<"way: "<<way<<" , q.p: "<<q.p<<endl;
            // cout<<"query point: "<<q.p<<endl;
        }
        sort(qs.begin(),qs.end());

        double his=0;
        stack<point> bars;
        bars.push(pt[0]);
        auto addpoint=[&](point p)->void{
            // cout<<"adding point "<<p<<endl;
            while(bars.size()>1u){
                point last=bars.top(); bars.pop();
                if(((p-bars.top())^(last-bars.top()))>=0){
                    his-=dist(last,bars.top());
                    // cout<<"delete "<<last<<" in stack"<<endl;
                    // cout<<bars.top()<<" , "<<last<<" , "<<p<<endl;
                    // cout<<"cross: "<<(((p-bars.top())^(last-bars.top())))<<endl;
                    // cout<<"2vecs: "<<(p-bars.top())<<" and "<<(last-bars.top())<<endl;
                }
                else{
                    bars.push(last);
                    break;
                }
            }
            his+=dist(bars.top(),p);
            bars.push(p);
            // cout<<"push "<<p<<" in stack"<<endl;
            // cout<<"now his: "<<his<<endl;
        };

        int itr=n-1;
        double tot=0;
        for(Q &q:qs){
            // cout<<"doing query of point "<<q.p<<endl;
            while(itr>0 && itr>q.x){
                addpoint(pt[itr]);
                --itr;
            }
            // cout<<"current stack: "; print(bars); cout<<endl;
            addpoint(q.p);
            tot+=his;
        }
        cout<<fixed<<setprecision(1)<<tot<<'\n';
    }
}
