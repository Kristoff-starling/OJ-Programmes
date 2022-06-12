class Solution:
    def findAndReplacePattern(self, words: List[str], pattern: str) -> List[str]:
        return [w for w in words if len(set(w)) == len(set(pattern)) == len(set(zip(w, pattern)))]