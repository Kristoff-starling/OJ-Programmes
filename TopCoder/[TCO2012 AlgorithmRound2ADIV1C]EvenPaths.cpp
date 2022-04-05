// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

struct fastio
{
    static const int S=1e7;
    char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
    fastio() {rpos=len=wpos=0;}
    inline char Getchar()
    {
        if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
        if (!len) return EOF;
        return rbuf[rpos++];
    }
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
    inline void getstring(char *s)
    {
        char ch;
        while ((ch=Getchar())<=32) {}
        for (;ch>32;ch=Getchar()) *s++=ch;
        *s='\0';
    }
    inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
    inline void Writechar(char ch)
    {
        if (wpos==S) flush();
        wbuf[wpos++]=ch;
    }
    template<typename T> inline void Print(T x,char ch)
    {
        char s[20];int pt=0;
        if (x==0) s[++pt]='0';
        else
        {
            if (x<0) Writechar('-'),x=-x;
            while (x) s[++pt]='0'+x%10,x/=10;
        }
        while (pt) Writechar(s[pt--]);
        Writechar(ch);
    }
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
    inline void printstring(char *s)
    {
        int pt=1;
        while (s[pt]!='\0') Writechar(s[pt++]);
    }
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int ga[148][148],n;
vector<int> v[148],vv[148];int d[148];
int seq[148],tot,head,tail,q[148];

int spe[148],stot;
bool isleft[148],isright[148];
int id[148],lsz,rsz;

int dp[148];
LL cntA[600048],cntB[600048],res[600048];

namespace polynomial
{
	inline void poly_fwt(LL c[],int len,int fl)
	{
		for (register int clen=2;clen<=len;clen<<=1)
			for (register int j=0;j<len;j+=clen)
				for (register int k=j;k<(j+(clen>>1));k++)
					if (fl==1) c[k]+=c[k+(clen>>1)]; else c[k]-=c[k+(clen>>1)];
	}
	inline void poly_fwtmul(LL A[],LL B[],int N,int M,LL C[])
	{
		int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(LL));
		memset(B+M,0,(len-M)*sizeof(LL));
		poly_fwt(A,len,1);poly_fwt(B,len,1);
		for (register int i=0;i<len;i++) C[i]=A[i]*B[i];
		poly_fwt(C,len,-1);
	}
}

class EvenPaths
{
	public:
		inline LL theCount(vector<string> maze,string room)
		{
			n=int(maze.size());
			rep(i,1,n) d[i]=0,v[i].clear(),vv[i].clear();
			rep(i,1,n) rep(j,1,n) if (maze[i-1][j-1]=='Y') v[i].pb(j),vv[j].pb(i),d[j]++;
			head=1;tail=0;tot=stot=0;
			rep(i,1,n) if (!d[i]) q[++tail]=i;
			while (head<=tail)
			{
				int cur=q[head++];seq[++tot]=cur;
				if (room[cur-1]=='?') spe[++stot]=cur;
				rep(i,0,int(v[cur].size())-1)
				{
					int y=v[cur][i];
					d[y]--;if (!d[y]) q[++tail]=y;
				}
			}
			int mid=(stot>>1);
			rep(i,1,n) isleft[i]=isright[i]=false,id[i]=0;
			rep(i,1,mid) isleft[spe[i]]=true,id[spe[i]]=i;
			rep(i,mid+1,stot) isright[spe[i]]=true,id[spe[i]]=i-mid;
			lsz=mid;rsz=stot-mid;
			rep(Mask,0,(1<<(rsz+1))-1) cntA[Mask]=cntB[Mask]=0;
			rep(Mask,0,(1<<lsz)-1)
			{
				dp[1]=1;
				rep(i,1,n)
				{
					int cur=seq[i];if (cur==1) continue;dp[cur]=0;
					if (isleft[cur] && (Mask&(1<<(id[cur]-1)))) continue;
					rep(j,0,int(vv[cur].size())-1)
					{
						int pre=vv[cur][j];
						if (!isright[pre]) dp[cur]=(dp[cur]^dp[pre])&1;
					}
				}
				int bit=0;
				rep(i,mid+1,stot+1)
				{
					int cur=(i<=stot?spe[i]:2);
					bit|=((dp[cur]&1)<<(i-mid-1));
				}
				cntA[bit]++;
			}
			rep(Mask,0,(1<<rsz)-1)
			{
				dp[2]=1;
				REP(i,n,1)
				{
					int cur=seq[i];if (cur==2) continue;dp[cur]=0;
					if (isright[cur] && (Mask&(1<<(id[cur]-1)))) continue;
					if (isleft[cur]) continue;	
					rep(j,0,int(v[cur].size())-1)
					{
						int to=v[cur][j];
						dp[cur]=(dp[cur]^dp[to])&1;
					}
				}
				int bit=0;
				rep(i,mid+1,stot+1)
				{
					int cur=(i<=stot?spe[i]:2);
					bit|=((dp[cur]&1)<<(i-mid-1));
				}
				cntB[bit]++;
			}
			polynomial::poly_fwtmul(cntA,cntB,(1<<(rsz+1)),(1<<(rsz+1)),res);
			LL ans=0;
			rep(Mask,0,(1<<(rsz+1))-1) if (~__builtin_popcount(Mask)&1) ans+=res[Mask];
			return ans;
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;string s;vector<string> aa,bb;
	EvenPaths A;
	while (cin>>nn)
	{
		aa.clear();
		rep(i,1,nn) cin>>s,aa.pb(s);
		cin>>s;
		cout<<A.theCount(aa,s)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
