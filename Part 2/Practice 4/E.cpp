// #pragma GCC optimize("Ofast")
#include"bits/stdc++.h"
using namespace std;

// #define int long long
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
    
    vector<int> up,lw;
    int n,INF=1e5;

    segtree(int sz){
       n=sz;
       up.assign(4*n+10,INF);
       lw.assign(4*n+10,0);
    }

    inline void prop(int v,int lb,int ub){
      
        if(lb>=up[v]){
           lw[v]=up[v]=lb;
        }
        else if(ub<=lw[v]){
           lw[v]=up[v]=ub;
        }
        else{
          lw[v]=max(lw[v],lb);
          up[v]=min(up[v],ub);
        }

    }
    

    void update(int v,int l,int r,int ql,int qr,int val,int id){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          if(id)
          prop(v,0,val);
          else
          prop(v,val,INF);
          return;
        }

        int m=(l+r)/2;
        
        prop(2*v,lw[v],up[v]);
        prop(2*v+1,lw[v],up[v]);
        lw[v]=0; up[v]=INF;

        update(2*v,l,m,ql,min(qr,m),val,id);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val,id);
    }

    void update(int l,int r,int v,int id){
       update(1,1,n,l+1,r+1,v,id);
    }

     void query(int v,int l,int r){
       
       if(l==r){
        cout<<lw[v]<<"\n";
        return;
       }
 
       int m=(l+r)/2;
       
       prop(2*v,lw[v],up[v]);
       prop(2*v+1,lw[v],up[v]);
       lw[v]=0; up[v]=INF;

       query(2*v,l,m);
       query(2*v+1,m+1,r);
    }

    void query(){
      query(1,1,n);
    }

};
 
 void kudne() 
 {
   int n,k; cin>>n>>k;
   
   segtree obj(n);

   for(int i=1;i<=k;++i){
       int tc,l,r,v;; cin>>tc>>l>>r>>v;
       obj.update(l,r,v,(tc==2));
   }
  
  obj.query();

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
