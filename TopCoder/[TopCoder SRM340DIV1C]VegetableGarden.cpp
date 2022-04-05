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
    template <class T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:-res);
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
    template <class T> inline void Print(T x,char ch)
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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int q[5000048],head,tail;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int a[148][148],under[148][148],dp[58][58][1048];

class VegetableGarden
{
	int n,m;
	public:
		inline vector<int> getMinDistances(vector<string> Garden)
		{
			n=int(Garden.size());m=int(Garden[0].size());
			int cntcare=0,cntwant=0,taboo=0;
			for (register int i=0;i<n;i++)
				for (register int j=0;j<=m;j++)
				{
					a[i+1][j+1]=0;
					if (Garden[i][j]=='I') ++cntwant,a[i+1][j+1]=++cntcare;
					if (Garden[i][j]=='X') a[i+1][j+1]=++cntcare,taboo|=(1<<(cntcare-1));
				}
			for (register int j=1;j<=m;j++)
			{
				under[n+1][j]=0;
				for (register int i=n;i>=1;i--)
				{
					under[i][j]=under[i+1][j];
					if (a[i][j]) under[i][j]|=(1<<(a[i][j]-1));
				}
			}
			for (register int i=1;i<=n+1;i++)
				for (register int j=1;j<=m+1;j++)
					for (register int Mask=0;Mask<=(1<<cntcare)-1;Mask++)
						dp[i][j][Mask]=INF;
			dp[1][1][0]=0;head=1;tail=0;q[++tail]=1;q[++tail]=1;q[++tail]=0;
			while (head<=tail)
			{
				int x=q[head++],y=q[head++],Mask=q[head++],nx,ny,nMask;
				for (register int dir=0;dir<=3;dir++)
				{
					nx=x+dx[dir];ny=y+dy[dir];nMask=Mask;
					if (1<=nx && nx<=n+1 && 1<=ny && ny<=m+1)
					{
						if (dy[dir]==1) nMask^=under[x][y];
						if (dy[dir]==-1) nMask^=under[nx][ny];
						if (dp[x][y][Mask]+1<dp[nx][ny][nMask])
						{
							dp[nx][ny][nMask]=dp[x][y][Mask]+1;
							q[++tail]=nx;q[++tail]=ny;q[++tail]=nMask;
						}
					}
				}
			}
			vector<int> res(cntwant,INF);
			for (register int Mask=1;Mask<=(1<<cntcare)-1;Mask++)
				if (!(Mask&taboo)) check_min(res[__builtin_popcount(Mask)-1],dp[1][1][Mask]);
			return res;
		}
};

/* ---Debug Part--- */
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;string ss;vector<string> sss;
	VegetableGarden A;
	while (cin>>nn)
	{
		sss.clear();
		for (register int i=1;i<=nn;i++) cin>>ss,sss.pb(ss);
		vector<int> res=A.getMinDistances(sss);
		for (auto item : res) cout<<item<<' ';
		cout<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/

