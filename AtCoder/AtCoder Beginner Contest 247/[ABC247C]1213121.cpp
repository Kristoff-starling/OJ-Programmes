#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

void dfs(int layer)
{
    if (layer==1) {printf("1 ");return;}
    dfs(layer-1);printf("%d ",layer);dfs(layer-1);
}

int main ()
{
    int n;scanf("%d",&n);
    dfs(n);puts("");
    return 0;
}