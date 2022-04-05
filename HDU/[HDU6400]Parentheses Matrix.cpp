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
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

int n,m;

char s[248][248];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca;io.Get(ca);int i,j;
	while (ca--)
	{
		io.Get(n);io.Get(m);
		if (n&1 && m&1)
		{
			for (i=1;i<=n;i++)
			{
				for (j=1;j<=m;j++)
					printf("(");
				printf("\n");
			}
			continue;
		}
		if (!(n&1) && !(m&1))
		{
			if (n>m)
			{
				if (m<=6)
				{
					for (i=1;i<=n;i++)
					{
						if (i&1)
							for (j=1;j<=m-1;j+=2) s[i][j]='(',s[i][j+1]=')';
						else
						{
							s[i][1]='(';
							for (j=2;j<=m-2;j+=2) s[i][j]='(',s[i][j+1]=')';
							s[i][m]=')';
						}
					}
				}
				else
				{
					for (j=1;j<=m;j++) s[1][j]='(';
					for (i=2;i<=n-1;i++)
					{
						if (i&1)
						{
							s[i][1]='(';
							for (j=2;j<=m-2;j+=2) s[i][j]='(',s[i][j+1]=')';
							s[i][m]=')';
						}
						else
							for (j=1;j<=m-1;j+=2) s[i][j]='(',s[i][j+1]=')';
					}
					for (j=1;j<=m;j++) s[n][j]=')';
				}
			}
			else
			{
				if (n<=6)
				{
					for (j=1;j<=m;j++)
					{
						if (j&1)
							for (i=1;i<=n-1;i+=2) s[i][j]='(',s[i+1][j]=')';
						else
						{
							s[1][j]='(';
							for (i=2;i<=n-2;i+=2) s[i][j]='(',s[i+1][j]=')';
							s[n][j]=')';
						}
					}
				}
				else
				{
					for (i=1;i<=n;i++) s[i][1]='(';
					for (j=2;j<=m-1;j++)
					{
						if (j&1)
						{
							s[1][j]='(';
							for (i=2;i<=n-2;i+=2) s[i][j]='(',s[i+1][j]=')';
							s[n][j]=')';
						}
						else
							for (i=1;i<=n-1;i+=2) s[i][j]='(',s[i+1][j]=')';
					}
					for (i=1;i<=n;i++) s[i][m]=')';
				}
			}
			for (i=1;i<=n;i++)
			{
				for (j=1;j<=m;j++)
					printf("%c",s[i][j]);
				printf("\n");
			}
			continue;
		}
		if (n&1)
		{
			for (i=1;i<=n;i++)
			{
				for (j=1;j<=m-1;j+=2) printf("()");
				printf("\n");
			}
		}
		else
		{
			for (i=1;i<=n;i++)
			{
				for (j=1;j<=m;j++)
					if (i&1) printf("("); else printf(")");
				printf("\n");
			}
		}
	}
	return 0;
}
