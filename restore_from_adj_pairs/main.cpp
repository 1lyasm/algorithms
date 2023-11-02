class Solution {
public:
    void print_vec(char *msg, vector<int> &vec) {
        std::cout << msg << "\n";
        for (const auto &item: vec) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }

    void print_map(char *msg, map<int, pair<int, int>> &map_) {
        std::cout << msg << ": \n";
        for (auto it = map_.begin(); it != map_.end(); ++it) {
            std::cout << "\t" << it->first << ": {" << it->second.first << ", "
                << it->second.second << "}\n";
        }
        std::cout << "\n";
    }

    void print_n_item_counts(char *msg, map<int, int> &map_) {
        std::cout << msg << ": \n";
        for (auto it = map_.begin(); it != map_.end(); ++it) {
            std::cout << "\t" << it->first << ": " << it->second << "\n";
        }
        std::cout << "\n";
    }

    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, pair<int, int>> positions;
        // print_map("positions", positions);

        unsigned n = adjacentPairs.size() + 1;
        // vector<int> n_item_counts = vector(n - 1, 0);
        map<int, int> n_item_counts;

        for (unsigned i = 0; i < n - 1; ++i) {
            int val_1 = adjacentPairs[i][0];
            int val_2 = adjacentPairs[i][1];
            if (n_item_counts.find(val_1) == n_item_counts.end()) {
                n_item_counts[val_1] = 0;
            }
            if (n_item_counts.find(val_2) == n_item_counts.end()) {
                n_item_counts[val_2] = 0;
            }
        }

        // print_n_item_counts("n_item_counts", n_item_counts);

        for (unsigned i = 0; i < n - 1; ++i) {
            int val_1 = adjacentPairs[i][0];
            int val_2 = adjacentPairs[i][1];
            vector<int> vals{val_1, val_2};
            for (const auto &val : vals) {
                // std::cout << "val: " << val << "\n";
                if (n_item_counts[val] == 0) {
                    // std::cout << "inserting 1. position";
                    positions[val] = {i, -1};
                    ++n_item_counts[val];
                } else if (n_item_counts[val] == 1) {
                    positions[val].second = i;
                    ++n_item_counts[val];
                } else if (n_item_counts[val] == 2) {
                    std::cout << "unreachable\n";
                    exit(EXIT_FAILURE);
                } else {
                    std::cout << "unreachable\n";
                    exit(EXIT_FAILURE);
                }
                // std::cout << "\n\n";
            }
        }

        // print_map("positions", positions);

        deque<int> nums = {adjacentPairs[0][0], adjacentPairs[0][1]};
        // print_vec("nums", nums);

        unsigned lmost = 0;
        unsigned rmost = 1;

        for (;;) {
            // std::cout << "finding left neb\n";

            // std::cout << "nums[lmost]: " << nums[lmost] << "\n";
            pair<int, int> nebs = positions[nums[lmost]];
            // std::cout << "left nebs: {" << nebs.first << ", " << nebs.second << "}" << "\n";

            vector<int> adj_pair;
            int neb_0;
            int neb_1;
            if (nebs.first >= 0) {
                adj_pair = adjacentPairs[nebs.first];
                if (adj_pair[0] == nums[lmost]) {
                    neb_0 = adj_pair[1];
                } else if (adj_pair[1] == nums[lmost]) {
                    neb_0 = adj_pair[0];
                }
            }

            if (nebs.second >= 0) {
                adj_pair = adjacentPairs[nebs.second];
                if (adj_pair[0] == nums[lmost]) {
                    neb_1 = adj_pair[1];
                } else if (adj_pair[1] == nums[lmost]) {
                    neb_1 = adj_pair[0];
                }
            }

            // std::cout << "adding to left side\n";
            if (nebs.first >= 0 && nebs.second >= 0) {
                if (nums[lmost + 1] == neb_0) {
                    nums.push_front(neb_1);
                    ++rmost;
                } else if (nums[lmost + 1] == neb_1) {
                    nums.push_front(neb_0);
                    ++rmost;
                }
            }

            if (rmost == n - 1) {
                break;
            }

            // std::cout << "finding right neb\n";

            nebs = positions[nums[rmost]];

            // std::cout << "right nebs: {" << nebs.first << ", " << nebs.second << "}" << "\n";
            if (nebs.first >= 0) {
                adj_pair = adjacentPairs[nebs.first];
                if (adj_pair[0] == nums[rmost]) {
                    neb_0 = adj_pair[1];
                } else if (adj_pair[1] == nums[rmost]) {
                    neb_0 = adj_pair[0];
                }
            }

            if (nebs.second >= 0) {
                adj_pair = adjacentPairs[nebs.second];
                if (adj_pair[0] == nums[rmost]) {
                    neb_1 = adj_pair[1];
                } else if (adj_pair[1] == nums[rmost]) {
                    neb_1 = adj_pair[0];
                }
            }

            // std::cout << "adding to right side\n";
            if (nebs.first >= 0 && nebs.second >= 0) {
                if (nums[rmost - 1] == neb_0) {
                    nums.push_back(neb_1);
                    ++rmost;
                } else if (nums[rmost - 1] == neb_1) {
                    nums.push_back(neb_0);
                    ++rmost;
                }
            }

            if (rmost == n - 1) {
                break;
            }

            // print_vec("nums", nums);
            // std::cout << "\n\n";
        }

        vector<int> res;
        res.reserve(n);
        for (const auto &item: nums) {
            res.push_back(item);
        }

        return res;
    }
};
