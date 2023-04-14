    #include<iostream>
    #include <algorithm>
    using std::max;
    static const int deleted = 1000000001;
    struct Node {
    public:
        int key;
        unsigned short int height = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        long long Number_of_nodes = 0;
        Node(int key) : key(key) {};
    };
    int maximum(Node* x) {
        if (x == nullptr) return -deleted;
        if ((x->right != nullptr) && (x->right->key != deleted)) return maximum(x->right);
        return x->key;
    }
    int minimum(Node* x) {
        if (x == nullptr) return deleted;
        if ((x->left != nullptr) && (x->left->key != deleted)) return minimum(x->left);
        return x->key;
    }
    unsigned short int h(Node* x) {
        if ((x == nullptr) or (x->key == deleted)) return 0;
        return x->height;
    }
    int balance(Node* x) {
        if (x == nullptr or x->key == deleted) return 0;
        return h(x->left) - h(x->right);
    }
    Node* rightRotate(Node* x) {
        Node* b = x->left;
        Node* c = b->right;
        b->right = x;
        x->left = c;
        x->height = max(h(x->right), h(x->left)) + 1;
        b->height = max(h(b->right), h(b->left)) + 1;
        x->Number_of_nodes = 0;
        if (x->left != nullptr) {
            x->Number_of_nodes += x->left->Number_of_nodes+1;
        }
        if (x->right != nullptr) {
            x->Number_of_nodes += x->right->Number_of_nodes+1;
        }
        b->Number_of_nodes = 0;
        if (b->left != nullptr) {
            b->Number_of_nodes += b->left->Number_of_nodes+1;
        }
        if (b->right != nullptr) {
            b->Number_of_nodes += b->right->Number_of_nodes+1;
        }
        return b;
    }
    Node* leftRotate(Node* x) {
        Node* b = x->right;
        Node* c = b->left;
        b->left = x;
        x->right = c;
        x->height = max(h(x->right), h(x->left)) + 1;
        b->height = max(h(b->right), h(b->left)) + 1;
        x->Number_of_nodes = 0;
        if (x->left != nullptr) {
            x->Number_of_nodes += x->left->Number_of_nodes+1;
        }
        if (x->right != nullptr) {
            x->Number_of_nodes += x->right->Number_of_nodes+1;
        }
        b->Number_of_nodes = 0;
        if (b->left != nullptr) {
            b->Number_of_nodes += b->left->Number_of_nodes+1;
        }
        if (b->right != nullptr) {
            b->Number_of_nodes += b->right->Number_of_nodes+1;
        }
        return b;
    }
    Node* bigRightRotate(Node* x) {
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    Node* bigLeftRotate(Node* x) {
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    Node* getBalancedForInsert(Node* x, int newKey) {
        if (balance(x) > 1 and newKey < x->left->key)
            return rightRotate(x);
        if (balance(x) < -1 and newKey > x->right->key)
            return leftRotate(x);
        if (balance(x) > 1 and newKey > x->left->key)
            return bigRightRotate(x);
        if (balance(x) < -1 and newKey < x->right->key)
            return bigLeftRotate(x);
        return x;
    }
    Node* getBalancedForErase(Node* x) {
        if (balance(x) > 1 and balance(x->left) >= 0)
            return rightRotate(x);
        if (balance(x) > 1 and balance(x->left) < 0)
            return bigRightRotate(x);
        if (balance(x) < -1 and balance(x->right) <= 0)
            return leftRotate(x);
        if (balance(x) < -1 and balance(x->right) > 0)
            return bigLeftRotate(x);
        return x;
    }
    Node* insert(Node* x,  int newKey) {
        if (x == nullptr or x->key == deleted) {
            return new Node(newKey);
        }
        if (newKey < x->key) {
            x->Number_of_nodes += 1;
            x->left = insert(x->left, newKey);
        }
        else if (newKey > x->key) {
            x->Number_of_nodes += 1;
            x->right = insert(x->right, newKey);
        }
        else return x;
        x->height = max(h(x->right), h(x->left)) + 1;
        return getBalancedForInsert(x, newKey);
    }
    int prevForRoot(Node* x) {
        if (x->left == nullptr or x->left->key == deleted) return -deleted;
        return maximum(x->left);
    }
    Node* erase(Node* x, int delKey) {
        if (x == nullptr or x->key == deleted) return x;
        if (delKey < x->key) {
            x->Number_of_nodes -= 1;
            x->left = erase(x->left, delKey);
        }
        else {
            if (delKey > x->key) {
                x->Number_of_nodes -= 1;
                x->right = erase(x->right, delKey);
            }
            else {
                if (x->left == nullptr or x->right == nullptr or x->left->key == deleted or x->right->key == deleted) {
                    if ((x->left == nullptr or x->left->key == deleted) and (x->right == nullptr or x->right->key == deleted))
                        x = nullptr;
                    else { *x = ((x->left == nullptr or x->left->key == deleted) ? *(x->right) : *(x->left)); }
                }
                else {
                    x->key = prevForRoot(x);
                    x->Number_of_nodes -= 1;
                    x->left = erase(x->left, x->key);
                }
            }
        }
        if (x == nullptr or x->key == deleted) return x;
        x->height = 1 + max(h(x->left), h(x->right));
        return getBalancedForErase(x);
    }
     
    long long find_max(Node* x, int point) {
        //std::cout << "key = " << x->key << "number of nodes=" << x->Number_of_nodes;
        if ((x->right == nullptr?-1: x->right->Number_of_nodes) + 2 == point) {
            return x->key;
        }
        else {
            if (point>(x->right==nullptr?-1:x->right->Number_of_nodes)+1) {
                return find_max(x->left, point - (x->right==nullptr?-1:x->right->Number_of_nodes)- 2);
            }
            else {
                return find_max(x->right, point);
            }
        }
    }
     
    int main() {
        long long number_of_itterations, x;
        int input;
        std::cin >> number_of_itterations;
        Node* avl = nullptr;
        for (long long i=0;i<number_of_itterations;++i) {
            std::cin >> x;
            if (x == 1) {
                std::cin >> input;
                avl = insert(avl, input);
            }
            if (x == -1) {
                std::cin >> input;
                avl = erase(avl, input);
            }
            if (x == 0) {
                std::cin >> input;
                std::cout<<find_max(avl, input)<<'\n';
            }
        }
    }
