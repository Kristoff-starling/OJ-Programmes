// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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

int n,m;
int a[148][148],suma[148][148];

int dp[2][148][148][2][2];
int sum[2][2][148][148][2][2];

class AmoebaDivOne
{
	inline void construct_map(vector<string> table)
	{
		int Mask,sx,sy;
		for (register int i=0;i<n;i++)
			for (register int j=0;j<m;j++)
			{
				if (isdigit(table[i][j])) Mask=table[i][j]-'0'; else Mask=table[i][j]-'a'+10;
				sx=i*2+1;sy=j*2+1;
				a[sx][sy]=(Mask&1);a[sx][sy+1]=(Mask>>1&1);
				a[sx+1][sy]=(Mask>>2&1);a[sx+1][sy+1]=(Mask>>3&1);
			}
		n*=2;m*=2;
		for (register int i=1;i<=n;i++)
		{
			suma[i][0]=0;
			for (register int j=1;j<=m;j++) suma[i][j]=suma[i][j-1]+a[i][j];
		}
	}
	inline void right_bigger(int row,int t1,int t2)
	{
		for (register int l=1;l<=m;l++)
			for (register int r=m;r>=1;r--)
				for (register int op1=0;op1<=1;op1++)
					for (register int op2=0;op2<=1;op2++)
						sum[t1][t2][l][r][op1][op2]=add(sum[t1][t2][l][r+1][op1][op2]+dp[row][l][r][op1][op2]);
	}
	inline void right_smaller(int row,int t1,int t2)
	{
		for (register int l=1;l<=m;l++)
			for (register int r=1;r<=m;r++)
				for (register int op1=0;op1<=1;op1++)
					for (register int op2=0;op2<=1;op2++)
						sum[t1][t2][l][r][op1][op2]=add(sum[t1][t2][l][r-1][op1][op2]+dp[row][l][r][op1][op2]);
	}
	inline void left_bigger(int row,int t1,int t2)
	{
		for (register int r=1;r<=m;r++)
			for (register int l=m;l>=1;l--)
				for (register int op1=0;op1<=1;op1++)
					for (register int op2=0;op2<=1;op2++)
						Add(sum[t1][t2][l][r][op1][op2],sum[t1][t2][l+1][r][op1][op2]);
	}
	inline void left_smaller(int row,int t1,int t2)
	{
		for (register int r=1;r<=m;r++)
			for (register int l=1;l<=m;l++)
				for (register int op1=0;op1<=1;op1++)
					for (register int op2=0;op2<=1;op2++)
						Add(sum[t1][t2][l][r][op1][op2],sum[t1][t2][l-1][r][op1][op2]);
	}
	inline void construct_sum(int row)
	{
		memset(sum,0,sizeof(sum));
		right_smaller(row,0,0);left_bigger(row,0,0);
		right_bigger(row,0,1);left_bigger(row,0,1);
		right_smaller(row,1,0);left_smaller(row,1,0);
		right_bigger(row,1,1);left_smaller(row,1,1);
	}
	inline bool has_obstacle(int r,int left,int right) {return suma[r][right]-suma[r][left-1];}
	public:
		inline int count(vector<string> table)
		{
			n=int(table.size());m=int(table[0].size());
			construct_map(table);memset(dp,0,sizeof(dp));
			int ans=0;
			for (register int l=1;l<=m;l++)
				for (register int r=l;r<=m;r++)
					if (!has_obstacle(1,l,r)) dp[0][l][r][0][0]=1,Add(ans,1);
			construct_sum(0);int pre=0,cur=1;
			for (register int i=2;i<=n;i++)
			{
				memset(dp[cur],0,sizeof(dp[cur]));
				for (register int l=1;l<=m;l++)
					for (register int r=l;r<=m;r++)
					{
						if (has_obstacle(i,l,r))
						{
							for (register int op1=0;op1<=1;op1++)
								for (register int op2=0;op2<=1;op2++)
									dp[cur][l][r][op1][op2]=0;
							continue;
						}
						dp[cur][l][r][0][0]=1;
						Add(dp[cur][l][r][0][0],sum[0][0][l][r][0][0]);
						Add(ans,dp[cur][l][r][0][0]);

						Add(dp[cur][l][r][0][1],sub(add(sum[0][1][l][r+1][0][0]+sum[0][1][l][r+1][0][1])-add(sum[0][1][r+1][r+1][0][0]+sum[0][1][r+1][r+1][0][1])));
						Add(dp[cur][l][r][0][1],sub(sum[0][1][l][r][0][1]-sum[0][1][l][r+1][0][1]));
						Add(ans,dp[cur][l][r][0][1]);

						Add(dp[cur][l][r][1][0],sub(add(sum[1][0][l-1][r][0][0]+sum[1][0][l-1][r][1][0])-add(sum[1][0][l-1][l-1][0][0]+sum[1][0][l-1][l-1][1][0])));
						Add(dp[cur][l][r][1][0],sub(sum[1][0][l][r][1][0]-sum[1][0][l-1][r][1][0]));
						Add(ans,dp[cur][l][r][1][0]);

						for (register int op1=0;op1<=1;op1++)
							for (register int op2=0;op2<=1;op2++)
								Add(dp[cur][l][r][1][1],sum[1][1][l-1][r+1][op1][op2]);
						for (register int op1=0;op1<=1;op1++)
							Add(dp[cur][l][r][1][1],sub(sum[1][1][l-1][r][op1][1]-sum[1][1][l-1][r+1][op1][1]));
						for (register int op2=0;op2<=1;op2++)
							Add(dp[cur][l][r][1][1],sub(sum[1][1][l][r+1][1][op2]-sum[1][1][l-1][r+1][1][op2]));
						Add(dp[cur][l][r][1][1],dp[pre][l][r][1][1]);
						Add(ans,dp[cur][l][r][1][1]);
					}
				construct_sum(cur);cur^=1;pre^=1;
			}
			return ans;
		}
};

/* --- Debug Part ---*/
/*
int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;string s;vector<string> ss;
	AmoebaDivOne A;
	while (cin>>nn)
	{
		ss.clear();
		for (register int i=1;i<=nn;i++) cin>>s,ss.pb(s);
		cout<<A.count(ss)<<endl;
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
*/
