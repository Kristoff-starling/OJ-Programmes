#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
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

const int MAXN=50000;
const int BIT=100000000;
const int BITNUM=8;

struct Bigint
{
	int b[5],len;
	Bigint () {memset(b,0,sizeof(b));}
	inline bool iszero() {return len==1 && b[1]==0;}
	inline void Set(int x)
	{
		memset(b,0,sizeof(b));
		if (!x) {b[1]=0;len=1;return;}
		len=0;
		while (x) b[++len]=x%BIT,x/=BIT;
	}
	/*inline string trans()
	{
		string res;res="";
		for (register int i=len;i>=1;i--)
		{
			int nu=getw(b[i]);string tmp=INT_TO_STRING(b[i]);
			if (i!=len) for (register int j=1;j<=(3-nu);j++) tmp="0"+tmp;
			res+=tmp;
		}
		return res;
	}*/
	inline int getw(int x)
	{
		if (!x) return 1;
		int res=0;
		while (x) res++,x/=10;
		return res;
	}
	inline void print()
	{
		printf("%d",b[len]);
		for (register int i=len-1;i>=1;i--)
		{
			int nu=getw(b[i]);
			for (register int j=1;j<=BITNUM-nu;j++) printf("0");
			printf("%d",b[i]);
		}
		printf("\n");
	}
	inline bool operator < (Bigint other)
	{
		if (len<other.len) return true;
		if (len>other.len) return false;
		for (register int i=len;i>=1;i--)
		{
			if (b[i]<other.b[i]) return true;
			if (b[i]>other.b[i]) return false;
		}
		return false;
	}
	inline bool operator == (Bigint other)
	{
		if (len!=other.len) return false;
		for (register int i=1;i<=len;i++) if (b[i]!=other.b[i]) return false;
		return true;
	}
	inline bool operator > (Bigint other)
	{
		if (len<other.len) return false;
		if (len>other.len) return true;
		for (register int i=len;i>=1;i--)
		{
			if (b[i]>other.b[i]) return true;
			if (b[i]<other.b[i]) return false;
		}
		return false;
	}
	inline bool operator <= (Bigint other) {return *(this)<other || *(this)==other;}
	inline bool operator >= (Bigint other) {return *(this)>other || *(this)==other;}
	inline Bigint operator << (int num)
	{
		Bigint res;res=*(this);
		if (len==1 && !b[1]) return res;
		for (register int i=len;i>=1;i--) res.b[i+num]=res.b[i];
		res.len+=num;return res;
	}
	inline Bigint operator + (Bigint other)
	{
		Bigint res;res.Set(0);
		res.len=max(len,other.len);
		for (register int i=1;i<=res.len;i++)
		{
			res.b[i]+=b[i]+other.b[i];
			res.b[i+1]+=res.b[i]/BIT;
			res.b[i]%=BIT;
		}
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline Bigint operator - (Bigint other)
	{
		Bigint res;res.Set(0);
		for (register int i=1;i<=len;i++)
		{
			if (b[i]<other.b[i]) b[i]+=BIT,b[i+1]--;
			res.b[i]=b[i]-other.b[i];
		}
		res.len=len;
		while (res.len && res.b[res.len]==0) res.len--;
		if (!res.len) res.len=1;
		return res;
	}
	inline Bigint operator * (Bigint other)
	{
		Bigint res;res.Set(0);
		if ((len==1 && b[len]==0) || other.iszero()) return res;
		for (register int i=1;i<=len;i++)
			for (register int j=1;j<=other.len;j++)
				res.b[i+j-1]+=b[i]*other.b[j];
		res.len=len+other.len-1;
		for (register int i=1;i<=res.len;i++) res.b[i+1]+=res.b[i]/BIT,res.b[i]%=BIT;
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline int getbit(Bigint other)
	{
		Bigint tmp;int l=0,r=BIT-1,mid,ans;
		while (l<=r)
		{
			mid=(l+r)>>1;
			tmp.Set(mid);if (other*tmp<=*(this)) ans=mid,l=mid+1; else r=mid-1;
		}
		return ans;
	}
	inline Bigint operator / (Bigint other)
	{
		Bigint cur;cur.Set(0);Bigint res,tmp;
		res.len=len;
		for (register int i=len;i>=1;i--)
		{
			cur=(cur<<1);cur.b[1]=b[i];
			int w=cur.getbit(other);
			res.b[i]=w;tmp.Set(w);
			cur=cur-other*tmp;
		}
		while (!res.b[res.len]) res.len--;
		return res;
	}
	inline Bigint operator % (Bigint other)
	{
		Bigint cur;cur.Set(0);Bigint tmp;
		for (register int i=len;i>=1;i--)
		{
			cur=(cur<<1);cur.b[1]=b[i];
			int w=cur.getbit(other);
			tmp.Set(w);
			cur=cur-other*tmp;
		}
		while (cur.len && !cur.b[cur.len]) cur.len--;
		if (!cur.len) cur.len++;
		return cur;
	}
};

int n;
int a[MAXN+48];

struct pt
{
	int val,from;
	pt () {}
	inline pt (int vv,int ff) {val=vv;from=ff;}
	inline bool operator < (const pt &other) const {return val<other.val;}
}b[MAXN+48];

int itot=0;

struct SegmentTree
{
	Bigint sum[MAXN*4+48];
	inline void clear() {for (register int i=1;i<=MAXN*4;i++) sum[i].Set(0);}
	inline void pushup(int cur) {sum[cur]=sum[cur<<1]+sum[cur<<1|1];}
	inline void update(int cur,int pos,Bigint delta,int l,int r)
	{
		if (l==r) {sum[cur]=sum[cur]+delta;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) update(cur<<1,pos,delta,l,mid); else update(cur<<1|1,pos,delta,mid+1,r);
		pushup(cur);
	}
	inline Bigint query(int cur,int left,int right,int l,int r)
	{
		if (left>right) {Bigint tmp;tmp.Set(0);return tmp;}
		if (left<=l && r<=right) return sum[cur];
		int mid=(l+r)>>1;
		Bigint res;res.Set(0);
		if (left<=mid) res=res+query(cur<<1,left,right,l,mid);
		if (mid+1<=right) res=res+query(cur<<1|1,left,right,mid+1,r);
		return res;
	}
}sgt[6];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	while (scanf("%d",&n)!=EOF)
	{
		for (register int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=pt(a[i],i);
		sort(b+1,b+n+1);itot=0;
		for (register int i=1;i<=n;i++)
		{
			if (i==1 || b[i].val!=b[i-1].val) itot++;
			a[b[i].from]=itot;
		}
		for (register int i=1;i<=5;i++) sgt[i].clear();
		Bigint tmp;
		for (register int i=1;i<=n;i++)
		{
			tmp.Set(1);
			sgt[1].update(1,a[i],tmp,1,itot);
			for (register int j=2;j<=5;j++)
			{
				Bigint ins=sgt[j-1].query(1,1,a[i]-1,1,itot);
				sgt[j].update(1,a[i],ins,1,itot);
			}
		}
		Bigint ans=sgt[5].sum[1];
		ans.print();
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}