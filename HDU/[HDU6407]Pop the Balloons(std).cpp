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
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

struct Bigint
{
	int b[48],len;
	inline void clear() {memset(b,0,sizeof(b));len=0;}
	inline Bigint operator * (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=len;i++)
			for (register int j=1;j<=other.len;j++)
				res.b[i+j-1]+=b[i]*other.b[j];
		res.len=len+other.len-1;
		for (register int i=1;i<=res.len;i++) res.b[i+1]+=res.b[i]/10,res.b[i]%=10;
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline void Print()
	{
		for (register int i=len;i>=1;i--) io.Writechar('0'+b[i]);
		io.Writechar('\n');
	}
};

template <class T> inline Bigint Set(T x)
{
	Bigint res;res.clear();
	while (x) res.b[++res.len]=x%10,x/=10;
	if (res.len==0) res.len=1;
	return res;
}

int n,m,K;
char a[48][48];int Mask[48];
LL dp[21][10048];
LL ans[21];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int i,j,ca,mask1,mask2,tomask;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(K);
		for (i=1;i<=n;i++) io.getstring(a[i]+1);
		for (j=1;j<=m;j++)
		{
			Mask[j]=0;
			for (i=1;i<=n;i++) if (a[i][j]=='Q') Mask[j]|=(1<<(i-1));
		}
		memset(ans,0,sizeof(ans));
		for (mask1=1;mask1<=(1<<n)-1;mask1++)
		{
			dp[0][0]=1;
			for (i=1;i<=m;i++)
			{
				bool f=false;
				for (mask2=mask1;;mask2=mask1&(mask2-1))
				{
					if (dp[i-1][mask2])
					{
						if ((Mask[i]&mask1)==Mask[i]) dp[i][mask2]+=dp[i-1][mask2],f=true;
						for (auto diff=Mask[i]&(mask1^mask2);diff;diff&=(diff-1))
						{
							auto bit=diff & (-diff);
							dp[i][mask2|bit]+=dp[i-1][mask2];
							f=true;
						}
						dp[i-1][mask2]=0;
					}
					if (!mask2) break;
				}
				if (!f) break;
			}
			ans[__builtin_popcount(mask1)]+=dp[m][mask1];
			for (mask2=mask1;;mask2=mask1&(mask2-1))
			{
				dp[m][mask2]=0;
				if (!mask2) break;
			}
		}
		LL fac=1;
		for (i=1;i<=K;i++)
		{
			fac*=i;
			if (ans[i]==0) {io.Print(0);continue;}
			(Set(fac)*Set(ans[i])).Print();
		}
	}
	io.flush();return 0;
}
