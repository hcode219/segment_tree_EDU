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
    
    vector<int> up;
    struct node{
       int pre,suf,sum,mx;
       node(){
        pre=suf=sum=mx=0;
       }
    };
    vector<node> qry;
    int sz,INF=(1LL<<60)-1;

    segtree(int n){
       sz=n;
       up.assign(4*n+10,INF);
       qry.resize(4*n+10);
    }

    node combine(const node& p1,const node& p2){
       node r;
       r.sum=p1.sum+p2.sum;
       r.mx=max({p1.mx,p2.mx,p1.suf+p2.pre});
       r.pre=max(p1.pre,p1.sum+p2.pre);
       r.suf=max(p2.suf,p2.sum+p1.suf);
       return r;
    }

    void update(int v,int l,int r,int ql,int qr,int val){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          up[v]=val;
          qry[v].sum=(r-l+1)*val;
          int k=0; if(val>0) k=qry[v].sum;
          qry[v].suf=qry[v].pre=qry[v].mx=k;
          return;
        }

        int m=(l+r)/2;

        if(up[v]!=INF){
           qry[2*v].sum=(m-l+1)*up[v];
           qry[2*v+1].sum=(r-m)*up[v];
           up[2*v]=up[2*v+1]=up[v];
           int k=0; if(qry[2*v].sum>0) k=qry[2*v].sum;
           qry[2*v].suf=qry[2*v].mx=qry[2*v].pre=k;
           k=0; if(qry[2*v+1].sum>0) k=qry[2*v+1].sum;
           qry[2*v+1].suf=qry[2*v+1].mx=qry[2*v+1].pre=k;
           up[v]=INF;
        }
    
        update(2*v,l,m,ql,min(qr,m),val);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val);
        qry[v]=combine(qry[2*v],qry[2*v+1]);
    }

    void update(int l,int r,int v){
       update(1,1,sz,l+1,r,v);
    }

    // int query(int v,int l,int r,int ql,int qr){
    //    if(ql>qr) return node();
    //    if(l==ql&&r==qr){
    //       return qry[v];
    //     }
        
    //    int m=(l+r)/2,q;
       
    //    if(up[v]!=-1){
    //        qry[2*v].sum=(m-l+1)*up[v];
    //        qry[2*v+1].sum=(r-m)*up[v];
    //        up[2*v]=up[2*v+1]=up[v];
    //        int k=0; if(qry[2*v].sum>0) k=qry[2*v].sum;
    //        qry[2*v].suf=qry[2*v].mx=qry[2*v].pre=k;
    //        k=0; if(qry[2*v+1].sum>0) k=qry[2*v+1].sum;
    //        qry[2*v+1].suf=qry[2*v+1].mx=qry[2*v+1].pre=k;
    //        up[v]=-1;
    //     }
       
    //    node q1=query(2*v,l,m,ql,min(qr,m));
    //    node q2=query(2*v+1,m+1,r,max(ql,m+1),qr);
    //    return combine();
    // }

    // int query(int l,int r){
    //   return query(1,1,sz,l+1,r).mx;
    // }
};
 
 void kudne() 
 {
   int n,m; cin>>n>>m;
   segtree obj(n);

   for(int i=1;i<=m;++i){
          int l,r,v; cin>>l>>r>>v;
          obj.update(l,r,v);
          cout<<obj.qry[1].mx<<"\n";
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
