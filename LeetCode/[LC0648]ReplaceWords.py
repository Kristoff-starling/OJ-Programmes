class Solution:
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        rootset = {}
        def hashword(s: str):
            h = 0
            for ch in s:
                h = (h * 19260817 + ord(ch)) % 1919191919191919
            return h
        for word in dictionary: rootset[hashword(word)] = 1
        words, ans = sentence.split(' '), []
        for word in words:
            h, flag = 0, False
            for i, ch in enumerate(word):
                h = (h * 19260817 + ord(ch)) % 1919191919191919
                if h in rootset:
                    flag = True
                    ans.append(word[:i+1])
                    break
            if flag is False: ans.append(word)
        return ' '.join(ans)