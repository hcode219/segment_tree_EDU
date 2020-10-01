#include"bits/stdc++.h"
using namespace std;

#define int long long
const int mod=1e9+7;

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

struct segtree{
    
    vector<int> up,qry;
    int sz,INF=(1LL<<60)-1;

    segtree(int n){
       sz=n;
       up.assign(4*n+10,0);
       qry.assign(4*n+10,0);
    }

    void update(int v,int l,int r,int ql,int qr,int val){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          qry[v]+=val;
          up[v]+=val;
          return;
        }
        
        // EVARS(v,l,r,ql,qr,val);

        int m=(l+r)/2;
    
        update(2*v,l,m,ql,min(qr,m),val);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val);
        qry[v]=max(qry[2*v],qry[2*v+1])+up[v];
    }

    void update(int l,int r,int val){
       update(1,1,sz,l+1,r,val);
    }

    int query(int v,int l,int r,int id,int val){
     

       // EVARS(v,qry[v],val);

       if(qry[v]<val) return -1;

       if(l==r){
          return l;
       }
       
       val-=up[v];

       // EVARS(v,l,r,id,val);

       int m=(l+r)/2,q=-1;
       if(id<=m) q=query(2*v,l,m,id,val);
       if(q==-1) q=query(2*v+1,m+1,r,id,val);

       return q;
    }

    int query(int x,int l){
      int ans=query(1,1,sz,l+1,x);
      if(ans!=-1) ans--;
      return ans;
    }

};
 
 void kudne() 
 {
   int n,m; cin>>n>>m;
   segtree obj(n);

   for(int i=1;i<=m;++i){
    
       int tc; cin>>tc;

       if(tc==1){
          int l,r,v; cin>>l>>r>>v;
          obj.update(l,r,v); 
       }
       else{
         int l,x; cin>>x>>l;
         cout<<obj.query(x,l)<<"\n";
       }
   }

 }

signed main()
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
