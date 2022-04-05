#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
char a[148][148];

struct BigInt
{
	int num[248],len;bool type;
	inline void clear()
	{
		memset(num,0,sizeof(num));
		len=1;type=true;
	}
	inline bool operator < (BigInt x)
	{
		if (tyep!=x.type)
		{
			if (len==1 && x.len==1 && num[1]==0 && x.num[1]==0) return false;
			if (type && !x.type) return false;
			if (!type && x.type) return true;
		}
		if (len>x.len) return false;
		if (len<x.len) return true;
		for (int i=len;i>=1;i--)
		{
			if (num[i]>x.num[i]) return false;
			if (num[i]<x.num[i]) return true;
		}
		return false;
	}
	inline BigInt operator + (BigInt x)
	{
		BigInt res;res.clear();int i;
		if (type==x.type)
		{
			for (i=1;i<=max(len,x.len);i++)
			{
				res.num[i]+=num[i]+x.num[i];
				if (res.num[i]>=10) res.num[i]-=10,res.num[i+1]++;
			}
			res.len=max(len,x.len);
			if (res.num[res.len+1]) res.len++;
			res.type=type;
			return res;
		}
		else
		{
			BigInt tmp1=*this,tmp2=x;
			if (tmp1<tmp2) swap(tmp1,tmp2);
			res.type=tmp1.type;
			for (i=1;i<=tmp1.len;i++)
			{
				res.num[i]+=tmp1.num[i]-tmp2.num[i];
				if (res.num[i]<0) res.num[i]+=10,res.num[i+1]--;
			}
			res.len=tmp1.len;
			while (!res.num[res.len] && res.len) res.len--;
			if (!res.len) res.len=1;
			return res;
		}
	}
	inline BigInt operator - (BigInt x)
	{
		BigInt res;res.clear();int i;
		if (type!=x.type)
		{
			for (i=1;i<=max(len,x.len);i++)
			{
				res.num[i]+=num[i]+x.num[i];
				if (res.num[i]>=10) res.num[i]-=10,res.num[i+1]++;
			}
			res.len=max(len,x.len);
			if (res.num[res.len+1]) res.len++;
			res.type=type;
			return res;
		}
		else
		{
			BigInt tmp1=*this,tmp2=x;
			res.type=type;if (tmp1<tmp2) res.type^=1,swap(tmp1,tmp2);
			for (i=1;i<=tmp1.len;i++)
			{
				res.num[i]+=tmp1.num[i]-tmp2.num[i];
				if (res.num[i]<0) res.num[i]+=10,res.num[i+1]--;
			}
			res.len=tmp1.len;
			while (!res.num[res.len] && res.len) res.len--;
			if (!res.len) res.len=1;
			return res;
		}
	}
	inline BigInt operator * (int x)
	{
		BigInt res;res.clear();int i;
		for (i=1;i<=len;i++)
		{
			res.num[i]+=num[i]*x;
			res.num[i+1]+=res.num[i]/10;res.num[i]%=10;
		}
		res.len=len;if (res.num[res.len+1]) res.len++;
		return res;
	}
	inline void print()
	{
		if (!type) cout<<"-";
		for (int i=len;i>=1;i--) cout<<num[i];
		cout<<endl;
	}
};

int num;
int head[100048],to[200048],nxt[200048],f[200048],tot=1;BigInt cost[200048];
bool visited[100048];BigInt D[100048];
inline void addedge(int s,int t,int cap,BigInt c)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=c;
	c.type=false;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=c;
}

inline int PairToInd(int x,int y)
{
	return (x-1)*m+y;
}

int R[48];
int dx[5]={-1,0,1,0},dy[5]={0,1,0,-1};

