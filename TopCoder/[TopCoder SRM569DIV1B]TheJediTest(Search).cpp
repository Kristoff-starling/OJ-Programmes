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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

class TheJediTest
{
	int a[48],n,ans=INF,k;
	inline int calc(int x) {return x%k==0?x/k:x/k+1;}
	inline void dfs(int cur,int delta,int curans)
	{
		if (cur==n+1) {check_min(ans,curans);return;}
		int val=a[cur]+delta;
		//throw it to the next
		if (cur<n)
		{
			int ndelta=min(val%k,a[cur]);
			dfs(cur+1,ndelta,curans+calc(val-ndelta));
		}
		//get from the next
		if (cur<n && val%k)
		{
			int ndelta=min(k-val%k,a[cur+1]);
			dfs(cur+1,-ndelta,curans+val/k+1);
		}
		if (cur==n) dfs(cur+1,0,curans+calc(val));
	}
	public:
		inline int minimumSupervisors(vector<int> students,int K)
		{
			n=int(students.size());k=K;
			for (register int i=1;i<=n;i++) a[i]=students[i-1];
			ans=INF;dfs(1,0,0);
			return ans;
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	int nn,kk;vector<int> aa;
	TheJediTest A;
	while (cin>>nn>>kk)
	{
		aa.clear();
		int x;
		for (register int i=1;i<=nn;i++) cin>>x,aa.pb(x);
		cout<<A.minimumSupervisors(aa,kk)<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif