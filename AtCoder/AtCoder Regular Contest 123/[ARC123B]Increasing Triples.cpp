#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define mp make_pair
using namespace std;

const int MAXN=1e5;

int n;

multiset<Pair> A,B,C;

int main ()
{
    scanf("%d",&n);int x;
    rep(i,1,n) scanf("%d",&x),A.insert(mp(x,3));
    rep(i,1,n) scanf("%d",&x),B.insert(mp(x,2));
    rep(i,1,n) scanf("%d",&x),C.insert(mp(x,1));
    int ans=0;
    for (multiset<Pair>::iterator iter=A.begin();iter!=A.end();iter++)
    {
        Pair val=(*iter);
        multiset<Pair>::iterator pos=B.lower_bound(val);
        if (pos==B.end()) break;
        val=(*pos);B.erase(pos);pos=C.lower_bound(val);
        if (pos==C.end()) break;
        C.erase(pos);ans++;
    }
    printf("%d\n",ans);
    return 0;
}