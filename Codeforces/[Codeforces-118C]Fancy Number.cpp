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
		for (;*s!='\0';Writechar(*s),s++);
	}
}io;

const int MAXN=1e4;

int n,k;

char s[MAXN+48],ans[MAXN+48],curs[MAXN+48];

inline int myabs(int x) {return x>=0?x:-x;}

struct node
{
	int id,val,type;
	node () {}
	inline node (int ii,int vv,int tt) {id=ii;val=vv;type=tt;}
	inline bool operator < (const node &other) const
	{
		if (val!=other.val) return val<other.val;
		if (type^other.type) return type;
		if (type) return id<other.id; else return id>other.id;
	}
}a[MAXN+48];

inline void gen(char ch)
{
	memcpy(curs+1,s+1,sizeof(s));
	for (register int i=1;i<=k;i++) curs[a[i].id]=ch;
}

inline bool cmp ()
{
	for (register int i=1;i<=n;i++)
	{
		if (ans[i]<curs[i]) return false;
		if (ans[i]>curs[i]) return true;
	}
	return false;
}

int main ()
{
	// freopen ("a.in","r",stdin);
	// freopen ("a.out","w",stdout);
	io.Get(n);io.Get(k);io.getstring(s+1);
	memcpy(ans+1,s+1,sizeof(s));
	int minn=INF,curans;
	for (register int num=0;num<=9;num++)
	{
		curans=0;
		for (register int i=1;i<=n;i++) a[i]=node(i,myabs(num-(s[i]-'0')),(s[i]-'0')>num);
		sort(a+1,a+n+1);
		for (register int i=1;i<=k;i++) curans+=a[i].val;
		gen('0'+num);
		if (curans<minn || (curans==minn && cmp())) minn=curans,memcpy(ans+1,curs+1,sizeof(curs));
	}
	io.Print(minn,'\n');
	io.printstring(ans+1);io.Writechar('\n');
	io.flush();return 0;
}