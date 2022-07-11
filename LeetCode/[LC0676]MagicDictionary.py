class MagicDictionary:

    def __init__(self):
        self.table = {}


    def buildDict(self, dictionary: List[str]) -> None:
        for word in dictionary: self.table[word] = 1

    def search(self, searchWord: str) -> bool:
        for i, ch in enumerate(searchWord):
            for index in range(97, 123):
                if chr(index) != ch:
                    new = searchWord[:i] + chr(index) + searchWord[i+1:]
                    if new in self.table: return True
        return False