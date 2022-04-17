class Solution:
    def mostCommonWord(self, paragraph: str, banned: List[str]) -> str:
        count, word = Counter(), ""
        for ch in paragraph + " ":
            if ch.isalpha(): word += ch.lower()
            else:
                if word != "" and not word in banned: count[word] += 1
                word = ""
        maxn = max(count.values())
        return next(word for word, cnt in count.items() if cnt == maxn)