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

const int MAXN=2000;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n,m,k;
char a[MAXN+48][MAXN+48];
int Left[MAXN+48][MAXN+48],bel[MAXN+48][MAXN+48];
int Right[MAXN+48][MAXN+48];
vector<Pair> v[MAXN+48];
int T[MAXN+48];

int dp1[MAXN+48][MAXN+48],dp2[MAXN+48][MAXN+48],sum[MAXN+48][MAXN+48];

inline int query(int i,int l,int r)
{
	int res=0;
	int bl=bel[i][l],br=bel[i][r];
	if (bl!=br)
	{
		if (bl+1<br) res=sub(sum[i][br-1]-sum[i][bl]);
		res=add(res+dp2[i][l]);res=add(res+dp1[i][r]);
		return res;
	}
	if (i==1) return 1; else return query(i-1,max(l-k,1),min(r+k,m));
	return res;
}

int main ()
{
	int i,j,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(k);
		for (i=1;i<=n;i++)
		{
			io.getstring(a[i]+1);
			v[i].clear();v[i].resize(m+10);
			Left[i][1]=1;v[i][1].x=1;T[i]=1;bel[i][1]=1;
			for (j=2;j<=m;j++)
			{
				if (a[i][j]!=a[i][j-1]) v[i][T[i]].y=j-1,++T[i],v[i][T[i]].x=i,Left[i][j]=j;
				else Left[i][j]=Left[i][j-1];
				bel[i][j]=T[i];
			}
			v[i][T[i]].y=m;
			Right[i][m]=m;
			for (j=m-1;j>=1;j--) Right[i][j]=(a[i][j]==a[i][j+1]?Right[i][j+1]:j);
		}
		for (i=1;i<=m;i++) dp1[1][i]=dp2[1][i]=1;
		for (i=1;i<=T[1];i++) sum[1][i]=i;
		for (i=2;i<=n;i++)
		{
			sum[i][0]=0;
			for (j=1;j<=m;j++)
			{
				int l=Left[i][j],r=j;
				l=max(1,l-k);r=min(m,r+k);
				dp1[i][j]=query(i-1,l,r);
				l=j;r=Right[i][j];
				l=max(1,l-k);r=min(m,r+k);
				dp2[i][j]=query(i-1,l,r);
				if (v[i][bel[i][j]].y==j) sum[i][bel[i][j]]=add(sum[i][bel[i][j]-1]+dp1[i][j]);
			}
		}
		io.Print(sum[n][T[n]]);
	}
	io.flush();return 0;
}
