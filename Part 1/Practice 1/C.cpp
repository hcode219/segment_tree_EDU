#include"bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds; 
using namespace std;

#define double long double
#define int long long
#define pb push_back 
#define eb emplace_back
#define Z(c) (int)(c).size()
#define L(c) c[Z(c)-1]
#define F first
#define S second
#define nl "\n"
#define mii map<int,int>
#define sp fixed<<setprecision 
#define all(c) (c).begin(),(c).end()
#define rall(c) (c).rbegin(),(c).rend()
#define rep(i,iv,n) for(int (i)=(iv);(i)<(n);++(i))
#define FO fflush(stdout) 
#define D1(x) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<nl
#define D2(x,y) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<nl
#define D3(x,y,z) cerr <<"At line "<<__LINE__<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<nl
#define tr(it,ct) for(auto &(it) : (ct))
#define pi acos(-1)
#define prt(ct) for(auto &(it) : (ct)) cerr<<it<<" "; cerr<<nl
#define prtp(ct) for(auto &(it) : (ct)) cerr<<it.F<<" "<<it.S<<nl; cerr<<nl

typedef vector< int > vi;
typedef vector< vi > vvi;
typedef pair< int,int > pii;
typedef pair<pii,pii> ppp;
typedef vector< pii > vp;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, 
             tree_order_statistics_node_update> baap;

template<typename T> 
void swap(T &a,T &b)
{ auto tm=a; a=b; b=tm; }

template<typename T> 
void mina(T& a, T b) { 
    a = min(a, b); 
}
template<typename T>
void maxa(T& a, T b) { 
    a = max(a, b); 
}

  const int mod=1000000007;
  const int mod2=998244353;
  const int INF=1e18;
  const int N=1e5+15;  
  const int M=1e5+1;           
  
  pii see[4*N];
  int a[N];
  
  pii combine(pii p1,pii p2){

     if(p1.F==p2.F) return {p1.F,p1.S+p2.S};
     else {
        if(p1.F<p2.F) return p1;
        return p2;
     }
  }
    void build(int vx,int l,int r)
    {
      if(l==r)
       see[vx]={a[l],1};
      else
      {
        int mid=(l+r)>>1;
        build(2*vx,l,mid);
        build(2*vx+1,mid+1,r);
        see[vx]=combine(see[2*vx],see[2*vx+1]);
      }
    }
    
    pii qry(int vx,int l,int r,int ql,int qr)
    { 
      if(ql>qr) return {mod,1};
      if(l==ql&&r==qr) return see[vx];
      int mid=(l+r)>>1;
      return combine(qry(2*vx,l,mid,ql,min(qr,mid)),qry(2*vx+1,mid+1,r,max(mid+1,ql),qr));
    }
    
    void upd(int vx,int l,int r,int id,int val)
    {
      if(l==r) see[vx]={val,1};
      else
      {
        int mid=(l+r)>>1;
        if(id<=mid)
          upd(2*vx,l,mid,id,val);
        else  
          upd(2*vx+1,mid+1,r,id,val);
        see[vx]=combine(see[2*vx],see[2*vx+1]);
      }
    }

 void doit()
 {
   int n,m; cin>>n>>m;
   rep(i,1,n+1) cin>>a[i];
   build(1,1,n);

   while(m--){

      int t,x,y; cin>>t>>x>>y;

      if(t==1) upd(1,1,n,x+1,y);
      else { pii p=qry(1,1,n,x+1,y);
        cout<<p.F<<" "<<p.S<<nl;
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

  rep(i,1,tc+1)
  { // cout<<"Case #"<<i<<": ";
  
   doit();
   if(i<tc)
   cout<<nl;
  }
  
  #ifndef ONLINE_JUDGE
  cerr<<(1000*clock())/CLOCKS_PER_SEC<<"ms";
  #endif

 return 0; 
}
