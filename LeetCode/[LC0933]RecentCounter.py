class RecentCounter:
    def __init__(self):
        self.q = []
    def ping(self, t: int) -> int:
        self.q.append(t)
        while self.q[0] < t - 3000:
            self.q = self.q[1:]
        return len(self.q)