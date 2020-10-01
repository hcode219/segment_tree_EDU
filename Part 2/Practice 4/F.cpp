// Tough one
#pragma GCC optimize("Ofast")
#include"bits/stdc++.h"
using namespace std;

// #define int long long
#define aniket main
const int mod=1e9+7;
const int N=2e6+26;

vector<string> split(const string& s, char c) {
    vector<string> v; stringstream ss(s); string x;
    while (getline(ss, x, c)) v.emplace_back(x); return move(v);
}
template<typename T, typename... Args>
inline string arrStr(T arr, int n) {
    stringstream s; s << "[";
    for(int i = 0; i < n - 1; i++) s << arr[i] << ",";
    s << arr[n - 1] << "]";
    return s.str();
}

#define EVARS(args...) {__evars_begin(__LINE__); __evars(split(#args, ',').begin(), args);}

inline void __evars_begin(int line) { cerr << "#" << line << ": "; }
template<typename T> inline void __evars_out_var(vector<T> val) { cerr << arrStr(val, val.size()); }
template<typename T> inline void __evars_out_var(T* val) { cerr << arrStr(val, 10); }
template<typename T> inline void __evars_out_var(T val) { cerr << val; }
inline void __evars(vector<string>::iterator it) { cerr << endl; }

template<typename T, typename... Args>
inline void __evars(vector<string>::iterator it, T a, Args... args) {
    cerr << it->substr((*it)[0] == ' ', it->length()) << "=";
    __evars_out_var(a);
    cerr << "; ";
    __evars(++it, args...);
}

map<int,int> m;
vector<int> pos(N);

struct segtree{
    
    vector<int> up,seg,qry,len;
    int n,rl,INF=INT_MAX;
    segtree(int sz,int k){
       n=sz; rl=k;
       up.assign(4*n+10,INF);
       seg.assign(4*n+10,0);
       qry.assign(4*n+10,0);
       len.assign(4*n+10,0);
       build(1,1,n);
    }

    void build(int v,int l,int r){
      if(l==r){
        len[v]=pos[l+1]-pos[l];
        return;
      }
      int m=(r+l)/2;
      build(2*v,l,m);
      build(2*v+1,m+1,r);
      len[v]=len[2*v]+len[2*v+1];
    }
    
    void prop(int v,int l,int r,int val){
        up[v]=val;
        seg[v]=len[v]*val;
        qry[v]=len[v]*val;
        if(val<0) qry[v]=val;
    }

    int ch;
    void update(int v,int l,int r,int ql,int qr,int val){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          prop(v,l,r,val);
          ch-=len[v];
          return;
        }

        int m=(l+r)/2;
        
        if(up[v]!=INF){
          prop(2*v,l,m,up[v]);
          prop(2*v+1,m+1,r,up[v]);
          up[v]=INF;
        }
        update(2*v,l,m,ql,min(qr,m),val);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val);
        seg[v]=seg[2*v] + seg[2*v+1];
        qry[v]=max(qry[2*v],seg[2*v]+qry[2*v+1]);
    }

    void update(int l,int r,int v){
       update(1,1,n,l,r,v);
    }

    int query(int v,int l,int r,int id){
       
       if(qry[v]<id) return -1;
 
       if(l==r){
         int ans=pos[l];
         int t=id/up[v];
         if(id%up[v]==0) t--;
         assert(up[v]>0);
         assert(t<len[v]);
         return ans+t-1;
       }
       
       int m=(l+r)/2;
       
       if(up[v]!=INF){
          prop(2*v,l,m,up[v]);
          prop(2*v+1,m+1,r,up[v]);
          up[v]=INF;
       }
       
       int q=query(2*v,l,m,id);
       if(q==-1) q=query(2*v+1,m+1,r,id-seg[2*v]);

       return q;
    }

    int query(int id){
      int ans=query(1,1,n,id+1);
      if(ans==-1) return rl;
      return ans;
    }

};
 
 void kudne() 
 {
   int n; cin>>n;
   char ch;
   vector<int> q,l,r,v;
   m[1],m[n],m[n+1];
   while(cin>>ch){
      if(ch=='E') break;
      if(ch=='I'){
         int x,y,z; cin>>x>>y>>z; m[x],m[y],m[y+1];
         q.push_back(1); l.push_back(x); r.push_back(y); v.push_back(z);
      }
      else{
         int h; cin>>h;
         q.push_back(0); l.push_back(-1); r.push_back(-1); v.push_back(h);
      }
   }

  int cnt=0;

  for(auto &x:m) { x.second=++cnt; pos[x.second]=x.first; 
  }

  
  segtree obj(cnt-1,n);
  int sz=q.size();
  for(int i=0;i<sz;++i){
      if(q[i]) obj.update(m[l[i]],m[r[i]],v[i]);      
      else cout<<obj.query(v[i])<<"\n";
  }


 }

signed aniket()
{ 
   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   #ifndef ONLINE_JUDGE
   freopen("input.txt","r", stdin); 
   freopen("output.txt","w", stdout);
   freopen("error.txt","w", stderr); 
   #endif

   int tc=1;                         
   // cin>>tc;
   
  for(int i=1;i<=tc;++i)
  { // cout<<"Case #"<<i<<": ";
  
   kudne();
   if(i<tc)
   cout<<"\n";
  }
  
  #ifndef ONLINE_JUDGE
  cerr<<(1000*clock())/CLOCKS_PER_SEC<<"ms";
  #endif

 return 0; 
}
