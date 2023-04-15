#include<iostream>
#include<string>
 
struct node {
private:
    int value;
    int height;
    node* left_son;
    node* right_son;
 
public:
    node(int new_element) {
        value = new_element;
        height = 1;
        right_son = nullptr;
        left_son = nullptr;
    }
    node(node* element){
        value = element->value;
        right_son = element->right_son;
        left_son = element->left_son;
        height = element->height;
    }
 
    void renew_height() {
        height = 0;
        if(left_son != nullptr){
            height = left_son->height;
        }
        if(right_son != nullptr){
            height = std::max(height, right_son->height);
        }
        height += 1;
    }
 
    bool is_one_int(int element){
        return right_son == nullptr && left_son == nullptr && value == element;
    }
 
    void right_rotation(){
        node* new_top = new node(right_son);
        right_son = right_son->left_son;
        renew_height();
        new_top->left_son = new node(this);
        new_top->renew_height();
        *this = new_top;
    }
    void left_rotation(){
        node* new_top = new node(left_son);
        left_son = left_son->right_son;
        renew_height();
        new_top->right_son = new node(this);
        new_top->renew_height();
        *this = new_top;
    }
 
    int get_delta() const {
        if(left_son == nullptr && right_son == nullptr){
            return 0;
        }
        if(left_son == nullptr){
            return -(right_son->height);
        }
        if(right_son == nullptr){
            return left_son->height;
        }
        return left_son->height - right_son->height;
    }
    void make_balance(){
        if(std::abs(get_delta())<=1){
            return;
        }
        if(get_delta() == -2){
            if(right_son->get_delta() == 1) {
                right_son->left_rotation();
            }
            right_rotation();
            return;
        }
        if(get_delta() == 2){
            if(left_son->get_delta() == -1) {
                left_son->right_rotation();
            }
            left_rotation();
            return;
        }
    }
    void insert(int new_element){
        if(value == new_element) {
            return;
        }
        if(new_element < value){
            if(left_son == nullptr){
                left_son = new node(new_element);
            } else {
                left_son->insert(new_element);
            }
        } else {
            if(right_son == nullptr){
                right_son = new node(new_element);
            } else {
                right_son->insert(new_element);
            }
        }
        renew_height();
        make_balance();
    }
 
    bool find(int& element_to_find) const {
        if(value == element_to_find){
            return true;
        }
        if(element_to_find < value){
            if(left_son == nullptr){
                return false;
            }
            return left_son->find(element_to_find);
        } else {
            if(right_son == nullptr){
                return false;
            }
            return right_son->find(element_to_find);
        }
    }
    void erase(int element){
        if (value == element) {
            if(right_son == nullptr){
                *this = new node(left_son);
                return;
            }
            if(left_son == nullptr){
                *this = new node(right_son);
                return;
            }
            if(right_son->left_son == nullptr){
                value = right_son->value;
                right_son = right_son->right_son;
                renew_height();
                make_balance();
                return;
            }
            node* to_move = new node(right_son);
            while(to_move->left_son != nullptr){
                to_move = to_move->left_son;
            }
            int key = to_move->value;
            right_son->erase(key);
            renew_height();
            value = key;
            make_balance();
            return;
        }
        if (!find(element)){
            return;
        }
        if (element < value) {
            if(left_son == nullptr){
                return;
            }
            if(left_son->value == element && left_son->left_son == nullptr && left_son->right_son == nullptr){
                left_son = nullptr;
            } else {
                left_son->erase(element);
            }
            renew_height();
            make_balance();
            return;
        } else {
            if(right_son == nullptr){
                return;
            }
            if(right_son->value == element && right_son->left_son == nullptr && right_son->right_son == nullptr){
                right_son = nullptr;
            } else {
                right_son->erase(element);
            }
            renew_height();
            make_balance();
            return;
        }
    }
 
    int next(int& element) const {
        if(value <= element){
            if(right_son == nullptr){
                return INT_MIN;
            }
            return right_son->next(element);
        }
        if(left_son == nullptr){
            return value;
        }
        int possible_answer = left_son->next(element);
        if (possible_answer == INT_MIN){
            return value;
        }
        return std::min(possible_answer, value);
    }
 
    int prev(int& element) const {
        if(element <= value){
            if(left_son == nullptr){
                return INT_MAX;
            }
            return left_son->prev(element);
        }
        if(right_son == nullptr){
            return  value;
        }
        int possible_answer = right_son->prev(element);
        if (possible_answer == INT_MAX){
            return value;
        }
        return std::max(possible_answer,value);
    }
};
 
struct Tree{
private:
    node* root;
    void insert(int new_element){
        if(root == nullptr){
            root = new node(new_element);
            return;
        }
        root->insert(new_element);
    }
    bool find(int& elem_to_find){
        if (root == nullptr){
            return false;
        }
        return root->find(elem_to_find);
    }
    void erase(int element){
        if(root == nullptr){
            return;
        }
        if(root->is_one_int(element)){
            root = nullptr;
            return;
        }
        root->erase(element);
    }
    int next(int& element){
        if(root == nullptr){
            return INT_MIN;
        }
        return root->next(element);
    }
    int prev(int& element){
        if(root == nullptr){
            return INT_MAX;
        }
        return root->prev(element);
    }
 
public:
 
    Tree(){
        root = nullptr;
    }
    void request(std::string& question, int& element){
        if(question == "insert"){
            insert(element);
            return;
        }
        if(question == "exists"){
            if(find(element)){
                std::cout<<"true"<<'\n';
            } else {
                std::cout<<"false"<<'\n';
            }
            return;
        }
        if(question == "delete"){
            erase(element);
            return;
        }
        if(question == "prev"){
            int answer = prev(element);
            if(answer == INT_MAX){
                std::cout<<"none"<<'\n';
            } else {
                std::cout<<answer<<'\n';
            }
            return;
        }
        if(question == "next"){
            int answer = next(element);
            if(answer == INT_MIN){
                std::cout<<"none"<<'\n';
            } else {
                std::cout<<answer<<'\n';
            }
            return;
        }
    }
};
 
int main(){
    std::string question;
    int value;
    Tree tree;
    while(std::cin >> question){
        std::cin >> value;
        tree.request(question, value);
    }
}
