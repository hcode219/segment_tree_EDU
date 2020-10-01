#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=1e5+15;  
 const int M=N*4;           
 
  int seg[M],sum[M],pre[M],suf[M],a[N];
  
  void build(int v,int l,int r){
      
     // D3(v,l,r);
     if(l==r){
         seg[v]=max(a[l],0LL);
         pre[v]=suf[v]=seg[v];
         sum[v]=a[l];
     }
     else{
         int m=(l+r)>>1;
         build(2*v,l,m);
         build(2*v+1,m+1,r);
         pre[v]=max(pre[2*v],sum[2*v]+pre[2*v+1]);
         suf[v]=max(suf[2*v+1],suf[2*v]+sum[2*v+1]);
         sum[v]=sum[2*v]+sum[2*v+1];
         seg[v]=max({seg[2*v],seg[2*v+1],suf[2*v]+pre[2*v+1]});
     }

     // D3(l,r,seg[v]);
  }
   
   /*
  

  2
  0
  2
*/
  void update(int v,int l,int r,int id){
     
     if(l==r){
        seg[v]=max(a[l],0LL);
        pre[v]=suf[v]=seg[v];
        sum[v]=a[l];
     }
     else{
        int m=(l+r)>>1;
        if(id<=m)
          update(2*v,l,m,id);
        else 
          update(2*v+1,m+1,r,id);
         pre[v]=max(pre[2*v],sum[2*v]+pre[2*v+1]);
         suf[v]=max(suf[2*v+1],suf[2*v]+sum[2*v+1]);
         sum[v]=sum[2*v]+sum[2*v+1];
         seg[v]=max({seg[2*v],seg[2*v+1],suf[2*v]+pre[2*v+1]});
     }
  }

 void doit()
 { 
   int n,m; cin>>n>>m;
   for(int i=1;i<=n;++i) cin>>a[i];
   build(1,1,n);
   cout<<seg[1]<<"\n";

   while(m--){
      int id,val; cin>>id>>val; id++;
      a[id]=val;
      update(1,1,n,id);
      cout<<seg[1]<<"\n";
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
  
   doit();
   if(i<tc)
   cout<<"\n";
  }
  
  #ifndef ONLINE_JUDGE
  cerr<<(1000*clock())/CLOCKS_PER_SEC<<"ms";
  #endif

 return 0; 
}
