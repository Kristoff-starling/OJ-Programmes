#include <bits/stdc++.h>
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

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const LB eps=1e-15;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

class FoxCardGame
{
	double a[148],b[148];int n,k;
	double dp[58][58][58];
	public:
		inline double theMaxProportion(vector<double> A,vector<double> B,int K)
		{
			n=int(A.size());k=K;int i;
			for (i=1;i<=n;i++) a[i]=A[i-1],b[i]=B[i-1];
			sort(a+1,a+n+1);sort(b+1,b+n+1);
		}
};

/*---Debug Part---*/
int main ()
{
	vector<double> aa,bb;int nn;double x;int kk;
	FoxCardGame A;
	while (cin>>nn)
	{
		aa.clear();bb.clear();
		for (int i=1;i<=nn;i++) scanf("%lf",&x),aa.pb(x);
		for (int i=1;i<=nn;i++) scanf("%lf",&x),bb.pb(x);
		cin>>kk;
		printf("%.10lf\n",A.theMaxProportion(aa,bb,kk));
	}
	return 0;
}
