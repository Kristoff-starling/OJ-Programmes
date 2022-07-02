from queue import PriorityQueue

class Solution:
    def minRefuelStops(self, target: int, startFuel: int, stations: List[List[int]]) -> int:
        ans, cur, ptr = 0, startFuel, 0
        q = PriorityQueue()
        while cur < target:
            while ptr <= len(stations) - 1 and stations[ptr][0] <= cur:
                q.put((-stations[ptr][1], 0))
                ptr += 1
            if q.qsize() == 0: return -1
            ans += 1
            fuel, _ = q.get()
            cur -= fuel
        return ans