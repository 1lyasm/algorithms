/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

enum Dir {
    Left,
    Right
};

class CBTInserter {
public:
    TreeNode *root;

    CBTInserter(TreeNode* root) {
        this->root = root;
        // std::cout << "this->root->left->val: " << this->root->left->val << "\n";
    }

    int insertLMost(int val) {
        std::cout << "insertLMost: called with val: " << val << "\n";
        auto cur = root;
        auto prev = cur;
        do {
            cur = cur->left;
            if (cur == nullptr) {
                prev->left = new TreeNode(val);
                // std::cout << "insertLMost: made new node with val: " << val << "\n";
                // std::cout << "insertLMost: returning: " << prev->val << "\n";
                return prev->val;
            }
            prev = cur;
        } while (1);
    }

    int insert(int val) {
        vector<TreeNode*> seen;
        auto cur = this->root;
        int dir = Dir::Left;
        do {
            std::cout << "cur->val: " << cur->val << "\n";
            if (cur->left && cur->right) {
                // std::cout << "has both childs\n";
                seen.push_back(cur);
            } else if (!cur->left && !cur->right) {
                // std::cout << "has no childs\n";
                if (seen.size() > 0) {
                    cur = seen.back();
                    seen.pop_back();
                }
                if (seen.size() == 0) {
                    return this->insertLMost(val);
                }
                dir = Dir::Right;
            } else if (!cur->right) {
                // std::cout << "has only left child\n";
                cur->right = new TreeNode(val);
                return cur->val;
            }
             if (dir == Dir::Left) {
                cur = cur->left;
            } else if (dir == Dir::Right) {
                cur = cur->right;
            }
            // std::cout << "\n";
        } while(1);
    }

    TreeNode* get_root() {
        return this->root;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */
