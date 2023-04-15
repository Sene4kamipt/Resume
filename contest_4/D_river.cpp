    #include<iostream>
    #include<string>
    #include<fstream>
     
    int64_t square(int64_t value){
        return value * value;
    }
     
    struct node {
    private:
        int64_t value;
        int64_t height;
        int64_t elem_under;
        node *left_son;
        node *right_son;
     
    public:
        node(int64_t new_element) {
            value = new_element;
            height = 1;
            elem_under = 1;
            right_son = nullptr;
            left_son = nullptr;
        }
     
        node(node *element) {
            value = element->value;
            right_son = element->right_son;
            left_son = element->left_son;
            height = element->height;
            elem_under = element->elem_under;
        }
     
        void renew_height() {
            height = 0;
            if (left_son != nullptr) {
                height = left_son->height;
            }
            if (right_son != nullptr) {
                height = std::max(height, right_son->height);
            }
            height += 1;
        }
     
     
        void renew_elem_under() {
            elem_under = 1;
            if (left_son != nullptr) {
                elem_under += left_son->elem_under;
            }
            if (right_son != nullptr) {
                elem_under += right_son->elem_under;
            }
        }
     
        bool is_one_int(int64_t element) {
            return right_son == nullptr && left_son == nullptr && value == element;
        }
     
        void right_rotation() {
            node *new_top = new node(right_son);
            right_son = right_son->left_son;
            renew_height();
            renew_elem_under();
            new_top->left_son = new node(this);
            new_top->renew_height();
            new_top->renew_elem_under();
            *this = new_top;
        }
     
        void left_rotation() {
            node *new_top = new node(left_son);
            left_son = left_son->right_son;
            renew_height();
            renew_elem_under();
            new_top->right_son = new node(this);
            new_top->renew_height();
            new_top->renew_elem_under();
            *this = new_top;
        }
     
        int64_t get_delta() const {
            if (left_son == nullptr && right_son == nullptr) {
                return 0;
            }
            if (left_son == nullptr) {
                return -(right_son->height);
            }
            if (right_son == nullptr) {
                return left_son->height;
            }
            return left_son->height - right_son->height;
        }
     
        void make_balance() {
            if (std::abs(get_delta()) <= 1) {
                return;
            }
            if (get_delta() == -2) {
                if (right_son->get_delta() == 1) {
                    right_son->left_rotation();
                }
                right_rotation();
                return;
            }
            if (get_delta() == 2) {
                if (left_son->get_delta() == -1) {
                    left_son->right_rotation();
                }
                left_rotation();
                return;
            }
        }
     
        void insert(int64_t new_element) {
            if (value == new_element) {
                return;
            }
            if (new_element < value) {
                if (left_son == nullptr) {
                    left_son = new node(new_element);
                } else {
                    left_son->insert(new_element);
                }
            } else {
                if (right_son == nullptr) {
                    right_son = new node(new_element);
                } else {
                    right_son->insert(new_element);
                }
            }
            renew_height();
            renew_elem_under();
            make_balance();
        }
     
        bool find(int64_t& element_to_find) const {
            if (value == element_to_find) {
                return true;
            }
            if (element_to_find < value) {
                if (left_son == nullptr) {
                    return false;
                }
                return left_son->find(element_to_find);
            } else {
                if (right_son == nullptr) {
                    return false;
                }
                return right_son->find(element_to_find);
            }
        }
     
        void erase(int64_t element) {
            if (value == element) {
                if (right_son == nullptr) {
                    *this = new node(left_son);
                    return;
                }
                if (left_son == nullptr) {
                    *this = new node(right_son);
                    return;
                }
                if (right_son->left_son == nullptr) {
                    value = right_son->value;
                    right_son = right_son->right_son;
                    renew_height();
                    renew_elem_under();
                    make_balance();
                    return;
                }
                node *to_move = new node(right_son);
                while (to_move->left_son != nullptr) {
                    to_move = to_move->left_son;
                }
                int64_t key = to_move->value;
                right_son->erase(key);
                renew_height();
                renew_elem_under();
                value = key;
                make_balance();
                return;
            }
            if (!find(element)) {
                return;
            }
            if (element < value) {
                if (left_son == nullptr) {
                    return;
                }
                if (left_son->value == element && left_son->left_son == nullptr && left_son->right_son == nullptr) {
                    left_son = nullptr;
                } else {
                    left_son->erase(element);
                }
                renew_height();
                renew_elem_under();
                make_balance();
                return;
            } else {
                if (right_son == nullptr) {
                    return;
                }
                if (right_son->value == element && right_son->left_son == nullptr && right_son->right_son == nullptr) {
                    right_son = nullptr;
                } else {
                    right_son->erase(element);
                }
                renew_height();
                renew_elem_under();
                make_balance();
                return;
            }
        }
        int64_t find_k_min(int64_t k){
            if(left_son == nullptr) {
                if(k==1) {
                    return value;
                } else {
                    return right_son->find_k_min(k - 1);
                }
            }
            if(left_son->elem_under == k-1){
                return value;
            }
            if(left_son->elem_under >= k){
                return left_son->find_k_min(k);
            }
            return right_son->find_k_min(k - left_son->elem_under - 1);
        }
        int64_t next(int64_t& element) const {
            if(value <= element){
                if(right_son == nullptr){
                    return -1;
                }
                return right_son->next(element);
            }
            if(left_son == nullptr){
                return value;
            }
            int64_t possible_answer = left_son->next(element);
            if (possible_answer == -1){
                return value;
            }
            return std::min(possible_answer, value);
        }
     
        int64_t prev(int64_t& element) const {
            if(element <= value){
                if(left_son == nullptr){
                    return -1;
                }
                return left_son->prev(element);
            }
            if(right_son == nullptr){
                return  value;
            }
            int64_t possible_answer = right_son->prev(element);
            if (possible_answer == -1){
                return value;
            }
            return std::max(possible_answer,value);
        }
     
        int64_t bankrupt(int64_t company, int64_t& river_length){
            int64_t delta_square_sum = 0;
            int64_t company_left_border = find_k_min(company);
            int64_t previous_company_left_border = prev(company_left_border);
            int64_t next_company_left_border = next(company_left_border);
            if(previous_company_left_border != -1 && next_company_left_border != -1){
                int64_t next_company_right_border = next(next_company_left_border);
                if(next_company_right_border == -1){
                    next_company_right_border = river_length;
                }
                delta_square_sum -= square(previous_company_left_border - company_left_border) +
                              square(company_left_border - next_company_left_border)+
                              square(next_company_left_border - next_company_right_border);
                int64_t new_border = (company_left_border+ next_company_left_border)/2;
                delta_square_sum += square(previous_company_left_border - new_border) +
                              square(new_border - next_company_right_border);
                insert(new_border);
                erase(company_left_border);
                erase(next_company_left_border);
                return delta_square_sum;
            }
            if(previous_company_left_border == -1){
                int64_t next_company_right_border = next(next_company_left_border);
                if(next_company_right_border == -1){
                    next_company_right_border = river_length;
                }
                delta_square_sum -= square(company_left_border - next_company_left_border) +
                              square(next_company_left_border - next_company_right_border);
                delta_square_sum += square(company_left_border - next_company_right_border);
                erase(next_company_left_border);
                return delta_square_sum;
            }
            if(next_company_left_border == -1){
                int64_t company_right_border = river_length;
                delta_square_sum -= square(previous_company_left_border - company_left_border) +
                              square(company_left_border - company_right_border);
                delta_square_sum += square(previous_company_left_border - company_right_border);
                erase(company_left_border);
                return delta_square_sum;
            }
        }
     
        int64_t separate(int64_t company, int64_t& river_length){
            int64_t delta_square_sum = 0;
            int64_t company_left_border = find_k_min(company);
            int64_t company_right_border = next(company_left_border);
            if (company_right_border == -1){
                company_right_border = river_length;
            }
            delta_square_sum -= square(company_right_border - company_left_border);
            int64_t new_border = (company_left_border + company_right_border)/2;
            delta_square_sum += square(new_border - company_left_border) + square(company_right_border - new_border);
            insert(new_border);
            return delta_square_sum;
        }
     
    };
     
    struct Tree{
    private:
        node* root;
        int64_t river_length;
        int64_t bankrupt(int64_t company){
            return root->bankrupt(company, river_length);
        }
        int64_t separate(int64_t company){
            return root->separate(company, river_length);
        }
     
    public:
     
        Tree(){
            root = nullptr;
            river_length = 0;
        }
     
        void insert(int64_t new_element){
            if(root == nullptr){
                root = new node(new_element);
                return;
            }
            root->insert(new_element);
        }
        void update_length(int64_t new_length){
            river_length = new_length;
        }
     
        int64_t request(int request_type, int64_t company){
            if (request_type == 1){
                return bankrupt(company);
            } else {
                return separate(company);
            }
        }
    };
     
     
     
    int main(){
        std::ifstream in;
        std::ofstream out;
        in.open("river.in");
        out.open("river.out");
     
        Tree tree;
     
        int64_t number_of_companies, parameter;
        in>>number_of_companies>>parameter;
        int64_t square_sum = 0;
        int64_t current_left_border = 0;
        int64_t length;
        for(int64_t i = 0; i < number_of_companies; ++i){
            tree.insert(current_left_border);
            in>>length;
            current_left_border += length;
            square_sum += length*length;
        }
        out<<square_sum<<'\n';
        tree.update_length(current_left_border);
     
        int64_t number_of_requests;
        in>>number_of_requests;
        int request_type;
        int64_t company;
        for(int64_t i = 0; i< number_of_requests; ++i){
            in>>request_type>>company;
            square_sum += tree.request(request_type, company);
            out<<square_sum<<'\n';
        }
     
    }
