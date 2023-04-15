    #include<iostream>
    #include<set>
    #include<map>
    #include<string>
     
    struct Multiset{
        std::map <int, std::set<int64_t>> set_to_elements;
        std::map <int64_t, std::set<int>> element_to_sets;
        Multiset() = default;
        void add (int64_t element, int set_number){
            if(set_to_elements.find(set_number) == set_to_elements.end()){
                set_to_elements.insert(std::pair<int, std::set<int64_t>>(set_number, {element}));
            } else {
                set_to_elements.find(set_number)->second.insert(element);
            }
            if(element_to_sets.find(element) == element_to_sets.end()){
                element_to_sets.insert(std::pair<int64_t, std::set<int>>(element, {set_number}));
            } else {
                element_to_sets.find(element)->second.insert(set_number);
            }
        }
        void erase (int64_t element, int set_number){
            set_to_elements.find(set_number)->second.erase(element);
            element_to_sets.find(element)->second.erase(set_number);
        }
        void clear(int set_number){
            if (set_to_elements.find(set_number) == set_to_elements.end() ||
            set_to_elements.find(set_number)->second.empty()){
                return;
            }
            for(int64_t it : set_to_elements.find(set_number)->second){
                element_to_sets.find(it)->second.erase(set_number);
            }
            set_to_elements.erase(set_to_elements.find(set_number));
        }
        void listset(int set_number){
            if(set_to_elements.find(set_number) == set_to_elements.end() ||
            set_to_elements.find(set_number)->second.empty()){
                std::cout<<"-1"<<'\n';
                return;
            }
            for(int64_t it : set_to_elements.find(set_number)->second){
                std::cout<<it<<' ';
            }
            std::cout<<'\n';
        }
        void listsetof(int64_t element){
            if(element_to_sets.find(element) == element_to_sets.end() ||
                    element_to_sets.find(element)->second.empty()){
                std::cout<<"-1"<<'\n';
                return;
            }
            for(int it : element_to_sets.find(element)->second){
                std::cout<<it<<' ';
            }
            std::cout<<'\n';
        }
        void request(std::string& question){
            int64_t element;
            int set_number;
            if(question == "ADD"){
                std::cin>>element>>set_number;
                add(element, set_number);
                return;
            }
            if(question == "DELETE"){
                std::cin>>element>>set_number;
                erase(element, set_number);
                return;
            }
            if(question == "CLEAR"){
                std::cin>>set_number;
                clear(set_number);
                return;
            }
            if (question == "LISTSET"){
                std::cin>>set_number;
                listset(set_number);
                return;
            }
            if (question == "LISTSETSOF"){
                std::cin>>element;
                listsetof(element);
                return;
            }
        }
    };
    int main(){
        int64_t n, m, k;
        std::string question;
        std::cin>>n>>m>>k;
        Multiset multiset;
        for(int64_t i = 0; i<k; ++i){
            std::cin >> question;
            multiset.request(question);
        }
    }


