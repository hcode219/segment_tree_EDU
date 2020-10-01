#include"bits/stdc++.h"
using namespace std;

// #define int long long
const int mod=1e9+7;
const int N=5e5+55;
const int M=2*N;

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
    
    vector<int> ct,len,up;
    vector<bool> lt,rt;
    int sz;

    segtree(){
       sz=M;
       ct.assign(4*M+10,0);
       len.assign(4*M+10,0);
       lt.assign(4*M+10,false);
       rt.assign(4*M+10,false);
       up.assign(4*M+10,-1);
    }
    
    void doit(int v,int id,int l,int r){
         if(id==0){
             len[v]=0;
             ct[v]=0;
             lt[v]=rt[v]=false;
             up[v]=0;
         }
         else{
            len[v]=r-l+1;
            ct[v]=1;
            lt[v]=rt[v]=true;
            up[v]=1;
         }
    }
    void update(int v,int l,int r,int ql,int qr,int col){
        
        if(ql>qr) return;
       
        if(l==ql&&r==qr){
          doit(v,col,l,r); 
          return;
        }

        int m=(l+r)/2;
        
        if(up[v]!=-1){
          doit(2*v,up[v],l,m);
          doit(2*v+1,up[v],m+1,r);
          up[v]=-1;
        }
        update(2*v,l,m,ql,min(qr,m),col);
        update(2*v+1,m+1,r,max(ql,m+1),qr,col);

        len[v]=len[2*v]+len[2*v+1];
        ct[v]=ct[2*v]+ct[2*v+1];
        if(lt[2*v+1]&&rt[2*v]) ct[v]--;
        lt[v]=lt[2*v]; rt[v]=rt[2*v+1];
    }

    void update(int l,int r,int col){
       update(1,1,sz,l+N,l+N+r-1,col);
    }
   
};
 

 void kudne() 
 {
   int n; cin>>n;
   segtree obj;

   for(int i=1;i<=n;++i){

          char ch; int l,r,id=1; cin>>ch>>l>>r;
          if(ch=='W') id=0;
          obj.update(l,r,id);
          cout<<obj.ct[1]<<" "<<obj.len[1]<<"\n";
   }
   
   // for(int i=1;i<=13;++i) EVARS(i,obj.ct[i],obj.len[i]);
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
