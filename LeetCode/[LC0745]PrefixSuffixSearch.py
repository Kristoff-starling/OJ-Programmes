class WordFilter:

    def __init__(self, words: List[str]):
        table = {}
        for i, word in enumerate(words):
            for j in range(0, len(word) + 1):
                for k in range(0, len(word) + 1):
                    table[(word[:j], word[k:])] = i
        self.table = table


    def f(self, pref: str, suff: str) -> int:
        return self.table.get((pref, suff), -1)