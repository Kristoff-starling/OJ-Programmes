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
#define REP(i,l,r) for (register int i=int(r);i>=int(l);i--)

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

const int Wall=1,Empty=0;
const int MAXN=2000;

int grid[MAXN+48][MAXN+48],Map[MAXN+48][MAXN+48];
int sx,sy,ex,ey;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int dp[MAXN+48][MAXN+48][4];
deque<int> q;

class EnergyGameOnGrid
{
	inline void gen(int N,int M,vector<int> p,int r1,int c1,int r2,int c2)
	{
		int i,j,k;
		LL x = N + 2 * M + 3 * r1 + 4 * c1 + 5 * r2 + 6 * c2;
		for(i = 0; i < N; i++){
			for(j = 0; j < M; j++){
				grid[i][j] = Empty;
			}
		}
		for(i = 0; i < int(p.size()); i += 5){
			for(j = p[i]; j <= p[i + 2]; j++){
				for(k = p[i + 1]; k <= p[i + 3]; k++){
					x = (x * 1103515245 + 12345) % (LL)2147483648;
					if(x < p[i + 4]){
						grid[j][k] = Wall;
					} else {
						grid[j][k] = Empty;
					}
				}
			}
		}
		grid[r1][c1] = Empty;
		grid[r2][c2] = Empty;
		rep(i,1,N) rep(j,1,M) Map[i][j]=grid[i-1][j-1];
	}
	inline void Push_back(int x,int y,int dir) {q.pb(x);q.pb(y);q.pb(dir);}
	inline void Push_front(int x,int y,int dir) {q.pf(dir);q.pf(y);q.pf(x);}
	public:
		inline string isReachable(int N,int M,vector<int> p,int r1,int c1,int r2,int c2,int E)
		{
			gen(N,M,p,r1,c1,r2,c2);
			sx=r2;sy=c2;ex=r1;ey=c1;sx++;sy++;ex++;ey++;
			rep(i,1,N) rep(j,1,M) rep(dir,0,3) dp[i][j][dir]=INF;
			rep(dir,0,3) dp[sx][sy][dir]=0,Push_back(sx,sy,dir);
			int cx,cy,cdir,tox,toy,step;
			while (!q.empty())
			{
				cx=q.front();q.pop_front();cy=q.front();q.pop_front();cdir=q.front();q.pop_front();
				step=dp[cx][cy][cdir];
				if (!Map[cx][cy])
				{
					rep(dir,0,3)
					{
						tox=cx+dx[dir]*step;toy=cy+dy[dir]*step;
						if (1<=tox && tox<=N && 1<=toy && toy<=M && step<dp[tox][toy][dir])
						{
							dp[tox][toy][dir]=step;
							Push_front(tox,toy,dir);
						}
					}
				}
				tox=cx+dx[cdir];toy=cy+dy[cdir];
				if (1<=tox && tox<=N && 1<=toy && toy<=M && step+1<dp[tox][toy][cdir])
				{
					dp[tox][toy][cdir]=step+1;
					Push_back(tox,toy,cdir);
				}
			}
			rep(dir,0,3) if (dp[ex][ey][dir]<=E) return "Possible";
			return "Impossible";
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
	int nn,mm,r1,c1,r2,c2,e;
	vector<int> P;int x;
	EnergyGameOnGrid A;
	while (cin>>nn>>mm>>r1>>c1>>r2>>c2>>e)
	{
		int num;cin>>num;P.clear();
		while (num--) cin>>x,P.pb(x);
		cout<<A.isReachable(nn,mm,P,r1,c1,r2,c2,e)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
