    #include <iostream>
    #include <utility>
    #include <vector>
    #include <algorithm>
     
     
     
    class Node {
    public:
      long long sum;
      long long tree_left;
      long long tree_right;
      long long left_son = -1;
      long long right_son = -1;
     
      Node(long long sum, long long tree_left, long long tree_right){
          this->sum = sum;
          this->tree_left = tree_left;
          this->tree_right = tree_right;
      }
    };
     
     
    class Tree {
    private:
      std::vector<Node> tree;
     
    public:
      Tree(std::vector<Node> tree) : tree(std::move(tree)) {};
     
     
      void update(long long vertex, long long position, long long value) {
        tree[vertex].sum += value;
        if (tree[vertex].tree_left == tree[vertex].tree_right) {
          return;
        }
        long long tree_middle = (tree[vertex].tree_left + tree[vertex].tree_right) >> 1;
        if (tree[vertex].left_son == -1 && position <= tree_middle) {
          tree.emplace_back(0, tree[vertex].tree_left, tree_middle);
          tree[vertex].left_son = tree.size() - 1;
        }
        if (position <= tree_middle) {
          update(tree[vertex].left_son, position, value);
        }
        if (tree[vertex].right_son == -1 && position > tree_middle) {
          tree.emplace_back(0, tree_middle + 1, tree[vertex].tree_right);
          tree[vertex].right_son = tree.size() - 1;
        }
        if (position > tree_middle) {
          update(tree[vertex].right_son, position, value);
        }
      }
     
     
      long long get_sum(long long vertex, long long left, long long right) {
        if (tree[vertex].tree_left == left && tree[vertex].tree_right == right) {
          return tree[vertex].sum;
        }
        long long tree_middle = (tree[vertex].tree_left + tree[vertex].tree_right) >> 1;
        long long answer = 0;
        if (left <= tree_middle) {
          if (tree[vertex].left_son != -1) {
            answer += get_sum(tree[vertex].left_son, left, std::min(right, tree_middle));
          }
        }
        if (right >= tree_middle + 1) {
          if (tree[vertex].right_son != -1) {
            answer += get_sum(tree[vertex].right_son, std::max(tree_middle + 1, left), right);
          }
        }
        return answer;
      }
    };
     
     
    int main() {
      std::ios::sync_with_stdio(0);
      std::cin.tie(0);
      std::cout.tie(0);
      long long n;
      std::cin >> n;
      Tree tree({Node(0, 0, 999999999)});
      for (long long request = 0; request < n; ++request) {
        char command;
        long long x;
        std::cin >> command >> x;
        if (command == '?') {
          std::cout << tree.get_sum(0, 0, x) << '\n';
        } else {
          tree.update(0, x, x);
        }
      }
    }
