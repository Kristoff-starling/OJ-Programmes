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
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=1e5;

int n,m,k;
int S1[MAXN+48],X1[MAXN+48][6];
int S2[MAXN+48],X2[MAXN+48][6];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i,j,Mask,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(k);
		for (i=1;i<=n;i++)
		{
			io.Get(S1[i]);
			for (j=1;j<=k;j++) io.Get(X1[i][j]);
		}
		for (i=1;i<=m;i++)
		{
			io.Get(S2[i]);
			for (j=1;j<=k;j++) io.Get(X2[i][j]);
		}
		LL ans=0,curans1,curans2,cur;
		for (Mask=0;Mask<=(1<<k)-1;Mask++)
		{
			curans1=-LINF;
			for (i=1;i<=n;i++)
			{
				cur=S1[i];
				for (j=1;j<=k;j++) if (Mask&(1<<(j-1))) cur+=X1[i][j]; else cur-=X1[i][j];
				curans1=max(curans1,cur);
			}
			curans2=-LINF;
			for (i=1;i<=m;i++)
			{
				cur=S2[i];
				for (j=1;j<=k;j++) if (Mask&(1<<(j-1))) cur-=X2[i][j]; else cur+=X2[i][j];
				curans2=max(curans2,cur);
			}
			ans=max(ans,curans1+curans2);
		}
		io.Print(ans,'\n');
	}
	io.flush();return 0;
}

