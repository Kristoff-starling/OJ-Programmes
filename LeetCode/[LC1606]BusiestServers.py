from sortedcontainers import SortedList

class Solution:
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:
        idol, busy, request = SortedList(range(k)), [], [0] * k 
        for i, (start, time) in enumerate(zip(arrival, load)):
            while busy and busy[0][0] <= start:
                idol.add(busy[0][1])
                heappop(busy)
            if len(idol) == 0: continue
            index = idol.bisect_left(i % k)
            if index == len(idol): index = 0
            server = idol[index]
            request[server] += 1
            heappush(busy, (start + time, server))
            idol.remove(server)
        maxr = max(request)
        return [i for i in range(k) if request[i] == maxr]