#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,p,k;

struct Order
{
	int hair,dis,ind;
	inline void input(int _i) {Get(hair);Get(dis);ind=_i;}
}a[MAXN+48];
bool visited[MAXN+48];

int val[MAXN+48],tot;
vector<Order> v[MAXN+48],vv[MAXN+48];
int ans[MAXN+48],atot;

inline bool cmp_hair(Order x,Order y) {return x.hair>y.hair;}
inline bool cmp_dis(Order x,Order y) {return x.dis>y.dis;}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
#endif
	Get(n);Get(p);Get(k);
	for (register int i=1;i<=n;i++) a[i].input(i);
	tot=0;for (register int i=1;i<=n;i++) val[++tot]=a[i].hair;
	sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
	for (register int i=1;i<=n;i++) a[i].hair=lower_bound(val+1,val+tot+1,a[i].hair)-val;
	tot=0;for (register int i=1;i<=n;i++) val[++tot]=a[i].dis;
	sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
	for (register int i=1;i<=n;i++) a[i].dis=lower_bound(val+1,val+tot+1,a[i].dis)-val,v[a[i].dis].pb(a[i]);
	int pt=1,cnt=0;
	while (pt<=n && cnt+int(v[pt].size())<=p-k) cnt+=int(v[pt++].size());
	sort(v[pt].begin(),v[pt].end(),cmp_hair);int st=p-k-cnt;
	for (register int i=st;i<int(v[pt].size());i++) vv[v[pt][i].hair].pb(v[pt][i]);
	for (register int i=pt+1;i<=tot;i++) for (auto item : v[i]) vv[item.hair].pb(item);
	cnt=0;pt=n;
	while (pt>=1 && cnt+int(vv[pt].size())<=k)
	{
		cnt+=int(vv[pt].size());
		for (auto item : vv[pt]) ans[++atot]=item.ind;
		pt--;
	}
	sort(vv[pt].begin(),vv[pt].end(),cmp_dis);
	for (register int i=0;i<k-cnt;i++) ans[++atot]=vv[pt][i].ind;
	assert(atot==k);int mindis=n+48,maxhair=-1;
	for (register int i=1;i<=atot;i++)
	{
		visited[ans[i]]=true;
		if (a[ans[i]].dis<mindis) mindis=a[ans[i]].dis,maxhair=a[ans[i]].hair;
		else if (a[ans[i]].dis==mindis) check_max(maxhair,a[ans[i]].hair);
	}
	sort(a+1,a+n+1,cmp_dis);
	for (register int i=1;i<=n && atot<p;i++) if (!visited[a[i].ind] && (a[i].dis<mindis || (a[i].dis==mindis && a[i].hair>=maxhair))) ans[++atot]=a[i].ind;
	for (register int i=1;i<=p;i++) printf("%d ",ans[i]);puts("");
	return 0;
}
