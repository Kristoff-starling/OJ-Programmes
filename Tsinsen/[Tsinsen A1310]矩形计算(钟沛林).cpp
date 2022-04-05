#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
//#define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=18;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

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

const int MAXN=200;
const int MAXQ=1e5;

int n,m,q;
int a[MAXN+48][MAXN+48];

int val[MAXN*MAXN+48],tot;
int cnt[MAXN*MAXN+48],sum[MAXN+1][MAXN+1];

inline int query(int X1,int Y1,int X2,int Y2) {return sum[X2][Y2]-sum[X2][Y1-1]-sum[X1-1][Y2]+sum[X1-1][Y1-1];}

int X1[MAXQ+48],Y1[MAXQ+48],X2[MAXQ+48],Y2[MAXQ+48];
int ans[MAXQ+48];

int head[MAXN*MAXN+48],tx[MAXN*MAXN+48],ty[MAXN*MAXN+48],nxt[MAXN*MAXN+48],t;
inline void add(int pos,int x,int y) {++t;tx[t]=x;ty[t]=y;nxt[t]=head[pos];head[pos]=t;}

namespace BIT
{
	int c[MAXN+48][MAXN+48][MAXN+48];
	inline void modify(int x,int y,int z)
	{
		int yy=y,zz=z;
		while (x)
		{
			y=yy;
			while (y<=n)
			{
				z=zz;
				while (z<=m)
				{
					c[x][y][z]++;
					z+=LOWBIT(z);
				}
				y+=LOWBIT(y);
			}
			x^=LOWBIT(x);
		}
	}
	inline int query(int x,int y,int z)
	{
		int res=0,yy=y,zz=z;
		while (x<=m)
		{
			y=yy;
			while (y)
			{
				z=zz;
				while (z)
				{
					res+=c[x][y][z];
					z^=LOWBIT(z);
				}
				y^=LOWBIT(y);
			}
			x+=LOWBIT(x);
		}
		return res;
	}
}

struct element
{
	int X1,Y1,X2,Y2,ind;
	element () {}
	inline element(int _X1,int _Y1,int _X2,int _Y2,int _i)
	{
		ind=_i;
		X1=min(_X1,_X2);X2=max(_X1,_X2);
		Y1=min(_Y1,_Y2);Y2=max(_Y1,_Y2);
	}
	inline void print()
	{
		cerr<<X1<<' '<<Y1<<' '<<X2<<' '<<Y2<<endl;
	}
	inline bool operator < (const element &other) const
	{
		if (X1!=other.X1) return X1>other.X1;
		return ind<other.ind;
	}
}ele[3000048];int etot;

int cx[MAXN*MAXN+48],cy[MAXN*MAXN+48],ctot;

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%d%d",&n,&m);tot=0;
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			scanf("%d",&a[i][j]),val[++tot]=a[i][j];
	sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			a[i][j]=lower_bound(val+1,val+tot+1,a[i][j])-val,cnt[a[i][j]]++,add(a[i][j],i,j);
	scanf("%d",&q);
	for (register int i=1;i<=q;i++)
	{
		int x,y,xx,yy;
		scanf("%d%d%d%d",&x,&y,&xx,&yy);
		X1[i]=min(x,xx);X2[i]=max(x,xx);
		Y1[i]=min(y,yy);Y2[i]=max(y,yy);
	}
	for (register int k=1;k<=tot;k++)
		if (cnt[k]>=magic)
		{
			memset(sum,0,sizeof(sum));
			for (register int i=head[k];i;i=nxt[i]) sum[tx[i]][ty[i]]=1;
			for (register int i=1;i<=n;i++)
				for (register int j=2;j<=m;j++)
					sum[i][j]+=sum[i][j-1];
			for (register int i=2;i<=n;i++)
				for (register int j=1;j<=m;j++)
					sum[i][j]+=sum[i-1][j];
			for (register int i=1;i<=q;i++)
			{
				int tmp=query(X1[i],Y1[i],X2[i],Y2[i]);
				ans[i]+=tmp*tmp;
			}
		}
		else
		{
			ctot=0;
			for (register int i=head[k];i;i=nxt[i]) ++ctot,cx[ctot]=tx[i],cy[ctot]=ty[i];
			for (register int i=1;i<=ctot;i++)
				for (register int j=1;j<=ctot;j++)
					ele[++etot]=element(cx[i],cy[i],cx[j],cy[j],0);
		}
	for (register int i=1;i<=q;i++) ele[++etot]=element(X1[i],Y1[i],X2[i],Y2[i],i);
	sort(ele+1,ele+etot+1);
	for (register int i=1;i<=etot;i++)
	{
		if (!ele[i].ind) BIT::modify(ele[i].Y1,ele[i].X2,ele[i].Y2); else ans[ele[i].ind]+=BIT::query(ele[i].Y1,ele[i].X2,ele[i].Y2);
	}
	for (register int i=1;i<=q;i++) printf("%d\n",ans[i]);
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}

