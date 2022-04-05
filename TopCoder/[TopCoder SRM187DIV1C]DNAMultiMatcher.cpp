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
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=2500;

struct Hash
{
	static const int hashmod=2333;
	int head[hashmod+48],nxt[10048],tot;ull to[10048];
	inline void init() {tot=0;memset(head,0,sizeof(head));}
	inline void insert(ull val)
	{
		int pos=val%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (to[i]==val) return;
		to[++tot]=val;nxt[tot]=head[pos];head[pos]=tot;
	}
	inline bool query(ull val)
	{
		int pos=val%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (to[i]==val) return true;
		return false;
	}
}h1,h2;

char s1[MAXN+48],s2[MAXN+48],s3[MAXN+48];
int len1,len2,len3;
inline void init_string(vector<string> A,vector<string> B,vector<string> C)
{
	int pt=0;
	for (register int i=0;i<int(A.size());i++)
		for (register int j=0;j<int(A[i].size());j++)
			s1[++pt]=A[i][j];
	len1=pt;pt=0;
	for (register int i=0;i<int(B.size());i++)
		for (register int j=0;j<int(B[i].size());j++)
			s2[++pt]=B[i][j];
	len2=pt;pt=0;
	for (register int i=0;i<int(C.size());i++)
		for (register int j=0;j<int(C[i].size());j++)
			s3[++pt]=C[i][j];
	len3=pt;
}

const int p=19260817;
ull hsh1[MAXN+48],hsh2[MAXN+48],hsh3[MAXN+48],pw[MAXN+48];
inline void init_hash()
{
	pw[0]=1;
	for (register int i=1;i<=MAXN;i++) pw[i]=pw[i-1]*p;
	hsh1[0]=0;
	for (register int i=1;i<=len1;i++) hsh1[i]=hsh1[i-1]*p+s1[i];
	hsh2[0]=0;
	for (register int i=1;i<=len2;i++) hsh2[i]=hsh2[i-1]*p+s2[i];
	hsh3[0]=0;
	for (register int i=1;i<=len3;i++) hsh3[i]=hsh3[i-1]*p+s3[i];
}

inline ull gethash1(int left,int right) {return hsh1[right]-hsh1[left-1]*pw[right-left+1];}
inline ull gethash2(int left,int right) {return hsh2[right]-hsh2[left-1]*pw[right-left+1];}
inline ull gethash3(int left,int right) {return hsh3[right]-hsh3[left-1]*pw[right-left+1];}

class DNAMultiMatcher
{
	public:
		inline int longestMatch(vector<string> A,vector<string> B,vector<string> C)
		{
			init_string(A,B,C);init_hash();
			int ans=0;
			for (register int i=min(min(len1,len2),len3);i>=1;i--)
			{
				h1.init();h2.init();
				for (register int j=1;j<=len1-i+1;j++) h1.insert(gethash1(j,j+i-1));
				for (register int j=1;j<=len2-i+1;j++)
				{
					ull cur=gethash2(j,j+i-1);
					if (h1.query(cur)) h2.insert(cur);
				}
				bool f=false;
				for (register int j=1;j<=len3-i+1;j++)
					if (h2.query(gethash3(j,j+i-1))) {f=true;break;}
				if (f) {ans=i;break;}
			}
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
	int aa,bb,cc;
	vector<string> AA,BB,CC;
	DNAMultiMatcher A;
	while (cin>>aa>>bb>>cc)
	{
		AA.clear();BB.clear();CC.clear();
		string s;
		for (register int i=1;i<=aa;i++) cin>>s,AA.pb(s);
		for (register int i=1;i<=bb;i++) cin>>s,BB.pb(s);
		for (register int i=1;i<=cc;i++) cin>>s,CC.pb(s);
		cout<<A.longestMatch(AA,BB,CC);
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif