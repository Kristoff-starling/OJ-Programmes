class RandomizedSet:
    def __init__(self):
        self.pool = {}
    def insert(self, val: int) -> bool:
        if val in self.pool: return False
        self.pool[val] = 1
        return True
    def remove(self, val: int) -> bool:
        if not val in self.pool: return False
        del self.pool[val]
        return True
    def getRandom(self) -> int:
        return random.sample(self.pool.keys(), 1)[0]