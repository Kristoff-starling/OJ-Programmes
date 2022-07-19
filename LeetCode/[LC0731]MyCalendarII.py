from sortedcontainers import SortedDict

class MyCalendarTwo:

    def __init__(self):
        self.table = SortedDict()

    def book(self, start: int, end: int) -> bool:
        self.table[start] = self.table.get(start, 0) + 1
        self.table[end] = self.table.get(end, 0) - 1
        cnt = 0
        for date in self.table.keys():
            cnt += self.table[date]
            if cnt > 2:
                self.table[start] -= 1
                self.table[end] += 1
                return False
        return True