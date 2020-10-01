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
    
    vector<int> up,qry,seg;
    int n,INF=(1LL<<60)-1;

    segtree(vector<int> &a){
       n=a.size()-1;
       up.assign(4*n+10,0);
       qry.assign(4*n+10,0);
       seg.assign(4*n+10,0);
       build(1,1,n,a);
    }

    void build(int v,int l,int r,vector<int> &a){
         if(l==r){
            seg[v]=a[l];
            qry[v]=a[l];
            return;
         }
         int m=(r+l)/2;
         build(2*v,l,m,a);
         build(2*v+1,m+1,r,a);
         seg[v]=seg[2*v]+seg[2*v+1];
         qry[v]=qry[2*v]+qry[2*v+1]+(m-l+1)*seg[2*v+1];
    }
    
    void prop(int v,int l,int m,int r){
        int t1=2*v,t2=2*v+1;
        int k=m-l+1;
        seg[t1]+=k*up[v];
        qry[t1]+=((k*(k+1))/2)*up[v];
        up[t1]+=up[v];
        k=r-m;
        seg[t2]+=k*up[v];
        qry[t2]+=((k*(k+1))/2)*up[v];
        up[t2]+=up[v];
        up[v]=0;
    }

    void update(int v,int l,int r,int ql,int qr,int val){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          int k=r-l+1;
          seg[v]+=k*val;
          qry[v]+=((k*(k+1))/2)*val;
          up[v]+=val;
          return;
        }

        int m=(l+r)/2;
        
        prop(v,l,m,r);

        update(2*v,l,m,ql,min(qr,m),val);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val);

        seg[v]=seg[2*v]+seg[2*v+1];
        qry[v]=qry[2*v]+qry[2*v+1]+(m-l+1)*seg[2*v+1];
    }

    void update(int l,int r,int v){
       update(1,1,n,l,r,v);
    }

    pair<int,int> query(int v,int l,int r,int ql,int qr){
       
       if(ql>qr) return {0,0};

       if(l==ql&&r==qr) return {seg[v],qry[v]};

       int m=(r+l)/2;
       
       prop(v,l,m,r);

       pair<int,int> p1,p2,ans;

       p1=query(2*v,l,m,ql,min(qr,m));
       p2=query(2*v+1,m+1,r,max(ql,m+1),qr);

       int t=min(qr,m)-ql+1; t=max(0LL,t);
       ans.first=p1.first+p2.first;
       ans.second=p1.second+p2.second+t*p2.first;

       return ans;
    }

    int query(int l,int r){
      return query(1,1,n,l,r).second;
    }

};
 
 void kudne() 
 {
   int n,m; cin>>n>>m;
   vector<int> a(n+1);
   for(int i=1;i<=n;++i) cin>>a[i];

   segtree obj(a);

   for(int i=1;i<=m;++i){
        
       int tc; cin>>tc;

       if(tc!=2){
          int l,r,v; cin>>l>>r>>v;
          obj.update(l,r,v); 
       }
       else{
         int l,r; cin>>l>>r;
         cout<<obj.query(l,r)<<"\n";
       }
   }


   // for(int i=1;i<=7;++i) EVARS(i,obj.up[0][i],obj.up[1][i],obj.qry[i]);

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
