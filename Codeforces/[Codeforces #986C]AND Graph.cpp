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

const int MAXN=1e7;

int n,m;
bool visited[MAXN+48];int lim;
bool exist[MAXN+48];

inline void dfs(int cur)
{
	visited[cur]=true;
	if (cur<=lim)
	{
		if (!visited[(cur^lim)+lim+1]) dfs((cur^lim)+lim+1);
		return;
	}
	int tmp=cur-lim-1,tt=tmp;
	if (exist[tmp] && !visited[tmp]) dfs(tmp);
	while (tt)
	{
		if (!visited[(tmp^LOWBIT(tt))+lim+1]) dfs((tmp^LOWBIT(tt))+lim+1);
		tt^=LOWBIT(tt);
	}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double t=clock();
	cerr<<"Running..."<<endl;
#endif
	io.Get(m);io.Get(n);int ans=0;
	lim=1;for (register int i=1;i<=m;i++) lim<<=1;lim--;
	for (register int i=1;i<=n;i++)
	{
		register int x;io.Get(x);exist[x]=true;
		//if (!visited[x]) ans++,dfs(x);
	}
	for (register int i=0;i<=lim;i++)
		if (exist[i] && !visited[i])
		{
			ans++;
			dfs(i);
			cerr<<endl;
		}
	io.Print(ans,'\n');io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}