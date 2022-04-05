#include <bits/stdc++.h>
using namespace std;

char s[1048];
string s1,s2;

int main ()
{
	int n,q,l,r;
	cin>>n>>q;
	scanf("%s",s+1);
	while (q--)
	{
		cin>>l>>r>>s1>>s2;
		for (int i=l;i<=r;i++)
			if (s[i]==s1[0]) s[i]=s2[0];
	}
	puts(s+1);
	return 0;
}
