#include <bits/stdc++.h>
using namespace std;

const int MAXN=(1<<23);

int n,ind[48];
char ga[48][48];
int f[MAXN+48],F[MAXN+48],coef[MAXN+48];

namespace DSU
{
	int pre[48],sz[48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i,sz[i]=1;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (x!=y) pre[x]=y,sz[y]+=sz[x];
	}
}

inline void poly_fwt(int c[],int len)
{
	for (register int clen=2;clen<=len;clen<<=1)
		for (register int j=0;j<len;j+=clen)
			for (register int k=j;k<j+(clen>>1);k++)
				c[k+(clen>>1)]+=c[k];
}

inline void init_coef(int c[],int len)
{
	for (register int clen=2;clen<=len;clen<<=1)
		for (register int j=0;j<len;j+=clen)
			for (register int k=j;k<j+(clen>>1);k++)
				c[k]*=-1;
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	scanf("%d",&n);
	for (register int i=1;i<=n;i++) scanf("%s",ga[i]+1);
	DSU::init();
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=i-1;j++)
			if (ga[i][j]=='A') DSU::update(i,j);
	int ans=0,tot=0;
	for (register int i=1;i<=n;i++)
		if (DSU::find_anc(i)==i) 
		{
			ans+=DSU::sz[i];
			if (DSU::sz[i]>=2) ind[i]=++tot;
		}
	if (!tot) {printf("%d\n",n-1);return 0;}
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=i-1;j++)
			if (ga[i][j]=='X')
			{
				if (DSU::issame(i,j)) {puts("-1");return 0;}
				int root1=DSU::find_anc(i),root2=DSU::find_anc(j);
				if (ind[root1] && ind[root2]) f[(1<<(ind[root1]-1))|(1<<(ind[root2]-1))]=1;
			}
	for (register int Mask=1;Mask<=(1<<tot)-1;Mask++)
		for (register int i=1;i<=tot;i++)
			if (Mask&(1<<(i-1))) f[Mask]|=f[Mask^(1<<(i-1))];
	for (register int Mask=0;Mask<=(1<<tot)-1;Mask++) f[Mask]^=1;
	for (register int Mask=0;Mask<=(1<<tot)-1;Mask++) coef[Mask]=1,F[Mask]=1;
	poly_fwt(f,1<<tot);init_coef(coef,1<<tot);
	for (register int i=0;;i++)
	{
		int tmp=0;
		for (register int Mask=0;Mask<=(1<<tot)-1;Mask++) F[Mask]*=f[Mask];
		for (register int Mask=0;Mask<=(1<<tot)-1;Mask++) tmp+=coef[Mask]*F[Mask];
		if (tmp) {printf("%d\n",ans+i);break;}
	}
	return 0;
}
