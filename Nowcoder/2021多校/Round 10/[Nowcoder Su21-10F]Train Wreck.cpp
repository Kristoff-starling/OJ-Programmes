#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define Pair pair<int,int>
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=2e6;

int n;
char s[MAXN+48];
int a[MAXN+48];

vector<int> v[MAXN+48];
int sta[MAXN+48],tot;

priority_queue<Pair> q;

bool visited[MAXN+48];
int ans[MAXN+48];

int cnt;

struct node
{
    int sz;
    vector<int> id;
    bool operator < (const node &other) const {return sz>other.sz;}
}b[MAXN+48];int btot;

void dfs(int cur)
{
    visited[cur]=true;b[btot].sz++;b[btot].id.pb(cur);
    for (auto y : v[cur]) if (!visited[y]) dfs(y);
}

int cc[MAXN+48];

bool cmp(int x,int y) {return x>y;}
Pair tmp[MAXN+48];int tt;

int main ()
{
    scanf("%d%s",&n,s+1);
    rep(i,1,n) scanf("%d",a+i),cc[a[i]]++;
    rep(i,1,n) if (cc[i]) q.push(mp(cc[i],i));
    int last=0;tot=0;
    rep(i,1,n+n)
    {
        if (s[i]=='(') sta[++tot]=i; else last=sta[tot--];
        if (i>1 && s[i]=='(' && s[i-1]==')') v[i].pb(last),v[last].pb(i);
    }
    rep(i,1,n+n) if (s[i]=='(' && !visited[i]) ++btot,b[i].sz=0,b[i].id.clear(),dfs(i);
    sort(b+1,b+btot+1);bool f=true;
    rep(i,1,btot)
    {
        if (int(q.size())<b[i].sz) {f=false;break;}
        rep(j,1,b[i].sz) tmp[j]=q.top(),q.pop();
        rep(j,1,b[i].sz) ans[b[i].id[j-1]]=tmp[j].y,tmp[j].x--;
        rep(j,1,b[i].sz) if (tmp[j].x>0) q.push(tmp[j]);
    }
    if (!f) puts("NO");
    else
    {
        puts("YES");
        rep(i,1,n+n) if (ans[i]) printf("%d ",ans[i]);
        puts("");
    }
    return 0;
}