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

const int INF=1e9;
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

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int Dx[]={-1,-1,-1,0,1,1,1,0},Dy[]={-1,0,1,1,1,0,-1,-1};

class Block3Checkers
{
	int Map[48][48],n,N;
	int type[48][48],tot;
	int ga[448][448],dist[448][448],val[448];
	inline int getind(int x,int y) {return (x-1)*n+y;}
	inline void addedge(int x,int y) {ga[x][y]=ga[y][x]=1;}
	inline void dfs(int x,int y,int col)
	{
		type[x][y]=col;addedge(getind(x,y),n*n+col);
		rep(dir,0,3)
		{
			int xx=x+dx[dir],yy=y+dy[dir];
			if ((1<=xx && xx<=n && 1<=yy && yy<=n) && (xx==1 || xx==n || yy==1 || yy==n) && Map[xx][yy]!=2 && !type[xx][yy]) dfs(xx,yy,col);
		}
	}
	inline void doit_border()
	{
		memset(type,0,sizeof(type));tot=0;
		rep(i,1,n) rep(j,1,n) if ((i==1 || i==n || j==1 || j==n) && !type[i][j] && Map[i][j]!=2) dfs(i,j,++tot);
	}
	public:
		inline int blockThem(vector<string> board)
		{
			n=int(board.size());N=n*n+3;
			memset(ga,0,sizeof(ga));
			rep(i,1,n) rep(j,1,n) Map[i][j]=((board[i-1][j-1]=='.')?1:(board[i-1][j-1]=='A'?2:0));
			doit_border();
			rep(i,1,n) rep(j,1,n)
				if (Map[i][j]!=2)
					rep(dir,0,7)
					{
						int xx=i+Dx[dir],yy=j+Dy[dir];
						if (1<=xx && xx<=n && 1<=yy && yy<=n && Map[xx][yy]!=2) addedge(getind(i,j),getind(xx,yy));
					}
			rep(i,1,n) rep(j,1,n) val[getind(i,j)]=Map[i][j];
			rep(i,N-2,N) val[i]=0;
			rep(i,1,N) rep(j,1,N) dist[i][j]=INF;
			rep(i,1,N) rep(j,1,N) if (ga[i][j]) dist[i][j]=val[i]+val[j];
			rep(i,1,N) dist[i][i]=val[i];
			rep(k,1,N) rep(i,1,N) rep(j,1,N) check_min(dist[i][j],dist[i][k]+dist[k][j]-val[k]);
			int ans=min(dist[N-2][N-1]+dist[N-2][N],100);
			check_min(ans,dist[N-1][N-2]+dist[N-1][N]);
			check_min(ans,dist[N][N-2]+dist[N][N-1]);
			rep(i,1,n) rep(j,1,n) if (Map[i][j]!=2) {int id=getind(i,j);check_min(ans,dist[id][N-2]+dist[id][N-1]+dist[id][N]-val[id]*2);}
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
	int nn;string s;vector<string> ss;
	Block3Checkers A;
	while (cin>>nn)
	{
		ss.clear();
		while (nn--) cin>>s,ss.pb(s);
		cout<<A.blockThem(ss)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
