#include <bits/stdc++.h>
#define LL long long
#define pb push_back
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,m;

int ga[48][48];

unordered_map<LL,int> s1,s2;
vector<int> v[48];

void init(int l,int r,unordered_map<LL,int> *s)
{
    int N=r-l+1;
    rep(Mask,0,(1<<N)-1)
    {
        LL val=0;int cnt=0;
        rep(i,0,N-1) if (Mask>>i&1)
        {
            cnt++;val^=(1ll<<(l+i-1));
            for (auto y : v[l+i]) val^=(1ll<<(y-1));
        }
        if ((*s).find(val)==(*s).end())
            (*s)[val]=cnt;
        else
            (*s)[val]=min((*s)[val],cnt);
    }
}

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),ga[x][y]=ga[y][x]=1;
    rep(i,1,n) rep(j,1,n) if (i!=j && ga[i][j]==1) v[i].pb(j);
    if (n==1) {puts("1");return 0;}
    init(1,n/2,&s1);init(n/2+1,n,&s2);
    int ans=100;
    for (unordered_map<LL,int>::iterator iter=s1.begin();iter!=s1.end();iter++)
    {
        LL target=(((1ll<<n)-1)^iter->first);
        if (s2.find(target)!=s2.end()) ans=min(ans,iter->second+s2.find(target)->second);
    }
    if (ans==100) ans=-1;
    printf("%d\n",ans);
    return 0;
}