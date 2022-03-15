class AllOne {
    unordered_map<string,int> mp;
    set<pair<int,string> > s;
public:
    AllOne() {
        mp.clear();
        s.clear();
    }
    
    void inc(string key) {
        int ori=mp[key];
        mp[key]=ori+1;
        if (ori!=0) s.erase(make_pair(ori,key));
        s.insert(make_pair(ori+1,key));
    }
    
    void dec(string key) {
        int ori=mp[key];
        mp[key]=ori-1;
        s.erase(make_pair(ori,key));
        if (ori!=1) s.insert(make_pair(ori-1,key));
    }
    
    string getMaxKey() {
        if (s.empty()) return ""; else return s.rbegin()->second;
    }
    
    string getMinKey() {
        if (s.empty()) return ""; else return s.begin()->second;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */