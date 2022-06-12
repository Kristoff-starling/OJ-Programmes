class DiscountSystem {
    struct node {
        int actId, priceLimit, discount, number, userLimit;
    }a[2048];
    int n, history[2001][2001];
public:
    DiscountSystem() {
        n = 0;
    }
    
    void addActivity(int actId, int priceLimit, int discount, int number, int userLimit) {
        a[++n] = (struct node){.actId = actId, .priceLimit = priceLimit, .discount = discount, .number = number, .userLimit = userLimit};
    }
    
    void removeActivity(int actId) {
        for (int i = 1; i <= n; i++) if (a[i].actId == actId) a[i].actId = -1;
    }
    
    int consume(int userId, int cost) {
        int maxdiscount = 0, id = 0;
        for (int i = 1; i <= n; i++)
            if (a[i].actId >= 0 && cost >= a[i].priceLimit && a[i].number > 0 && history[userId][a[i].actId] < a[i].userLimit)
                if (a[i].discount > maxdiscount)
                    maxdiscount = a[i].discount, id = i;
        if (id == 0) return cost;
        history[userId][a[id].actId]++;
        a[id].number--;
        return cost - maxdiscount;
    }
};