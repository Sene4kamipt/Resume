    #include <iostream>
    #include <vector>
    #include <string>
    #include <queue>
    struct Node{
        int to[26];
        std::vector<int> number_of_terms = std::vector<int>();
        Node(){
            for(int i=0;i<26;++i){
                to[i]=-1;
            }
        }
    };
     
    struct Bor{
    public:    
        std::vector<Node> tree = std::vector<Node>(1, Node());
        std::vector<int> link = std::vector<int>(1,0);
        std::vector<std::vector<int>> go = std::vector<std::vector<int>>(1,std::vector<int>(26,0));
        void add_word(std::string& str, int number){
            int curr_vertex = 0;
            for (int i=0;i<str.size();++i){
                if (this->tree[curr_vertex].to[str[i]-'a'] != -1){
                    curr_vertex = this->tree[curr_vertex].to[str[i]-'a'];
                }
                else{
                    tree.emplace_back(Node());
                    this->tree[curr_vertex].to[str[i]-'a'] = tree.size()-1;
                    //tree[tree.size()-1].number_of_terms = tree[curr_vertex].number_of_terms;
                    curr_vertex = tree.size()-1;
                    link.emplace_back(0);
                    go.emplace_back(std::vector<int>(26,0));
                }
                if (i==str.size()-1){
                    tree[curr_vertex].number_of_terms.push_back(number);
                }
            }
        }
     
        void make_links_and_goes (){
            std::queue<int> que;
            que.push(0);
            for (int j=0;j<26;++j){
                if (tree[0].to[j]!=-1){
                    go[0][j]=tree[0].to[j];
                }
            }
            while (!que.empty()){
                int current_vertex = que.front();
                que.pop();
                for (int i=0;i<26;++i){
                    if (tree[current_vertex].to[i]==-1){
                        continue;
                    }
                    int new_vertex = tree[current_vertex].to[i];
                    que.push(new_vertex);
                    link[new_vertex] = (current_vertex==0?0:go[link[current_vertex]][i]);
                    for (int j=0; j<26;++j){
                        if (tree[new_vertex].to[j] !=-1){
                            go[new_vertex][j] = tree[new_vertex].to[j];
                        }
                        else{
                            go[new_vertex][j] = go[link[new_vertex]][j];
                        }
                    }
                }
            }
        }
     
        void set_terms (){
            std::queue<int> que;
            que.push(0);
            while (!que.empty()){
                int curr_vertex = que.front();
                que.pop();
                for (int i=0;i<26;++i){
                    if (tree[curr_vertex].to[i]==-1){
                        continue;
                    }
                    int new_vertex = tree[curr_vertex].to[i];
                    que.push(new_vertex);
                    if (tree[new_vertex].number_of_terms.size()==0){
                        tree[new_vertex].number_of_terms = tree[link[new_vertex]].number_of_terms;
                    }
                    else{
                        for(int q=0;q<tree[link[new_vertex]].number_of_terms.size();++q){
                            tree[new_vertex].number_of_terms.push_back(tree[link[new_vertex]].number_of_terms[q]);
                        }
     
                    }   
                }
            }
        }
    };
     
     
    int main(){
        std::string text; std::string word;
        std::cin>>text;
        int number_of_words;
        std::cin>>number_of_words;
        Bor bor = Bor();
        std::vector<std::string> words(number_of_words);
        for (int i=0;i<number_of_words;++i){
            std::cin>>word;
            bor.add_word(word, i);
            words[i]=word;
        }
        bor.make_links_and_goes();
        std::vector<std::vector<int>> answer(number_of_words);
        bor.set_terms();
        int v=0;
        for (int i=0;i<text.size();++i){
            v=bor.go[v][text[i] - 'a'];
            for (int j=0;j<bor.tree[v].number_of_terms.size();++j){
                answer[bor.tree[v].number_of_terms[j]].push_back(2+i-words[bor.tree[v].number_of_terms[j]].size());
            }
        }
        for (int i=0;i<answer.size();++i){
            std::cout<<answer[i].size()<<" ";
            for (int j=0;j<answer[i].size();++j){
                std::cout<<answer[i][j]<<" ";
            }        
            std::cout<<'\n';
        }
    }
