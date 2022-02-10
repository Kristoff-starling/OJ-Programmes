class Solution {
    #define rep(i,a,b) for (int i=(a);i<=(b);i++)
    string tostring(int n)
    {
        string res="";
        while (n)
        {
            res=string(1,n%10+'0')+res;
            n/=10;
        }
        return res;
    }
    int mygcd(int x,int y) {return !y?x:mygcd(y,x%y);}
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> res;res.clear();
        rep(i,2,n) rep(j,1,i-1) if (mygcd(i,j)==1)
            res.push_back(tostring(j)+"/"+tostring(i));
        return res;
    }
};