#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define ull unsigned long long
#define pb push_back
using namespace std;

const int MAXN=1e5;
const int P=998244353;

ull h[MAXN+48],pw[MAXN+48];
char s[MAXN+48],ss[100];

unordered_map<ull,int> S;
int len[MAXN+48];

ull query(int l,int r)
{
    return h[r]-h[l-1]*pw[r-l+1];
}

vector<int> v[MAXN+48];

int ans[MAXN+48];
int toans[MAXN+48];

int solve(int ind)
{
    if (ans[ind]!=-1) return ans[ind];
    int res=0,cur=-100;
    for (auto pos : v[ind]) if (pos-cur>=len[ind]) res++,cur=pos;
    ans[ind]=res;
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    pw[0]=1;rep(i,1,MAXN) pw[i]=pw[i-1]*P;
    while (ca--)
    {
        scanf("%s",s+1);int n=strlen(s+1);
        h[0]=0;rep(i,1,n) h[i]=h[i-1]*P+s[i];
        S.clear();
        int m;scanf("%d",&m);rep(i,1,m) v[i].clear();
        rep(i,1,m)
        {
            scanf("%s",ss+1);ull cur=0;int nn=strlen(ss+1);len[i]=nn;
            rep(j,1,nn) cur=cur*P+ss[j];
            if (S.find(cur)==S.end()) S[cur]=i,toans[i]=i;
            else toans[i]=S[cur];
        }
        rep(i,1,n)
        {
            rep(j,1,min(i,30))
            {
                ull id=query(i-j+1,i);
                if (S.find(id)!=S.end()) v[S[id]].pb(i);
            }
        }
        rep(i,1,m) ans[i]=-1;
        rep(i,1,m) printf("%d\n",solve(toans[i]));
    }
    return 0;
}