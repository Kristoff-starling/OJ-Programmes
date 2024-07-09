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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
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

const int MAXN=1000;
const int MAXK=1e6;

int n,m,k,p;
int a[MAXN+48][MAXN+48];
int rsum[MAXN+48],csum[MAXN+48];
priority_queue<LL> srow,scol;

LL maxrow[MAXK+48],maxcol[MAXK+48];

int main ()
{
	// freopen ("number.in","r",stdin);
	// freopen ("number.out","w",stdout);
#ifdef LOCAL
	double t=clock();
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);io.Get(k);io.Get(p);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			io.Get(a[i][j]),rsum[i]+=a[i][j],csum[j]+=a[i][j];
	for (register int i=1;i<=n;i++) srow.push(rsum[i]);
	for (register int i=1;i<=k;i++)
	{
		LL val=srow.top();srow.pop();
		maxrow[i]=maxrow[i-1]+val;
		val-=p*m;srow.push(val);
	}
	for (register int j=1;j<=m;j++) scol.push(csum[j]);
	for (register int i=1;i<=k;i++)
	{
		LL val=scol.top();scol.pop();
		maxcol[i]=maxcol[i-1]+val;
		val-=p*n;scol.push(val);
	}
	LL ans=-LINF;
	for (register int i=0;i<=k;i++) ans=max(ans,maxrow[i]+maxcol[k-i]-1ll*p*i*(k-i));
	io.Print(ans,'\n');
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	io.flush();return 0;
}