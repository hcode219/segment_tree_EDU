#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=1e5+15;  
 const int M=N*4;           

  int freq[M][41],a[N];
  
  void build(int v,int l,int r){

     if(l==r){
         freq[v][a[l]]=1;
     }
     else{
         int m=(l+r)>>1;
         build(2*v,l,m); 
         build(2*v+1,m+1,r); 
         for(int i=40;i>=1;--i) 
         freq[v][i]=freq[2*v][i]+freq[2*v+1][i];
            
     }
  }
   
  vector<int> query(int v,int l,int r,int ql,int qr){
    
    vector<int> b; b.resize(41); 

    if(ql>qr) return b;
    if(l==ql&&r==qr){
       for(int i=0;i<=40;++i)
        b[i]=freq[v][i];
       return b;
    }
 
    int mid=(l+r)>>1;
    
    vector<int> q1(query(2*v,l,mid,ql,min(mid,qr))),q2(query(2*v+1,mid+1,r,max(mid+1,ql),qr));
    
    for(int i=40;i>=1;--i)
        b[i]=q1[i]+q2[i];
          
    return b;

  }
 
  void update(int v,int l,int r,int id,int val){
     
     if(l==r){
        freq[v][a[l]]--;
        freq[v][val]++;
        a[l]=val;
     }
     else{
        int m=(l+r)>>1;
        if(id<=m)
          update(2*v,l,m,id,val);
        else 
          update(2*v+1,m+1,r,id,val);

         for(int i=40;i>=1;--i)
            freq[v][i]=freq[2*v][i]+freq[2*v+1][i];
     }
  }
 
 void doit()
 { 
   int n,q; cin>>n>>q;

   for(int i=1;i<=n;++i) cin>>a[i];

   build(1,1,n);
   

   while(q--){
            
      int t,x,y; cin>>t>>x>>y;
     
      if(t==1){     
         vector<int> ans(query(1,1,n,x,y));
         int ct=0;
         for(int i=0;i<=40;++i) if(ans[i]>0) ct++;
         cout<<ct<<"\n";
      }
      else{
         update(1,1,n,x,y);
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
