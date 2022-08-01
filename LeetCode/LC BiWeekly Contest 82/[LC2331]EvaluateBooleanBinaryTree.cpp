class Solution {
public:
    bool dfs(TreeNode *root)
    {
        if (root->val < 2) return root->val;
        bool val1 = dfs(root->left), val2 = dfs(root->right);
        if (root->val == 2) return (val1 || val2); else return (val1 && val2);
    }
    bool evaluateTree(TreeNode* root) {
        return dfs(root);
    }
};