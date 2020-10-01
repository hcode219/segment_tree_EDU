#include"bits/stdc++.h"
using namespace std;

#define int long long
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<"\n"
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<"\n"
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<"\n"
 const int N=2e5+15;  
 const int M=N*4;           
 
 int r;

 class matrix{

   public:

     int mat[2][2];
     
     matrix(){
       mat[0][0]=mat[1][1]=1;
       mat[0][1]=mat[1][0]=0;
     }
   
    matrix operator * (matrix &c){
        
        matrix x;

        for(int i=0;i<2;++i){

           for(int j=0;j<2;++j){
               x.mat[i][j]=0;
               for(int k=0;k<2;++k)
                x.mat[i][j]+=mat[i][k]*c.mat[k][j];
              x.mat[i][j]%=r;
           }
        }

        return x;
    }

    void operator = (matrix &c){
        for(int i=0;i<2;++i){

           for(int j=0;j<2;++j){
               mat[i][j]=c.mat[i][j];
           }
        }
    }

 }id;

ostream& operator << (ostream& out,matrix &c){

        for(int i=0;i<2;++i)
        {
          for(int j=0;j<2;++j) out<<c.mat[i][j]<<" ";
          out<<"\n";
        }

        return out;
  }

istream& operator >> (istream &in,matrix &c){

     for(int i=0;i<2;++i)
        {
          for(int j=0;j<2;++j) in>>c.mat[i][j];
        }

        return in;
}
  
   matrix seg[M],a[N];
  
  void build(int v,int l,int r){
     if(l==r){
         seg[v]=a[l];
     }
     else{
         int m=(l+r)>>1;
         build(2*v,l,m);
         build(2*v+1,m+1,r);
         matrix k=seg[2*v]*seg[2*v+1];
         seg[v]=k;
     }
  }
   
  matrix query(int v,int l,int r,int ql,int qr){
    
    if(ql>qr) return id;
    if(l==ql&&r==qr){
       return seg[v];
    }
    int mid=(l+r)>>1;
    matrix a=query(2*v,l,mid,ql,min(mid,qr)),b=query(2*v+1,mid+1,r,max(mid+1,ql),qr);
    return a*b;
  }
 
 
 
 void doit()
 { 
   int n,m; cin>>r>>n>>m; 

   for(int i=1;i<=n;++i){
     cin>>a[i];
   }
   
   build(1,1,n);

   while(m--){

      int l,r; cin>>l>>r;
      matrix ans=query(1,1,n,l,r);
      cout<<ans<<"\n";
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
