namespace DC3{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

#define SG(v,i) ((i)>=int(v.size())?0:v[i])
    inline bool smaller(int a, int b, vector<int> &r){
        if(SG(r,a+0) != SG(r,b+0)) return SG(r,a+0)<SG(r,b+0);
        if(SG(r,a+1) != SG(r,b+1)) return SG(r,a+1)<SG(r,b+1);
        return SG(r,a+2)<SG(r,b+2);
    }
    
    int cc[100005];
    inline vector<int> sort(vector<int> &r, int o, vector<int> &ix, int m){
        vector<int> rt(ix.size());
        for(int z=0;z<o;++z) r.push_back(0);
        for(int i=0;i<=m;++i) cc[i] = 0;
        for(int i=0;i<ix.size();++i) ++cc[r[ix[i]+o]];
        for(int i=0;i<=m;++i) cc[i+1] += cc[i];
        for(int i=ix.size()-1;i>=0;--i) rt[--cc[r[ix[i]+o]]] = ix[i];
        for(int z=0;z<o;++z) r.pop_back();
        return rt;
    }

    vector<int> dc3(vector<int> &v, int n, int m){
        int c1 = (n+1)/3;
        vector<int> i12;
        for(int i=0;i<n;++i){
            if(i%3==0)continue;
            i12.push_back(i);
        }
        i12 = sort(v, 2, i12, m);
        i12 = sort(v, 1, i12, m);
        i12 = sort(v, 0, i12, m);

        int nr = 1;
        vector<int> r12(i12.size());
#define GRI(x) ((x)/3 + ((x)%3==2?c1:0))
        r12[GRI(i12[0])] = 1;
        for(int i=1;i<i12.size();++i){
            if(smaller(i12[i-1], i12[i], v)) r12[GRI(i12[i])] = ++nr;
            else r12[GRI(i12[i])] = nr;
        }

#define GEI(x) ((x)<c1?(x)*3+1:(x-c1)*3+2)
        if(nr != i12.size()){
            i12 = dc3(r12, i12.size(), nr);
            
            for(int i=0;i<i12.size();++i) r12[i12[i]] = i+1;
            for(int &i: i12) i = GEI(i);
        }

        vector<int> i0;
        if(n%3==1) i0.push_back(n-1);
        for(int i=0;i<i12.size();++i) if(i12[i]%3 == 1) i0.push_back(i12[i]-1);
        i0 = sort(v, 0, i0, m);

        vector<int> ret(v.size());
        int ptr12=0, ptr0=0, ptr=0;
        while(ptr12<i12.size() && ptr0<i0.size()){
            if(i12[ptr12]%3 == 1){
                if([&](int i, int j) -> bool{
                    if(SG(v,i) != SG(v,j)) return SG(v,i)<SG(v,j);
                    return SG(r12,GRI(i+1))<SG(r12,GRI(j+1));
                }(i12[ptr12], i0[ptr0]))ret[ptr++] = i12[ptr12++];
                else ret[ptr++] = i0[ptr0++];
            }
            else{
                if([&](int i, int j) -> bool{
                    if(SG(v,i+0) != SG(v,j+0)) return SG(v,i+0)<SG(v,j+0);
                    if(SG(v,i+1) != SG(v,j+1)) return SG(v,i+1)<SG(v,j+1);
                    return SG(r12,GRI(i+2))<SG(r12,GRI(j+2));
                }(i12[ptr12], i0[ptr0]))ret[ptr++] = i12[ptr12++];
                else ret[ptr++] = i0[ptr0++];
            }
        }
        while(ptr12<i12.size()) ret[ptr++] = i12[ptr12++];
        while(ptr0<i0.size()) ret[ptr++] = i0[ptr0++];

        return ret;
    }
    vector<int> build(string str){
        vector<int> val(str.size()+1, 0);
        for(int i=0;i<str.size();++i) val[i] = str[i];
        return dc3(val, val.size(), 255);
    }
#pragma GCC diagnostic pop
}
