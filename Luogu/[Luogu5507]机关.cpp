#include <bits/stdc++.h>
using namespace std;

/* 状态操作的 helper function
 * 使用位运算记录和修改状态，时间和空间代价都相对较小
 */
inline int getState(int Mask, int pos) { return Mask >> ((pos - 1) << 1) & 3; }
inline int nxtState(int state) {return (state + 1) & 3; }
inline void setState(int &Mask, int pos, int state)
{
    Mask &= ~(3 << ((pos - 1) << 1));
    Mask |= (state << ((pos - 1) << 1));
}

int startState;
int trans[100][10];

double fmap[1 << 24]; int gmap[1 << 24];
bool inq[1 << 24];
pair<int, int> pre[1 << 24];

struct AStarState
{
    int Mask;
    AStarState(int _Mask) { Mask = _Mask; }
    bool operator < (const AStarState &other) const { return fmap[Mask] > fmap[other.Mask]; }
};

/*
 * A-star 算法的估值函数 f = g + h
 * 其中 g 为从初始状态到当前状态的步数
 *     h 为从当前状态到目标状态的估计步数
 * 这里采用的估计步数是理论可能的最小步数: 即距离全 1 状态的步数 / 2 (每次操作可以改变
 * 两个状态)，这保证了最终得到的目标状态步数一定是正确的 (为什么?)
 */
void compute_f(int Mask)
{
    int count = 0;
    for (int i = 1; i <= 12; i++)
    {
        int currentState = getState(Mask, i);
        count += (4 - currentState) % 4;  // currentState -> 0 所需要的步数
    }
    fmap[Mask] = double(count) / 2 + gmap[Mask];
}

priority_queue<AStarState> q;

void AStar()
{
    gmap[startState] = 0; compute_f(startState);
    q.push(AStarState(startState));
    inq[startState] = true;
    int state, relatedState, toState, currentState;
    while (!q.empty())
    {
        currentState = q.top().Mask; // 取出 f 值最小的状态，这是 A* 的核心思想
        q.pop(); inq[currentState] = false;
        if (currentState == 0) break;
        for (int i = 1; i <= 12; i++) // 枚举下一个操作的机关
        {
            state = getState(currentState, i);
            relatedState = getState(currentState, trans[i][state]);
            // 修改操作的机关和关联机关，得到下一个状态
            toState = currentState;
            setState(toState, i, nxtState(state));
            setState(toState, trans[i][state], nxtState(relatedState));
            if (toState == startState) continue;
            /* 注意 A* 和 bfs 的不同点:
             * A* 不能保证第一次搜索到的状态就是最优的，因为它不是按照 g 排序
             * 而是按照 f 排序，因此要检查是否可以更新最小步数。
             */
            if (gmap[toState] == 0 || gmap[toState] > gmap[currentState] + 1)
            {
                gmap[toState] = gmap[currentState] + 1;
                compute_f(toState);
                pre[toState] = make_pair(currentState, i);
                if (!inq[toState])
                {
                    inq[toState] = true;
                    q.push(AStarState(toState));
                }
            }
        }
    }
}

void output(int currentState)
{
    if (currentState == startState) return;
    output(pre[currentState].first);
    printf("%d ", pre[currentState].second);
    if (currentState == 0) puts("");
}

int main ()
{
    int state;
    for (int i = 1; i <= 12; i++)
    {
        scanf("%d", &state);
        setState(startState, i, state - 1);
        for (int j = 0; j <= 3; j++) scanf("%d", &trans[i][j]);
    }
    AStar();
    printf("%d\n", int(gmap[0]));
    output(0);
    return 0;
}