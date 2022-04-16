#include <bits/stdc++.h>
#define LL long long
#define Pair pair<int,int>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=3e5;
const LL LINF=2e16;

int n,m;
vector<Pair> v[MAXN+48];
vector<int> path[MAXN+48];int tot;

int main ()
{
    scanf("%d%d",&n,&m);int x,y,c;LL sum=0;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].push_back(make_pair(y,c)),sum+=c;
    tot=0;
    for (auto item : v[1])
    {
        ++tot;
        path[tot].push_back(item.second);int cur=item.first;
        while (cur!=n)
        {
            path[tot].push_back(v[cur][0].second);
            cur=v[cur][0].first;
        }
    }
    int len=int(path[1].size());LL maxans=sum/len;
    rep(i,1,tot) sort(path[i].begin(),path[i].end());
    LL ans=0,cnt=0;
    rep(i,0,len-1){
        rep(j,1,tot){
            LL la=0;
            if(i!=0) la=path[j][i-1];
            LL avl=path[j][i]-la;
            if(cnt+avl>=maxans) avl=maxans-cnt;
            cnt+=avl;
            ans+=i*avl;
        }
    }
    printf("%lld\n",ans);
    return 0;
}