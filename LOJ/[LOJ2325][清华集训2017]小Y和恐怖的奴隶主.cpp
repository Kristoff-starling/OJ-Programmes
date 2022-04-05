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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch=='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

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

int T,m,k;LL n;

struct State
{
	int num1,num2,num3;
	State () {}
	inline State(int _n1,int _n2,int _n3) {num1=_n1;num2=_n2;num3=_n3;}
}toState[248];

int toind[10][10][10],tot=0;

struct Matrix
{
	int b[188][188];
	inline void clear() {for (register int i=1;i<=tot;i++) for (register int j=1;j<=tot;j++) b[i][j]=0;}
	inline void init_I() {clear();for (register int i=1;i<=tot;i++) b[i][i]=1;}
	inline Matrix operator + (Matrix other)
	{
		Matrix res;
		for (register int i=1;i<=tot;i++)
			for (register int j=1;j<=tot;j++)
				res.b[i][j]=add(b[i][j]+other.b[i][j]);
		return res;
	}
	inline Matrix operator * (Matrix other)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=tot;i++)
			for (register int j=1;j<=tot;j++)
				for (register int k=1;k<=tot;k++)
					Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%MOD);
		return res;
	}
}trans,Trans[100];
LL pw[100];

struct Vector
{
	int b[170];
	inline void clear() {for (register int i=1;i<=tot;i++) b[i]=0;}
	inline Vector operator * (Matrix other)
	{
		Vector res;res.clear();
		for (register int j=1;j<=tot;j++)
			for (register int k=1;k<=tot;k++)
				Add(res.b[j],1ll*b[k]*other.b[k][j]%MOD);
		return res;
	}
}sta;

inline void init()
{
	for (register int i=0;i<=k;i++)
		for (register int j=0;j<=k-i;j++)
			for (register int p=0;p<=k-i-j;p++)
			{
				if (m<3 && i) continue;
				if (m<2 && j) continue;
				toind[i][j][p]=++tot;toState[tot]=State(i,j,p);
			}
	++tot; //for the constant 1
	trans.clear();
	for (register int i=0;i<=k;i++)
		for (register int j=0;j<=k-i;j++)
			for (register int p=0;p<=k-i-j;p++)
			{
				if (m<3 && i) continue;
				if (m<2 && j) continue;
				int inv=quick_pow(i+j+p+1,MOD-2),ind=toind[i][j][p],toi,toj,top;
				//attack boss
				trans.b[ind][ind]=inv;
				trans.b[tot][ind]=inv;
				//attack 3
				if (m>=3 && i)
				{
					toi=i-1;toj=j+1;top=p;if (toi+toj+top<k) toi++;
					trans.b[toind[toi][toj][top]][ind]=1ll*i*inv%MOD;
				}
				//attack 2
				if (m>=2 && j)
				{
					toi=i;toj=j-1;top=p+1;if (toi+toj+top<k) (m==3)?toi++:toj++;
					trans.b[toind[toi][toj][top]][ind]=1ll*j*inv%MOD;
				}
				//attack 1
				if (p)
				{
					toi=i;toj=j;top=p-1;
					trans.b[toind[toi][toj][top]][ind]=1ll*p*inv%MOD;
				}
			}
	trans.b[tot][tot]=1;
	Trans[0]=trans;
	for (register int i=1;i<=60;i++) Trans[i]=Trans[i-1]*Trans[i-1];
	pw[0]=1;for (register int i=1;i<=60;i++) pw[i]=pw[i-1]+pw[i-1];
}

inline Vector Quick_pow(LL n)
{
	Vector res;res.clear();res.b[tot]=1;
	for (register int i=60;i>=0;i--)
		if (n>=pw[i]) res=res*Trans[i],n-=pw[i];
	return res;
}

map<LL,int> Mp;

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(T);Get(m);Get(k);
	init();LL lastn=-1;int lastans;
	while (T--)
	{
		Get(n);
		if (Mp.find(n)!=Mp.end()) {printf("%d\n",Mp[n]);continue;}
		Vector res=Quick_pow(n);
		int ind=((m==1)?toind[0][0][1]:((m==2)?toind[0][1][0]:toind[1][0][0]));
		printf("%d\n",res.b[ind]);
		Mp[n]=res.b[ind];
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
