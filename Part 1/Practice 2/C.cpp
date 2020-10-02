#include"bits/stdc++.h"
using namespace std;

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
         seg[v]=max(seg[2*v],seg[2*v+1]);
     }
  }
  
  int query(int v,int l,int r,int k){
      
    if(seg[v]<k) return-1;

    if(l==r){
       return l;
    }

    int lt=seg[2*v],rt=seg[2*v+1],mid;
    mid=(l+r)>>1;
    if(lt>=k)
     return query(2*v,l,mid,k);
    else 
     return query(2*v+1,mid+1,r,k);
  }

  void update(int v,int l,int r,int id){
     
     if(l==r){
        seg[v]=a[l];
     }
     else{
        int m=(l+r)>>1;
        if(id<=m)
          update(2*v,l,m,id);
        else 
          update(2*v+1,m+1,r,id);
         seg[v]=max(seg[2*v],seg[2*v+1]);
     }
  }

 void doit()
 { 
   int n,m; cin>>n>>m;
   for(int i=1;i<=n;++i) cin>>a[i];
   build(1,1,n);
   
   while(m--){
      int t; cin>>t; 
      if(t==1){
         int id,val; cin>>id>>val;  id++;
         a[id]=val;
         update(1,1,n,id);
      }
      else{
         int val; cin>>val; val=query(1,1,n,val);
         if(val!=-1) cout<<val-1;
         else cout<<-1;
         cout<<"\n";
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
