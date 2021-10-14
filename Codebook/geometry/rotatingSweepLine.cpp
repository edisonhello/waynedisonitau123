void rotatingSweepLine(vector<pair<int,int>> &ps){
  int n=int(ps.size());
  vector<int> id(n),pos(n);
  vector<pair<int,int>> line(n*(n-1)/2);
  int m=-1;
  for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)line[++m]=make_pair(i,j); ++m;
  sort(line.begin(),line.end(),[&](const pair<int,int> &a,const pair<int,int> &b)->bool{
      if(ps[a.first].first==ps[a.second].first)return 0;
      if(ps[b.first].first==ps[b.second].first)return 1;
      return (double)(ps[a.first].second-ps[a.second].second)/(ps[a.first].first-ps[a.second].first) < (double)(ps[b.first].second-ps[b.second].second)/(ps[b.first].first-ps[b.second].first);
      });
  for(int i=0;i<n;++i)id[i]=i;
  sort(id.begin(),id.end(),[&](const int &a,const int &b){ return ps[a]<ps[b]; });
  for(int i=0;i<n;++i)pos[id[i]]=i;

  for(int i=0;i<m;++i){
    auto l=line[i];
    // meow
    tie(pos[l.first],pos[l.second],id[pos[l.first]],id[pos[l.second]])=make_tuple(pos[l.second],pos[l.first],l.second,l.first);
  }
}
