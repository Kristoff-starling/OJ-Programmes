#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

char s[101],t[101];
vector<int> v;

int main ()
{
    scanf("%s%s",s+1,t+1);int len=strlen(s+1);
    rep(i,1,len) if (s[i]!=t[i]) v.push_back(i);
    if (!int(v.size())) {puts("Yes");return 0;}
    if (int(v.size())==1 || int(v.size())>=3) {puts("No");return 0;}
    if (v[0]+1!=v[1]) {puts("No");return 0;}
    if (s[v[0]]==t[v[1]] && s[v[1]]==t[v[0]]) puts("Yes"); else puts("No");
    return 0;
}