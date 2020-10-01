#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=1e5+15;  
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
   
  int query(int v,int l,int r,int k){
      
    if(l==r&&seg[v]==1){
       return l;
    }

    int m1=seg[2*v],m=(l+r)>>1;
    
    if(m1>=k)
     return query(2*v,l,m,k);
    else 
     return query(2*v+1,m+1,r,k-m1);
  }

  void update(int v,int l,int r,int id){
     
     if(l==r){
        seg[v]=0;
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
  /*
  4 1 3 5 2 

  */
 void doit()
 { 
   int n; cin>>n;
   for(int i=1;i<=n;++i) a[i]=1;
   build(1,1,n);
   
   vector<int> v(n+1),ans;
   for(int i=1;i<=n;++i) cin>>v[i];

   for(int i=n;i>=1;--i){ int pos=query(1,1,n,seg[1]-v[i]);
      ans.push_back(pos);
      update(1,1,n,pos);
   }

   for(int i=n-1;i>=0;--i) cout<<ans[i]<<" ";

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
