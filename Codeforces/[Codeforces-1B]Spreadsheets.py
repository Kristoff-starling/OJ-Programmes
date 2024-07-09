import re

def NUM_TO_ALPHA(num):
	res=''
	while num!=0:
		cur=num%26
		num//=26
		if cur==0:
			cur=26
			num-=1
		res=chr(ord('A')+cur-1)+res
	return res

def ALPHA_TO_NUM(s):
	res=0
	for c in s:
		res=res*26+(ord(c)-ord('A')+1)
	return res

ca=int(input())
for i in range(ca):
	s=input()
	m=re.match('R(\d+)C(\d+)',s)
	if m is not None:
		print("%s%s" % (NUM_TO_ALPHA(int(m.group(2))),m.group(1)))
	else:
		m=re.match('([A-Z]+)(\d+)',s)
		print('R%sC%d' % (m.group(2),ALPHA_TO_NUM(m.group(1))))