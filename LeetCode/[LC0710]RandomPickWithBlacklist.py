class Solution:

    def __init__(self, n: int, blacklist: List[int]):
        self.N = n - len(blacklist)
        small = {i for i in blacklist if i < self.N}
        large = {i for i in range(self.N, n)} - set(blacklist)
        self.mp = dict(zip(small, large))

    def pick(self) -> int:
        r = randint(0, self.N - 1)
        return r if r not in self.mp else self.mp[r]