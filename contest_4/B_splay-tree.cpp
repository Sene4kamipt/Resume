    #include<iostream>
     
    struct node{
    public:
        int64_t value;
        int64_t sum_under;
        node* left_son;
        node* right_son;
        node(int64_t new_element) {
            value = new_element;
            sum_under = new_element;
            right_son = nullptr;
            left_son = nullptr;
        }
        node(node* current){
            value = current->value;
            sum_under = current->sum_under;
            right_son = current->right_son;
            left_son = current->left_son;
        }
    };
    int64_t get_sum_under(node* current){
        if(current == nullptr){
            return 0;
        }
        return current->sum_under;
    }
    node* renew_sum (node* current){
        if(current == nullptr){
            return current;
        }
        current->sum_under = get_sum_under(current->left_son) + get_sum_under(current->right_son) + current->value;
        return current;
    }
    node* zag(node* current){
        if (current == nullptr){
            return current;
        }
        node* new_top = current->right_son;
        current->right_son = new_top->left_son;
        current = renew_sum(current);
        new_top->left_son = current;
        new_top = renew_sum(new_top);
        return new_top;
    }
    node* zig(node* current){
        if(current == nullptr){
            return current;
        }
        node* new_top = current->left_son;
        current->left_son = new_top->right_son;
        current = renew_sum(current);
        new_top->right_son = current;
        new_top = renew_sum(new_top);
        return new_top;
    }
    node* zigzig(node* current){
        if(current == nullptr){
            return current;
        }
        current = zig(current);
        current = zig(current);
        return current;
    }
    node* zagzag(node* current){
        if(current == nullptr){
            return current;
        }
        current = zag(current);
        current = zag(current);
        return current;
    }
    node* zigzag(node* current){
        if(current == nullptr){
            return current;
        }
        current->left_son = zag(current->left_son);
        current = zig(current);
        return current;
    }
    node* zagzig(node* current){
        if(current == nullptr){
            return current;
        }
        current->right_son = zig(current->right_son);
        current = zag(current);
        return current;
    }
     
    node* splay(node* current, int64_t val_to_splay){
        if (current == nullptr || current->value == val_to_splay){
            return current;
        }
        if(current->value > val_to_splay){
            if(current->left_son == nullptr){
                return current;
            }
            if(current->left_son->value > val_to_splay){
                current->left_son->left_son = splay(current->left_son->left_son, val_to_splay);
                current = zigzig(current);
            } else if (current->left_son->value < val_to_splay){
                current->left_son->right_son = splay(current->left_son->right_son, val_to_splay);
                current = zigzag(current);
            } else {
                current = zig(current);
            }
            return current;
        } else {
            if(current->right_son == nullptr){
                return current;
            }
            if(current->right_son->value > val_to_splay){
                current->right_son->left_son = splay(current->right_son->left_son, val_to_splay);
                current = zagzig(current);
            } else if (current->right_son->value < val_to_splay){
                current->right_son->right_son = splay(current->right_son->right_son, val_to_splay);
                current = zagzag(current);
            } else {
                current = zag(current);
            }
            return current;
        }
    }
     
    node* simple_insert(node* current, int64_t new_element){
        if(current == nullptr){
            current = new node(new_element);
            return current;
        }
        if(current->value == new_element) {
            return current;
        }
        if(new_element < current->value){
            current->left_son = simple_insert(current->left_son, new_element);
        } else {
            current->right_son = simple_insert(current->right_son, new_element);
        }
        current = renew_sum(current);
        return current;
    }
    node* insert(node* current, int64_t new_element){
        current = simple_insert(current, new_element);
        current = splay(current, new_element);
        return current;
    }
    int64_t next(node* current, int64_t element){
        if(current == nullptr){
            return -1;
        }
        if(current->value <= element){
            return next(current->right_son, element);
        }
        int64_t possible_answer = next(current->left_son, element);
        if (possible_answer == -1){
            return current->value;
        }
        return std::min(possible_answer, current->value);
    }
    int64_t prev(node* current, int64_t element){
        if(current == nullptr){
            return -1;
        }
        if(current->value >= element){
            return prev(current->left_son, element);
        }
        int64_t possible_answer = prev(current->right_son, element);
        if (possible_answer == -1){
            return current->value;
        }
        return std::max(possible_answer, current->value);
    }
     
    node* find_sum(node* current, int64_t left_bound, int64_t right_bound, int64_t& last_answer){
        if(current == nullptr){
            std::cout<<0<<'\n';
            last_answer = 0;
            return current;
        }
        if(prev(current, right_bound + 1) == -1 ||
           next(current, left_bound - 1) == -1){
            std::cout<<0<<'\n';
            last_answer = 0;
            return current;
        }
        int64_t l_val_to_splay = prev(current, left_bound); // последний строго меньший l
        int64_t r_val_to_splay = next(current, right_bound);
        if(l_val_to_splay == -1 && r_val_to_splay == -1){ // все подходят
            std::cout<<current->sum_under<<'\n';
            last_answer = get_sum_under(current);
            return current;
        }
        if(l_val_to_splay == -1){
            current = splay(current, r_val_to_splay); // все в левом сыне
            std::cout<<get_sum_under(current->left_son)<<'\n';
            last_answer = get_sum_under(current->left_son);
            return current;
        }
        if(r_val_to_splay == -1){
            current = splay(current, l_val_to_splay); // все в правом сыне
            std::cout<<get_sum_under(current->right_son)<<'\n';
            last_answer = get_sum_under(current->right_son);
            return current;
        }
        current = splay(current, l_val_to_splay); // теперь все в правом сыне
        current->right_son = splay(current->right_son, r_val_to_splay);
        std::cout << get_sum_under(current->right_son->left_son)<<'\n';
        last_answer = get_sum_under(current->right_son->left_son);
        return current;
    }
     
    int main(){
        int64_t number_of_requests, left_bound, right_bound, new_element, last_answer;
        node* tree = nullptr;
        char request;
        char last_request = '0';
        std::cin>>number_of_requests;
        for(int64_t i = 0; i<number_of_requests; i++){
            std::cin>>request;
            if(request == '+'){
                std::cin>>new_element;
                if(last_request != '?') {
                    tree = insert(tree, new_element);
                } else {
                    tree = insert(tree, (new_element + last_answer) % 1000000000);
                }
                last_request = '+';
            } else {
                std::cin>>left_bound>>right_bound;
                tree = find_sum(tree, left_bound, right_bound, last_answer);
                last_request = '?';
            }
     
        }
    }


