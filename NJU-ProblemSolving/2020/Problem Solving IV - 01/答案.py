alphabet = [chr(ch) for ch in range(ord('a'), ord('z')+1)] + [chr(ch) for ch in range(ord('A'), ord('Z')+1)]
vowel = ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']
str = input()

def calc(str, frac):
    chcnt = 0
    for ch in alphabet:
        chcnt += str.count(ch)
    currentch = 0; loc = 0; endloc = 0; ans = ""
    lim = round(chcnt * 1.0 * frac)
    for ch in str:
        if currentch == lim and endloc == 0:
            endloc = loc
        if ch in alphabet:
            currentch += 1
        loc += 1
        if (ch in alphabet) and (currentch > lim):
            ans += "."
        else:
            ans += ch
    return ans, endloc

ans1 = str
for ch in alphabet:
    ans1 = ans1.replace(ch, '.')
print(ans1)

ans2, endloc = calc(str, 1.0 / 3)
print(ans2)

leftover = str[endloc::]
if not (set(leftover) & set(vowel)):
    ans3, endloc = calc(str, 2.0 / 3)
    print(ans3)
else:
    for ch in set(alphabet) - set(vowel):
        leftover = leftover.replace(ch, '.')
    print(ans2[0:endloc:] + leftover)