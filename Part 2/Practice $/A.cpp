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
    
    vector<int> up[2],qry;
    int sz,INF=(1LL<<60)-1;

    segtree(int n){
       sz=n;
       up[0].assign(4*n+10,-1);
       qry.assign(4*n+10,0);
       up[1].assign(4*n+10,0);
    }
    
    void prop(int v,int l,int m,int r){
        
        int t1=2*v,t2=2*v+1;

        if(up[0][v]!=-1){
          up[0][t1]=up[0][t2]=up[0][v];
          up[1][t1]=up[1][t2]=0;
          qry[t1]=(m-l+1)*up[0][v];
          qry[t2]=(r-m)*up[0][v];
        }

         up[1][t1]+=up[1][v];
         up[1][t2]+=up[1][v];
         qry[t1]+=(m-l+1)*up[1][v];
         qry[t2]+=(r-m)*up[1][v];
         
         up[0][v]=-1;
         up[1][v]=0;
        
    }

    void update(int v,int l,int r,int ql,int qr,int val,int id){
        if(ql>qr) return;
        if(l==ql&&r==qr){
          if(id){
            up[id][v]+=val;
            qry[v]+=(r-l+1)*val;
          }
          else{
            up[id][v]=val;
            up[1-id][v]=0;
            qry[v]=(r-l+1)*val;
          }
          return;
        }

        int m=(l+r)/2;
        
        prop(v,l,m,r);

        update(2*v,l,m,ql,min(qr,m),val,id);
        update(2*v+1,m+1,r,max(ql,m+1),qr,val,id);
        qry[v]=(qry[2*v]+qry[2*v+1]);
    }

    void update(int l,int r,int v,int id){
       update(1,1,sz,l+1,r,v,id);
    }

    int query(int v,int l,int r,int ql,int qr){
       
       if(ql>qr) return 0;

       if(l==ql&&r==qr) return qry[v];

       int m=(r+l)/2;
       
       prop(v,l,m,r);

       int q=0;
       q+=query(2*v,l,m,ql,min(qr,m));
       q+=query(2*v+1,m+1,r,max(ql,m+1),qr);

       return q;
    }

    int query(int l,int r){
      return query(1,1,sz,l+1,r);
    }

};
 
 void kudne() 
 {
   int n,m; cin>>n>>m;
   segtree obj(n);

   for(int i=1;i<=m;++i){
    
       int tc; cin>>tc;

       if(tc!=3){
          int l,r,v,id=0; cin>>l>>r>>v;
          if(tc==2) id=1;
          obj.update(l,r,v,id); 
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
