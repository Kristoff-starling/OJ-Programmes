class Solution:
    def stringMatching(self, words: List[str]) -> List[str]:
        ans, n = [], len(words)
        words = sorted(words, key=lambda s: len(s))
        for i in range(n):
            flag = False
            for j in range(i+1, n):
                if words[i] in words[j]: flag = True
            if flag == True: ans.append(words[i])
        return ans