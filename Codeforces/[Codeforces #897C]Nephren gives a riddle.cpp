#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL num[100048];
string s1="What are you doing while sending *";
string s2="What are you doing at the end of the world? Are you busy? Will you save us?";
string s3="*? Are you busy? Will you send *";
string s4="*?";

void init()
{
	num[0]=75;
	int i;
	for (i=1;i<=53;i++)
		num[i]=num[i-1]*2+68;
}

int n;LL k;

void doit(LL rest,int step)
{
	if (step==0)
	{
		cout<<s2[rest-1];
		return;
	}
	if (rest<=34)
	{
		if (s1[rest-1]=='*') cout<<"\""; else cout<<s1[rest-1];
		return;
	}
	if (34+num[step-1]>=rest)
	{
		doit(rest-34,step-1);
		return;
	}
	rest=rest-(34+num[step-1]);
	if (rest<=32)
	{
		if (s3[rest-1]=='*') cout<<"\""; else cout<<s3[rest-1];
		return;
	}
	if (32+num[step-1]>=rest)
	{
		doit(rest-32,step-1);
		return;
	}
	rest=rest-(32+num[step-1]);
	if (s4[rest-1]=='*') cout<<"\""; else cout<<s4[rest-1];
}

int main ()
{
	init();
	int q;
	cin>>q;
	while (q--)
	{
		cin>>n>>k;
		if (n<53 && num[n]<k)
		{
			printf(".");
			continue;
		}
		if (n>53)
		{
			LL dd=(n-53)*34;
			if (dd>=k)
			{
				k%=34;
				if (k==0) k+=34;
				if (s1[k-1]=='*') cout<<"\""; else cout<<s1[k-1];
				continue;
			}
			k-=dd;
		}
		doit(k,min(53,n));
	}
	return 0;
}
