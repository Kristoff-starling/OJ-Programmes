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
#define LOWBIT(x) x & (-x)
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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=3e4;

int n,d;
int cnt[MAXN+48],mul[MAXN+48];

inline int toval(int x,int y) {return mul[x]+y;}

struct Hash
{
	const int hashmod=15260827;
	static const int MAXS=16000000;
	int head[MAXS+48],to[MAXS+48],nxt[MAXS+48],tot;short f[MAXS+48];
	Hash () {tot=1;}
	inline void insert(int pos,int vv)
	{
		int pp=pos%hashmod;
		to[++tot]=pos;nxt[tot]=head[pp];head[pp]=tot;f[tot]=vv;
		assert(tot<=MAXS);
	}
	inline int query(int pos)
	{
		int pp=pos%hashmod;
		for (register int i=head[pp];i;i=nxt[i])
			if (to[i]==pos) return f[i];
		return -1;
	}
}h;

inline int solve(int cur,int curd)
{
	int res=h.query(toval(cur,curd));
	if (res!=-1) return res;
	int vv=cnt[cur],maxn=vv;
	if (cur+curd<=MAXN) maxn=max(maxn,vv+solve(cur+curd,curd));
	if (cur && curd>1 && cur+curd-1<=MAXN) maxn=max(maxn,vv+solve(cur+curd-1,curd-1));
	if (cur && cur+curd+1<=MAXN) maxn=max(maxn,vv+solve(cur+curd+1,curd+1));
	h.insert(toval(cur,curd),maxn);
	return maxn;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(d);
	for (register int i=1;i<=n;i++)
	{
		register int x;io.Get(x);
		cnt[x]++;
	}
	for (register int i=1;i<=MAXN;i++) mul[i]=i*(MAXN+1);
	io.Print(solve(0,d),'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}