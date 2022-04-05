#include <bits/stdc++.h>
#define pb push_back
// #define LOCAL true
using namespace std;

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

typedef long long LL;
typedef pair<int,int> Pair;

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e6;

int n,m;
int t[MAXN+48],A[MAXN+48],B[MAXN+48];

int L[MAXN+48];
vector<int> v[MAXN+48];
int sta[MAXN+48],stot;

int root[MAXN+48];LL dp[MAXN+48];
int val[MAXN+48],delta[MAXN+48],lson[MAXN+48],rson[MAXN+48],h[MAXN+48],tot;

inline int Create(int nv,int d,int ls,int rs)
{
	++tot;val[tot]=nv;delta[tot]=d;lson[tot]=ls;rson[tot]=rs;h[tot]=0;
	return tot;
}

inline int merge(int root1,int root2)
{
	if (!root1 || !root2) return root1^root2;
	if (val[root1]>val[root2]) swap(root1,root2);
	rson[root1]=merge(rson[root1],root2);
	if (h[lson[root1]]<h[rson[root1]]) swap(lson[root1],rson[root1]);
	h[root1]=h[rson[root1]]+1;
	return root1;
}

inline int push(int rt,int nv,int delta) {return merge(rt,Create(nv,delta,0,0));}

inline int pop(int rt) {return merge(lson[rt],rson[rt]);}

inline void dfs(int cur)
{
	root[cur]=Create(0,0,0,0);dp[cur]=1ll*t[cur]*A[cur];
	root[cur]=push(root[cur],t[cur],A[cur]+B[cur]);
	for (auto y : v[cur]) dfs(y),root[cur]=merge(root[cur],root[y]),dp[cur]+=dp[y];
	if (cur)
	{
		int k=-A[cur]+delta[root[cur]];
		for (;k<0;k+=delta[root[cur]])
		{
			int pos1=val[root[cur]];
			root[cur]=pop(root[cur]);int pos2=val[root[cur]];
			dp[cur]+=1ll*k*(pos2-pos1);
		}
		int nv=val[root[cur]];
		root[cur]=pop(root[cur]);root[cur]=push(root[cur],nv,k);
	}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n);Get(m);int l,r;
	for (register int i=1;i<=n;i++) Get(t[i]),Get(A[i]),Get(B[i]);
	for (register int i=1;i<=n;i++) L[i]=n+1;
	for (register int i=1;i<=m;i++) Get(l),Get(r),check_min(L[r],l);
	for (register int i=1;i<=n;i++)
	{
		while (stot && sta[stot]>=L[i]) v[i].pb(sta[stot--]);
		sta[++stot]=i;
	}
	while (stot) v[0].pb(sta[stot--]);
	dfs(0);printf("%lld\n",dp[0]);
	return 0;
}
