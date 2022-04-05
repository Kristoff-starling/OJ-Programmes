#include <bits/stdc++.h>
#include <unordered_map> 
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
int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],tot=0;
inline int addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
}

int val[MAXN+48],ind[MAXN+48];
int ans[MAXN+48];
int sz[MAXN+48];

unordered_map<int,bool> Mp[MAXN+48];
unordered_map<int,bool>::iterator iter;

inline void Merge(int id1,int id2,int Id)
{
	id1=ind[id1];id2=ind[id2];
	for (iter=Mp[id2].begin();iter!=Mp[id2].end();iter++)
	{
		int res=iter->x;
		if (Mp[id1][res]) ans[Id]=max(ans[Id],res); else Mp[id1][res]=true,sz[id1]++;
	}
}

int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int i,j,x;
	io.Get(n);init_divisor();
	for (i=2;i<=n;i++) io.Get(x),addedge(x,i);
	for (i=1;i<=n;i++)
	{
		io.Get(val[i]);
		for (auto D : d[val[i]]) Mp[i][D]=true,sz[i]++;
		ind[i]=i;
	}
	for (i=n;i>=1;i--)
	{
		int maxn=sz[ind[i]],maxind=i;
		for (j=head[i];j;j=nxt[j])
			if (sz[ind[to[j]]]>maxn)
			{
				maxn=sz[ind[to[j]]];
				maxind=to[j];
			}
		ans[i]=-1;
		if (maxind!=i) Merge(maxind,i,i);
		for (j=head[i];j;j=nxt[j])
			if (to[j]!=maxind) Merge(maxind,to[j],i);
		ind[i]=ind[maxind];
	}
	for (i=1;i<=n;i++) io.Print(ans[i],'\n');	
	io.flush();return 0;
}
