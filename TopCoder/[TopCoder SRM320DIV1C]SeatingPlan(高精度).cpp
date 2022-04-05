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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void add(int &x,int y) {x=add(x+y);}
inline void sub(int &x,int y) {x=sub(x-y);}

inline int getw(int x)
{
	if (!x) return 1;
	int res=0;
	while (x) res++,x/=10;
	return res;
}

inline string INT_TO_STRING(ull x)
{
	string res;res="";
	if (!x) {res="0";return res;}
	while (x)
	{
		res=string(1,'0'+x%10)+res;
		x/=10;
	}
	return res;
}

const int BIT=1000;

struct Bigint
{
	int b[108],len;
	Bigint () {memset(b,0,sizeof(b));}
	inline bool iszero() {return len==1 && b[1]==0;}
	inline void Set(int x)
	{
		memset(b,0,sizeof(b));
		if (!x) {b[1]=0;len=1;return;}
		len=0;
		while (x) b[++len]=x%BIT,x/=BIT;
	}
	inline string trans()
	{
		string res;res="";
		for (register int i=len;i>=1;i--)
		{
			int nu=getw(b[i]);string tmp=INT_TO_STRING(b[i]);
			if (i!=len) for (register int j=1;j<=(3-nu);j++) tmp="0"+tmp;
			res+=tmp;
		}
		return res;
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
		assert(len>=other.len);
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

inline Bigint gcd(Bigint x,Bigint y)
{
	if (y.iszero()) return x;
	return gcd(y,x%y);
}

class SeatingPlan
{
	int n,m,k;
	int vMask[10048],vtot;
	int cnt[10048];
	Bigint dp[2][348][21],fac[148];
	inline void init_Mask()
	{
		vtot=0;
		for (register int Mask=0;Mask<=(1<<m)-1;Mask++)
		{
			if (!(Mask&(Mask<<1))) vMask[++vtot]=Mask;
			cnt[Mask]=0;
			for (register int tmp=Mask;tmp;tmp-=LOWBIT(tmp)) cnt[Mask]++;
		}
	}
	public:
		inline string expectedTrial(int N,int M,int K)
		{
			n=N;m=M;k=K;if (n<m) swap(n,m);
			init_Mask();
			for (register int i=0;i<=1;i++)
				for (register int Mask=0;Mask<=(1<<m)-1;Mask++)
					for (register int num=0;num<=k;num++)
						dp[i][Mask][num].Set(0);
			dp[0][0][0].Set(1);int cur=0,nxt=1;
			for (register int i=0;i<=n-1;i++)
			{
				for (register int j=1;j<=vtot;j++)
					for (register int num=0;num<=k;num++)
					{
						register int Mask=vMask[j];
						if (!dp[cur][Mask][num].iszero())
						{
							for (register int jj=1;jj<=vtot;jj++)
							{
								register int toMask=vMask[jj];
								if (!(Mask&toMask))
									dp[nxt][toMask][num+cnt[toMask]]=dp[nxt][toMask][num+cnt[toMask]]+dp[cur][Mask][num];
							}
							dp[cur][Mask][num].Set(0);
						}
					}
				cur^=1;nxt^=1;
			}
			Bigint ans;ans.Set(0);ull aa=0;
			for (register int j=1;j<=vtot;j++)
				ans=ans+dp[cur][vMask[j]][k],aa+=f[cur][vMask[j]][k];
			if (ans.iszero()) return "Impossible!";
			fac[0].Set(1);Bigint tmp;
			for (register int i=1;i<=n*m;i++) tmp.Set(i),fac[i]=fac[i-1]*tmp;
			ans=ans*fac[k]*fac[n*m-k];
			Bigint g=gcd(ans,fac[n*m]);
			ans=ans/g;fac[n*m]=fac[n*m]/g;
			string fans;fans="";
			fans+=fac[n*m].trans();fans+="/";fans+=ans.trans();
			return fans;
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	// cerr<<__gcd(384,720)<<endl;
	// LL aa=2040548182754328576,bb=516260983;
	// LL g=__gcd(aa,bb);
	// aa/=g;bb/=g;
	// cerr<<aa<<' '<<bb<<endl;
	int nn,mm,kk;SeatingPlan A;
	while (cin>>nn>>mm>>kk) cout<<A.expectedTrial(nn,mm,kk)<<endl;
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif