    #include <iostream>
    #include <string>
    #include <vector>
     
    const int kAlphabetSize = 27;
    const int kNoTransition = -1;
    const char kFirstLetter = 'a';
    const char kFinalSymbol = '$';
    const int kRootNode = 0;
    const int kFinalSuffixNode = 1;
    const int kUnsetBorder = -1;
    const int kStartPosition = 0;
     
    int CharToNum(char letter) {
      return (letter == kFinalSymbol) ? 0 : letter - kFirstLetter + 1;
    }
     
    struct Node {
      std::vector<int> to;
      int left;
      int right;
      int parent;
      int link;
      Node() : left(kUnsetBorder), right(kUnsetBorder),
               parent(kRootNode), link(kRootNode) {
        to = std::vector<int>(kAlphabetSize, kNoTransition);
      }
      Node(int left, int right, int parent, int link)
          : left(left), right(right), parent(parent), link(link) {
        to = std::vector<int>(kAlphabetSize, kNoTransition);
      }
    };
     
    class SuffixTree {
     public:
      int GetSize() const { return size_; }
      void Build(std::string& str) {
        string_ = str;
        int current_pos = kStartPosition;
        int current_end = kRootNode;
     
        tree_.emplace_back(kUnsetBorder, kUnsetBorder,
                           kRootNode, kFinalSuffixNode);
        tree_.emplace_back(kUnsetBorder, kUnsetBorder, kRootNode, kRootNode);
        size_ = 2;
     
        for (int i = 0; i < kAlphabetSize; ++i) {
          tree_[kFinalSuffixNode].to[i] = kRootNode;
        }
     
        for (size_t index = 0; index < string_.size(); ++index) {
          Add(index, current_pos, current_end);
        }
      }
     
      void PrintTree(int node_index, int current_parent, int& count) {
        for (int j = 0; j < kAlphabetSize; ++j) {
          if (tree_[node_index].to[j] == kNoTransition) {
            continue;
          }
          std::cout << current_parent << ' ' << tree_[tree_[node_index].to[j]].left
                    << ' ' << tree_[tree_[node_index].to[j]].right + 1 << '\n';
          ++count;
          PrintTree(tree_[node_index].to[j], count, count);
        }
      }
     
     private:
      std::vector<Node> tree_;
      int size_;
      std::string string_;
     
      void AddLeaf(int parent, int letter_index) {
        int letter = CharToNum(string_[letter_index]);
        tree_[parent].to[letter] = size_;
        ++size_;
        tree_.emplace_back(letter_index, string_.size() - 1,
                           parent, kNoTransition);
      }
     
      void Split(int current_end, int current_pos, int letter_index) {
        int letter = CharToNum(string_[letter_index]);
     
        tree_.emplace_back(tree_[current_end].left, current_pos - 1,
                           tree_[current_end].parent, kRootNode);
        tree_.emplace_back(letter_index, string_.size() - 1, size_, kRootNode);
        tree_[size_].to[letter] = size_ + 1;
        tree_[size_].to[CharToNum(string_[current_pos])] = current_end;
        tree_[current_end].left = current_pos;
        tree_[current_end].parent = size_;
        tree_[tree_[size_].parent].to[CharToNum(string_[tree_[size_].left])] =
            size_;
        size_ += 2;
      }
     
      void Add(int letter_index, int& current_pos, int& current_end) {
        int letter = CharToNum(string_[letter_index]);
        while (true) {
          if (tree_[current_end].right < current_pos) {
            if (tree_[current_end].to[letter] == kNoTransition) {
              AddLeaf(current_end, letter_index);
              current_pos = tree_[current_end].right + 1;
              current_end = tree_[current_end].link;
              continue;
            }
            current_end = tree_[current_end].to[letter];
            current_pos = tree_[current_end].left;
          }
          if (current_pos == kUnsetBorder ||
              letter == CharToNum(string_[current_pos])) {
            ++current_pos;
            break;
          }
          Split(current_end, current_pos, letter_index);
          current_end = tree_[tree_[size_ - 2].parent].link;
          current_pos = tree_[size_ - 2].left;
          while (current_pos <= tree_[size_ - 2].right) {
            current_end = tree_[current_end].to[CharToNum(string_[current_pos])];
            current_pos += tree_[current_end].right - tree_[current_end].left + 1;
          }
          tree_[size_ - 2].link =
              (current_pos == tree_[size_ - 2].right + 1) ? current_end : size_;
          current_pos = tree_[current_end].right -
              (current_pos - tree_[size_ - 2].right) + 2;
        }
      }
    };
     
    int main() {
      std::string string;
      std::cin >> string;
     
      SuffixTree tree;
      tree.Build(string);
     
      std::cout << tree.GetSize() - 1 << '\n';
      int count = 0;
      tree.PrintTree(kRootNode, kRootNode, count);
    }
