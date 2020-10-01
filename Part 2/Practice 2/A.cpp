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
    
    vector<int> sm,mn;
    int sz,INF=1e18;

    segtree(int n){
       sz=n;
       mn.assign(4*n+10,0);
       sm.assign(4*n+10,0);
    }
    // void prop(int x){
    //     if(seg[x]!=-1){
    //        seg[2*x]=seg[x];
    //        seg[2*x+1]=seg[x];
    //        seg[x]=-1;
    //     }
    // }

    void update(int v,int l,int r,int ql,int qr,int val){
        if(ql>qr) return;
        // EVARS(v,l,r,ql,qr);
        if(l==ql&&r==qr){
          sm[v]+=val;
          mn[v]+=val;
          // EVARS(v,l,r,mn[v]);
          return;
        }
        // prop(v);
        int m=(l+r)/2;
        update(2*v,l,m,ql,min(qr,m),val);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val);
        mn[v]=min(mn[2*v],mn[2*v+1])+sm[v];
    }

    void update(int l,int r,int v){
       update(1,1,sz,l+1,r,v);
    }

    int query(int v,int l,int r,int ql,int qr,int val){
       if(ql>qr) return INF;
       // EVARS(v,l,r,ql,qr,val);
       if(l==ql&&r==qr){
          // EVARS(l,r,mn[v],val);
          return mn[v]+val;
        }

       int m=(l+r)/2;
       int q1=query(2*v,l,m,ql,min(qr,m),val+sm[v]);
       int q2=query(2*v+1,m+1,r,max(ql,m+1),qr,val+sm[v]);


      return min(q1,q2);
    }

    int query(int l,int r){
      return query(1,1,sz,l+1,r,0);
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
         int l,r; cin>>l>>r;
         cout<<obj.query(l,r)<<"\n";
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
