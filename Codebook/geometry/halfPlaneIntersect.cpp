
bool jizz(Line l1,Line l2,Line l3){
    Point p=intersect(l2,l3);
    return ((l1.pb-l1.pa)^(p-l1.pa))<-eps;
}

bool cmp(const Line &a,const Line &b){
    return same(a.angle,b.angle)?(((b.pb-b.pa)^(a.pb-b.pa))>eps):a.angle<b.angle;
}

// availble area for Line l is (l.pb-l.pa)^(p-l.pa)>0
// if solution is a line gives no solution
vector<Point> HPI(vector<Line> &ls){
    sort(ls.begin(),ls.end(),cmp);
    vector<Line> pls(1,ls[0]); 
    for(unsigned int i=0;i<ls.size();++i)if(!same(ls[i].angle,pls.back().angle))pls.push_back(ls[i]);
    deque<int> dq; dq.push_back(0); dq.push_back(1);
    for(unsigned int i=2u;i<pls.size();++i){
        while(dq.size()>1u && jizz(pls[i],pls[dq.back()],pls[dq[dq.size()-2]]))dq.pop_back();
        while(dq.size()>1u && jizz(pls[i],pls[dq[0]],pls[dq[1]]))dq.pop_front();
        dq.push_back(i);
    }
    while(dq.size()>1u && jizz(pls[dq.front()],pls[dq.back()],pls[dq[dq.size()-2]]))dq.pop_back();
    while(dq.size()>1u && jizz(pls[dq.back()],pls[dq[0]],pls[dq[1]]))dq.pop_front();
    if(dq.size()<3u)return vector<Point>(); // no solution or solution is not a convex
    vector<Point> rt;
    for(unsigned int i=0u;i<dq.size();++i)rt.push_back(intersect(pls[dq[i]],pls[dq[(i+1)%dq.size()]]));
    return rt;
}
