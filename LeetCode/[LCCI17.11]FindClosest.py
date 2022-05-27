class Solution:
    def findClosest(self, words: List[str], word1: str, word2: str) -> int:
        pos, n, ans = 0, len(words), 200000
        for i, word in enumerate(words):
            if word == word1:
                pos = max(pos, i + 1)
                while pos < n and words[pos] != word2: pos += 1
                if pos < n: ans = min(ans, pos - i)
        pos = 0
        for i, word in enumerate(words):
            if word == word2:
                pos = max(pos, i + 1)
                while pos < n and words[pos] != word1: pos += 1
                if pos < n: ans = min(ans, pos - i)
        return ans