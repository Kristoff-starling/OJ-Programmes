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

vector<int> d[MAXN+48];
inline void init_divisor()
{
	for (register int i=1;i<=MAXN;i++)
		for (register int j=i;j<=MAXN;j+=i)
			d[j].pb(i);
}

int n;

int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],tot;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
}

int val[MAXN+48];
int root[MAXN+48],ans[MAXN+48];

namespace SegmentTree
{
	const int MAXM=8e7;
	int lson[MAXM+48],rson[MAXM+48],tot=0;
	inline void insert(int &cur,int pos,int l,int r)
	{
		if (!cur) cur=++tot;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) insert(lson[cur],pos,l,mid); else insert(rson[cur],pos,mid+1,r);
	}
	inline int merge(int root1,int root2,int l,int r,int ind)
	{
		if (!root1 || !root2) return root1^root2;
		if (l==r) ans[ind]=max(ans[ind],l);
		int mid=(l+r)>>1;
		lson[root1]=merge(lson[root1],lson[root2],l,mid,ind);
		rson[root1]=merge(rson[root1],rson[root2],mid+1,r,ind);
		return root1;
	}
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i,j,x;io.Get(n);init_divisor();
	for (i=2;i<=n;i++) io.Get(x),addedge(x,i);
	for (i=1;i<=n;i++)
	{
		io.Get(val[i]);
		for (auto D : d[val[i]]) SegmentTree::insert(root[i],D,1,MAXN);
	}
	for (i=n;i>=1;i--)
	{
		ans[i]=-1;
		for (j=head[i];j;j=nxt[j])
			root[i]=SegmentTree::merge(root[i],root[to[j]],1,MAXN,i);
	}
	for (i=1;i<=n;i++) io.Print(ans[i],'\n');
	io.flush();return 0;
}
