#include "binary_tree_codec.h"

#include <deque>
#include <string>
#include <vector>

struct Codec {
  int nullValue = 1001;
  void push_as_chars(std::string &buf, int value) {
    buf.push_back(static_cast<char>(value >> 8));
    buf.push_back(static_cast<char>(value));
  }

  int chars_to_int(std::string &s, std::string::size_type ind) {
    uint8_t upper = s[2 * ind], lower = s[2 * ind + 1];
    return static_cast<int>(static_cast<int16_t>((upper << 8)) | lower);
  }

  std::string serialize(TreeNode *root) {
    if (root == nullptr) {
      return "";
    }
    std::string buf;
    push_as_chars(buf, root->val);
    std::vector<TreeNode *> stack = {root};
    std::vector<TreeNode *>::size_type parent_ind = 0;
    while (parent_ind < stack.size()) {
      if (stack[parent_ind] != nullptr) {
        stack.push_back(stack[parent_ind]->left);
        stack.push_back(stack[parent_ind]->right);
        if (stack[parent_ind]->left != nullptr) {
          push_as_chars(buf, stack[parent_ind]->left->val);
        } else {
          push_as_chars(buf, Codec::nullValue);
        }
        if (stack[parent_ind]->right != nullptr) {
          push_as_chars(buf, stack[parent_ind]->right->val);
        } else {
          push_as_chars(buf, Codec::nullValue);
        }
      }
      parent_ind++;
    }
    return buf;
  }

  TreeNode *deserialize(std::string data) {
    if (data.empty()) {
      return nullptr;
    }
    std::string buf = data;
    std::string::size_type data_size = buf.size() / 2;
    std::string::size_type child_ind = 1;
    TreeNode *root = new TreeNode(chars_to_int(buf, 0));
    std::deque<TreeNode *> parents{root};
    while (child_ind < data_size) {
      if (chars_to_int(buf, child_ind) == Codec::nullValue) {
        parents.front()->left = nullptr;
      } else {
        parents.front()->left = new TreeNode(chars_to_int(buf, child_ind));
        parents.push_back(parents.front()->left);
      }
      ++child_ind;
      if (chars_to_int(buf, child_ind) == Codec::nullValue) {
        parents.front()->right = nullptr;
      } else {
        parents.front()->right = new TreeNode(chars_to_int(buf, child_ind));
        parents.push_back(parents.front()->right);
      }
      ++child_ind;
      parents.pop_front();
    }
    return root;
  }
};
