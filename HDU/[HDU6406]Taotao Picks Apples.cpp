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

const int MAXN=1e5;

int n,m;
int a[MAXN+48];

int maxn[MAXN+48][21],Log[MAXN+48];

inline void construct_ST()
{
	int i,j;
	for (i=1;i<=n;i++) maxn[i][0]=a[i];
	for (j=1;j<=20;j++)
		for (i=1;i<=n;i++)
		{
			maxn[i][j]=maxn[i][j-1];
			if (i+(1<<(j-1))<=n) maxn[i][j]=max(maxn[i][j],maxn[i+(1<<(j-1))][j-1]);
		}
	Log[0]=Log[1]=0;
	for (i=2;i<=MAXN;i++) Log[i]=Log[i>>1]+1;
}

inline int query_ST(int l,int r)
{
	int k=r-l+1;
	return max(maxn[l][Log[k]],maxn[r-(1<<Log[k])+1][Log[k]]);
}

inline int find(int pos,int cmp)
{
	int l=pos,r=n,mid,res=-1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (query_ST(pos,mid)>cmp) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

int dp[MAXN+48];
inline void init_dp()
{
	for (register int i=n;i>=1;i--)
	{
		dp[i]=1;
		int res=find(i+1,a[i]);
		if (res!=-1) dp[i]+=dp[res];
	}
}

int seq[MAXN+48],tot;
inline int bsearch(int cmp)
{
	int l=1,r=tot,res=0,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (seq[mid]>=cmp) r=mid-1; else res=mid,l=mid+1;
	}
	return res;
}

int main ()
{
	int ca;io.Get(ca);int i,pos,nv;
	while (ca--)
	{
		io.Get(n);io.Get(m);
		for (i=1;i<=n;i++) io.Get(a[i]);
		construct_ST();init_dp();tot=0;
		seq[++tot]=1;
		for (i=2;i<=n;i++) if (a[i]>a[seq[tot]]) seq[++tot]=i;
		while (m--)
		{
			io.Get(pos);io.Get(nv);
			int pp=bsearch(pos),ans=pp;
			if (!pp || a[seq[pp]]<nv)
			{
				ans++;
				int res=find(pos+1,nv);
				if (res!=-1) ans+=dp[res];
			}
			else
			{
				int res=find(pos+1,a[seq[pp]]);
				if (res!=-1) ans+=dp[res];
			}
			io.Print(ans);
		}
	}
	io.flush();return 0;
}
