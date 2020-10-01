#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=2e5+15;  
 const int M=N*4;           
 
  int seg[M],a[N];
  
  void build(int v,int l,int r){
     if(l==r){
         seg[v]=a[l];
     }
     else{
         int m=(l+r)>>1;
         build(2*v,l,m);
         build(2*v+1,m+1,r);
         seg[v]=seg[2*v]+seg[2*v+1];
     }
  }
   
  int query(int v,int l,int r,int ql,int qr){
    
    if(ql>qr) return 0;
    if(l==ql&&r==qr){
       return seg[v];
    }

    int mid=(l+r)>>1;

     return query(2*v,l,mid,ql,min(mid,qr)) + query(2*v+1,mid+1,r,max(mid+1,ql),qr);
  }

  void update(int v,int l,int r,int id){
     
     if(l==r){
        seg[v]=1;
     }
     else{
        int m=(l+r)>>1;
        if(id<=m)
          update(2*v,l,m,id);
        else 
          update(2*v+1,m+1,r,id);
         seg[v]=seg[2*v]+seg[2*v+1];
     }
  }

 void doit()
 { 
   int n; cin>>n;
   vector<int> v(2*n+1); for(int i=1;i<=2*n;++i) cin>>v[i];

   vector<int> pos(n+1),ans(n+1);

   for(int i=1;i<=2*n;++i){

       if(pos[v[i]]){
         ans[v[i]]=query(1,1,2*n,pos[v[i]],i);
         update(1,1,2*n,pos[v[i]]);
       }
       else
        pos[v[i]]=i;
   }

   for(int i=1;i<=n;++i) cout<<ans[i]<<" ";

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
  
   doit();
   if(i<tc)
   cout<<"\n";
  }
  
  #ifndef ONLINE_JUDGE
  cerr<<(1000*clock())/CLOCKS_PER_SEC<<"ms";
  #endif

 return 0; 
}
