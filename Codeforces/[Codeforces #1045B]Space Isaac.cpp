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

const int INF=1e9;
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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=1e6;

int n,m;
int a[MAXN+48],b[MAXN+48],len;
int RL[MAXN+48],maxright,pos;
vector<int> res;

inline void manacher()
{
	maxright=pos=0;
	for (register int i=1;i<=len;i++)
	{
		if (i>maxright) RL[i]=1; else RL[i]=min(maxright-i+1,RL[(pos<<1)-i]);
		while (i-RL[i]>=1 && i+RL[i]<=len && b[i+RL[i]]==b[i-RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);
	for (register int i=1;i<=n;i++) io.Get(a[i]),a[i+n]=a[i]+m;
	// for (register int i=1;i<=(n<<1);i++) cerr<<a[i]<<' ';
	// cerr<<endl;
	for (register int i=1;i<=(((n<<1)-1)<<1);i++) if (i&1) b[i]=-1; else b[i]=a[(i>>1)+1]-a[i>>1];
	b[(n<<2)-1]=-1;len=(n<<2)-1;
	// for (register int i=1;i<=len;i++) cerr<<b[i]<<' ';
	// cerr<<endl;
	manacher();
	for (register int i=(n+1);i<=(n+1)+n-1;i++)
		if (i-RL[i]+1==1) res.pb((a[i-n]+a[1])%m);
	io.Print(int(res.size()),'\n');sort(res.begin(),res.end());
	for (auto x : res) io.Print(x,' ');
	io.Writechar('\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}