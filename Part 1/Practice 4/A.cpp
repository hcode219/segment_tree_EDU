#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=2e5+15;  
 const int M=N*4;           
 
  int seg[M][2],a[N];
  
  void build(int v,int l,int r){
     if(l==r){
         if(l%2)
         seg[v][0]=a[l];
         else
         seg[v][1]=a[l];
     }
     else{
         int m=(l+r)>>1;
         build(2*v,l,m);
         build(2*v+1,m+1,r);
         seg[v][0]=seg[2*v][0]+seg[2*v+1][0];
         seg[v][1]=seg[2*v][1]+seg[2*v+1][1];
     }
  }
   
  int query(int v,int l,int r,int ql,int qr,int id){
    
    if(ql>qr) return 0;
    if(l==ql&&r==qr){
       return seg[v][id];
    }

    int mid=(l+r)>>1;

     return query(2*v,l,mid,ql,min(mid,qr),id) + query(2*v+1,mid+1,r,max(mid+1,ql),qr,id);
  }

  void update(int v,int l,int r,int id,int val){
     
     if(l==r){
        if(l%2)
         seg[v][0]=a[l];
         else
         seg[v][1]=a[l];
     }
     else{
        int m=(l+r)>>1;
        if(id<=m)
          update(2*v,l,m,id,val);
        else 
          update(2*v+1,m+1,r,id,val);
        seg[v][0]=seg[2*v][0]+seg[2*v+1][0];
        seg[v][1]=seg[2*v][1]+seg[2*v+1][1];
     }
  }

 void doit()
 { 
   int n; cin>>n;
   for(int i=1;i<=n;++i) cin>>a[i];
   build(1,1,n);

   int m; cin>>m;

   while(m--){
     int t,l,r; cin>>t>>l>>r;

     if(t){
        int a1=query(1,1,n,l,r,0),a2=query(1,1,n,l,r,1);
        if(l%2)
          cout<<a1-a2<<"\n";
        else
          cout<<a2-a1<<"\n";
     }
     else{
        a[l]=r;
        update(1,1,n,l,r);
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
  
   doit();
   if(i<tc)
   cout<<"\n";
  }
  
  #ifndef ONLINE_JUDGE
  cerr<<(1000*clock())/CLOCKS_PER_SEC<<"ms";
  #endif

 return 0; 
}
