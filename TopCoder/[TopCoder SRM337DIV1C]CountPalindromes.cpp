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
const int MOD=835454957;
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
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

class CountPalindromes
{
	int n;
	char s[148][48];int len[148];
	bool table_suf[148][48][148],table_pref[148][48][148];
	int dp[148][58][21][2];
	inline bool judge_evenpalindrome(int id,int pos)
	{
		if (pos<=len[id]-pos)
		{
			for (register int i=pos;i>=1;i--)
				if (s[id][i]!=s[id][pos+pos-i+1]) return false;
			return true;
		}
		else
		{
			for (register int i=pos+1;i<=len[id];i++)
				if (s[id][i]!=s[id][pos-(i-(pos+1))]) return false;
			return true;
		}
	}
	inline bool judge_oddpalindrome(int id,int pos)
	{
		if (pos-1<=len[id]-pos)
		{
			for (register int l=1,r=pos+pos-1;l<=r;l++,r--)
				if (s[id][l]!=s[id][r]) return false;
			return true;
		}
		else
		{
			for (register int l=pos-(len[id]-pos),r=len[id];l<=r;l++,r--)
				if (s[id][l]!=s[id][r]) return false;
			return true;
		}
	}
	public:
		inline int count(vector<string> words,int lim)
		{
			n=int(words.size());
			for (register int i=1;i<=n;i++)
			{
				for (register int j=0;j<int(words[i-1].size());j++)
					s[i][j+1]=words[i-1][j];
				len[i]=int(words[i-1].size());s[i][len[i]+1]='\0';
			}
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=len[i]+1;j++)
					for (register int k=1;k<=n;k++)
					{
						bool f=true;
						for (register int p=j;p<=min(len[i],j+len[k]-1);p++)
							if (s[i][p]!=s[k][len[k]-(p-j)]) {f=false;break;}
						table_suf[i][j][k]=f;
					}
			for (register int i=1;i<=n;i++)
				for (register int j=0;j<=len[i];j++)
					for (register int k=1;k<=n;k++)
					{
						bool f=true;
						for (register int p=j;p>=max(1,j-len[k]+1);p--)
							if (s[i][p]!=s[k][j-p+1]) {f=false;break;}
						table_pref[i][j][k]=f;
					}
			// cerr<<table_pref[1][3][1]<<"@"<<endl;
			memset(dp,0,sizeof(dp));
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=len[i];j++)
					if (judge_evenpalindrome(i,j))
					{	
						if (j<len[i]-j)
							Add(dp[len[i]][i][j*2+1][1],1);
						else
							Add(dp[len[i]][i][len[i]-(len[i]-j)*2][0],1);
					}
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=len[i];j++)
					if (judge_oddpalindrome(i,j))
					{
						if (j-1<len[i]-j)
							Add(dp[len[i]][i][j*2][1],1);
						else
							Add(dp[len[i]][i][len[i]-(len[i]-j)*2-1][0],1);
					}
			for (register int L=1;L<=lim-1;L++)
				for (register int i=1;i<=n;i++)
					for (register int j=0;j<=len[i];j++)
					{
						if (dp[L][i][j][0])
						{
							if (j==0)
							{
								for (register int k=1;k<=n;k++)
									if (L+len[k]+1<=lim)
										Add(dp[L+len[k]+1][k][len[k]][0],dp[L][i][j][0]);
								continue;
							}
							for (register int k=1;k<=n;k++)
								if (table_pref[i][j][k] && L+len[k]+1<=lim)
								{
									if (j>=len[k])
										Add(dp[L+len[k]+1][i][j-len[k]][0],dp[L][i][j][0]);
									else
										Add(dp[L+len[k]+1][k][j+1][1],dp[L][i][j][0]);
								}
						}
						if (dp[L][i][j][1])
							for (register int k=1;k<=n;k++)
								if (table_suf[i][j][k] && L+len[k]+1<=lim)
								{
									if (len[i]-j+1>len[k])
										Add(dp[L+len[k]+1][i][j+len[k]][1],dp[L][i][j][1]);
									else
										Add(dp[L+len[k]+1][k][len[k]-(len[i]-j+1)][0],dp[L][i][j][1]);
								}
					}
			int ans=0;
			for (register int L=1;L<=lim;L++)
				for (register int i=1;i<=n;i++)
					Add(ans,dp[L][i][0][0]);
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
	vector<string> ss;string s;CountPalindrome A;int nn,kk;
	while (cin>>nn>>kk)
	{
		ss.clear();
		for (register int i=1;i<=nn;i++) cin>>s,ss.pb(s);
		cout<<A.count(ss,kk)<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif