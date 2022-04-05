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

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1000;

multiset<int> s;

int n;
int a[MAXN+48];

inline int myabs(int x) {return x>=0?x:-x;}

int main ()
{
	int i,j;
	while (scanf("%d",&n)!=EOF)
	{
		s.clear();int ans=-1;
		for (i=1;i<=n;i++) a[i]=getint(),s.insert(a[i]);
		int i,j;multiset<int>::iterator iter1,iter2,iter;
		for (i=1;i<=n-1;i++)
			for (j=i+1;j<=n;j++)
			{
//				cout<<i<<' '<<j<<endl;
				iter1=s.find(a[i]);s.erase(iter1);
				iter2=s.find(a[j]);s.erase(iter2);
				iter=s.lower_bound(a[i]+a[j]);
//				cout<<(iter==s.end())<<endl;
				if (iter!=s.begin())
				{
					--iter;
					int num=(*iter);
					if (num>myabs(a[i]-a[j])) ans=max(ans,num+a[i]+a[j]);
				}
				s.insert(a[i]);s.insert(a[j]);
			}
		printf("%d\n",ans);
	}
	return 0;
}
