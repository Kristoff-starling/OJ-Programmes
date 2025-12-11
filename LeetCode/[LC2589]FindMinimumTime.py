class Solution:
    def findMinimumTime(self, tasks: List[List[int]]) -> int:
        durations, task_end = {}, {}
        add_task = {i: [] for i in range(1, 2001)}
        delete_task = {i: [] for i in range(1, 2001)}
        for i, (s, t, d) in enumerate(tasks):
            add_task[s].append(i)
            delete_task[t].append(i)
            durations[i] = d
            task_end[i] = t
        current = [False] * len(tasks)
        ans = 0
        for tick in range(1, 2001):
            for idx in add_task[tick]:
                current[idx] = True
            force = False
            for i in range(len(tasks)):
                if current[i] is True and durations[i] > 0 and task_end[i] - tick + 1 == durations[i]:
                    force = True
                    break
            if force is True:
                ans += 1
                for i in range(len(tasks)):
                    if current[i] is True:
                        durations[i] -= 1
            for idx in delete_task[tick]:
                current[idx] = False
        return ans