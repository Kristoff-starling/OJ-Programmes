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

const int MAXN=2e5;

int n,m;

struct node
{
	int A,B,C;
	inline void input() {io.Get(A);io.Get(B);io.Get(C);}
}a[MAXN+48];

inline Pair query(int id,int ti)
{
	if (ti==1) return mp(a[id].A,a[id].B);
	if ((a[id].A+1)%n==a[id].B && !(ti&1)) return mp(0,0);
	if (ti&1)
	{
		Pair res=mp(a[id].B+ti/2-1,a[id].B+ti/2);
		res.x%=n;res.y%=n;
		return res;
	}
	else
	{
		Pair res=mp(a[id].A+ti/2-1,a[id].A+ti/2);
		res.x%=n;res.y%=n;
		return res;
	}
}

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=0;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

priority_queue<pair<int,pair<Pair,bool> > > q;

int main ()
{
	io.Get(n);io.Get(m);
	for (register int i=1;i<=m;i++)
	{
		a[i].input();
		q.push(mp(-a[i].C,mp(mp(a[i].A,a[i].B),false)));
		if (a[i].A+1!=a[i].B) q.push(mp(-a[i].C-1,mp(mp(a[i].A,(a[i].A+1)%n),true)));
		q.push(mp(-a[i].C-2,mp(mp(a[i].B,(a[i].B+1)%n),true)));
	}
	LL ans=0;DSU::init();
	for (register int cnt=0;cnt<n-1;)
	{
		int len=q.top().x;Pair res=q.top().y.x;bool type=q.top().y.y;q.pop();
		if (DSU::issame(res.x,res.y)) continue;
		cnt++;ans-=len;
		DSU::update(res.x,res.y);
		if (type)
		{
			res.x=(res.x+1)%n;res.y=(res.y+1)%n;
			len-=2;
			q.push(mp(len,mp(res,type)));
		}
	}
	io.Print(ans,'\n');
	io.flush();return 0;
}