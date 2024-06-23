#include <bits/stdc++.h>
using namespace std;

int n;

void dfs(int step,string s,int x)
{
    if (step==n) {cout<<s<<endl;return;}
    char ch1='1',ch2='0';if (x&1) swap(ch1,ch2);
    dfs(step+1,s+string(1,ch1),x*2-1);dfs(step+1,s+string(1,ch2),x<<1);
}

int main ()
{
    scanf("%d",&n);
    dfs(0,"",1);return 0;
}