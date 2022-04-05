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

int n,k;
set<Pair> s[48];
set<Pair>::iterator iter;

struct node
{
	int val[48];
	inline void input() {for (register int i=1;i<=k;i++) io.Get(val[i]);}
}a[MAXN+48];

namespace DSU
{
	int pre[MAXN+48],sz[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i,sz[i]=1;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;sz[y]+=sz[x];}
}

int head;
int nxt[MAXN+48];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	io.Get(n);io.Get(k);
	for (register int i=1;i<=n;i++) a[i].input();
	DSU::init();
	for (register int i=1;i<=n;i++)
	{
		int Pre=0,Nxt=0;
		for (register int j=1;j<=k;j++)
		{
			iter=s[j].upper_bound(mp(a[i].val[j],1));
			if (iter!=s[j].end())
			{
				int curpre=iter->y;
				if (!Pre || a[DSU::find_anc(Pre)].val[j]>a[DSU::find_anc(curpre)].val[j]) Pre=curpre;
			}
			if (iter!=s[j].begin())
			{
				--iter;
				int curnxt=iter->y;
				if (!Nxt || a[DSU::find_anc(Nxt)].val[j]<a[DSU::find_anc(curnxt)].val[j]) Nxt=curnxt;
			}
		}
		if (!Pre && !Nxt)
		{
			head=DSU::find_anc(i);
			nxt[head]=0;
		}
		else if (Pre && !Nxt)
		{
			nxt[DSU::find_anc(Pre)]=i;
			nxt[i]=0;
		}
		else if (!Pre && Nxt)
		{
			nxt[i]=head;
			head=i;
		}
		else if (DSU::find_anc(Pre)==DSU::find_anc(Nxt))
		{
			int nn=nxt[DSU::find_anc(Pre)];
			DSU::update(Pre,i);
			nxt[DSU::find_anc(i)]=nn;
		}
		else if (DSU::find_anc(nxt[DSU::find_anc(Pre)])==DSU::find_anc(Nxt))
		{
			nxt[DSU::find_anc(Pre)]=i;
			nxt[i]=DSU::find_anc(Nxt);
		}
		else
		{
			int nn=nxt[DSU::find_anc(Pre)];
			register int pt,cnt;
			for (pt=DSU::find_anc(Nxt);pt!=DSU::find_anc(Pre);pt=DSU::find_anc(nxt[pt]))
				DSU::update(pt,i);DSU::update(pt,i);
			nxt[DSU::find_anc(i)]=nn;
		}
		io.Print(DSU::sz[DSU::find_anc(head)],'\n');
		for (register int j=1;j<=k;j++) s[j].insert(mp(a[i].val[j],i));
	}
	io.flush();return 0;
}