struct TheSquareDivOne
{
	inline void Clear()
	{
		memset(head,0,sizeof(head));tot=1;
		for (int i=0;i<=num+10;i++) D[i].clear();
	}
	inline bool check(BigInt x)
	{
		if (x.len==1 && x.num[1]==0) return true; else return false;
	}
	int aug(int cur,int maxf)
	{
		visited[cur]=true;
		if (cur==num) return maxf;
		int i,y,now,minf,ans=0;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (!visited[y] && f[i] && check(D[cur]+cost[i]-D[y]))
			{
				minf=min(f[i],maxf-ans);
				now=aug(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
				if (ans>=maxf) return ans;
			}
		}
		return ans;
	}
	bool relabel()
	{
		int cur,i,y;BigInt d;
		d.type=true;d.len=200;d.num[200]=1;
		for (cur=0;cur<=num;cur++)
			if (visited[cur])
				for (i=head[cur];i;i=nxt[i])
				{
					y=to[i];
					if (!visited[y] && f[i] && (D[cur]+cost[i]-D[y])<d) d=D[cur]+cost[i]-D[y];
				}
		if (d.len==200) return false;
		for(cur=0;cur<=num;cur++) if (visited[cur]) D[cur]=D[cur]-d;
	}
	vector<string> solve(vector<string> a)
	{
		vector<string> res;string ins;res.clear();
		n=int(a.size());m=int(a[0].size());
		num=n*m+m+1;Clear();
		int i,j,k,xx,yy,cur,y;BigInt cc;
		for (i=1;i<=n;i++)
		{
			R[i]=0;
			for (j=1;j<=m;j++)
				if (a[i-1][j-1]=='C') R[i]++;
		}
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (a[i-1][j-1]=='C')
				{
					cc.clear();
					addedge(0,PairToInd(i,j),1,cc);
				}
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
			{
				cc.clear();cc.num[1]=1;
				for (k=1;k<=(n*m+1-PairToInd(i,j));k++) cc=cc*2;
				addedge(PairToInd(i,j),n*m+j,1,cc);
				cc.clear();cc.num[1]=1;
				for (k=1;k<=n*m+48;k++) cc=cc*2;
				for (k=0;k<=3;k++)
				{
					xx=i+dx[k];yy=j+dy[k];
					if (1<=xx && xx<=n && 1<=yy && yy<=n)
						addedge(PairToInd(i,j),PairToInd(xx,yy),INF,cc);
				}
			}
		cc.clear();
		for (j=1;j<=m;j++) if (R[j]) addedge(n*m+j,num,R[j],cc);
		do
			do
				memset(visited,false,sizeof(visited));
			while (aug(0,INF));
		while (relabel());
		for (i=1;i<=n;i++)
		{
			ins="";
			for (j=1;j<=m;j++)
			{
				cur=PairToInd(i,j);
				bool ff=false;
				for (k=head[cur];k;k=nxt[k])
				{
					y=to[k];
					if (n*m+1<=y && y<=n*m+m && !f[k] && cost[k].type) {ins+=string(1,'C');ff=true;break;}
				}
				if (!ff) ins+=string(1,'.');
			}
			res.pb(ins);
		}
		return res;
	}
};

/*---Debug Part---*/
vector<string> v,ans;string s;
int main ()
{
	int nn,i,j;TheSquareDivOne A;
	while (scanf("%d",&nn)!=EOF)
	{
		v.clear();
		while (nn--)
		{
			cin>>s;
			v.pb(s);
		}
		ans=A.solve(v);
		for (i=0;i<int(ans.size());i++) cout<<ans[i]<<endl;
	}
	return 0;
}

/*---Test BigInt---*/
int main ()
{
	BigInt a,b;int x,y;
	x=getint();y=getint();
	a.len=b.len=0;a.type=b.type=true;
	while (x)
	{
		a.num[++a.len]=x%10;
		x/=10;
	}
	while (y)
	{
		b.num[++b.len]=y%10;
		y/=10;
	}
	BigInt c=a-b;
	if (!c.type) cout<<"-";
	for (int i=c.len;i>=1;i--) cout<<c.num[i];
	cout<<endl;
	return 0;
}
