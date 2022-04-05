#include <bits/stdc++.h>
using namespace std;

int n,m;
int a[100048];

namespace DSU
{
	int pre[100048];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]); return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

int main ()
{
	int i,x,y;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	DSU::init();
	for (i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		DSU::update(x,y);
	}
	int ans=0;
	for (i=1;i<=n;i++) if (DSU::find_anc(i)==DSU::find_anc(a[i])) ans++;
	printf("%d\n",ans);
	return 0;
}
