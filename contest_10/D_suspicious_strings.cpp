    #include <iostream>
    #include <vector>
    #include <string>
    #include <queue>
    #include <unordered_set>
    struct Node{
        int to[26];
        bool term = false;
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
        std::vector<int> comp_links = std::vector<int>(1,0);
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
                    comp_links.push_back(0);
                    go.emplace_back(std::vector<int>(26,0));
                }
                if (i==str.size()-1){
                    tree[curr_vertex].term = true;
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
                    comp_links[new_vertex] = (tree[link[new_vertex]].term?link[new_vertex]:comp_links[link[new_vertex]]);
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
     
        /*void set_terms (){
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
        }*/
    };
     
     
    int main(){
        std::string word;
        int number_of_words, length_of_words;
        std::cin>>length_of_words>>number_of_words;
        Bor bor = Bor();
        for (int i=0;i<number_of_words;++i){
            std::cin>>word;
            bor.add_word(word, i);
        }
        bor.make_links_and_goes();
        std::vector<std::vector<int>> suspicious_words = std::vector<std::vector<int>>(length_of_words+1,std::vector<int>(bor.tree.size(),0));
        std::vector<std::vector<int>> not_suspicious_words = std::vector<std::vector<int>>(length_of_words+1,std::vector<int>(bor.tree.size(),0));
        //int v=0;
        std::unordered_set<int> curr_starts = std::unordered_set<int>();
        curr_starts.reserve(bor.tree.size());
        //curr_starts.insert(2);
        //curr_starts.insert(1);
        bool flag = false;
        for (int i=0;i<26;++i){
            if (bor.tree[0].to[i]==-1){
                if (bor.tree[0].term){
                    curr_starts.insert(0);
                    suspicious_words[1][0]+=1;
                }
                else{
                    curr_starts.insert(0);
                    not_suspicious_words[1][0]+=1;
                }
            }
            else{
                if (bor.tree[bor.tree[0].to[i]].term){
                    curr_starts.insert(bor.tree[0].to[i]);
                    suspicious_words[1][bor.tree[0].to[i]]+=1;
                }
                else{
                    curr_starts.insert(bor.tree[0].to[i]);
                    not_suspicious_words[1][bor.tree[0].to[i]]+=1;
                }
            }
        }
        std::unordered_set<int> new_starts;
        new_starts.reserve(bor.tree.size());
        for (int i=2;i<=length_of_words;++i){
            new_starts.clear();
            for(int v:curr_starts){
                for (int j=0; j<26;++j){
                    if (!(bor.tree[bor.go[v][j]].term) && bor.comp_links[bor.go[v][j]]==0){
                        suspicious_words[i][bor.go[v][j]]= (suspicious_words[i][bor.go[v][j]]+suspicious_words[i-1][v])%10000;
                        not_suspicious_words[i][bor.go[v][j]]= (not_suspicious_words[i][bor.go[v][j]]+not_suspicious_words[i-1][v])%10000;
                        new_starts.insert(bor.go[v][j]);
                    }
                    else{
                        suspicious_words[i][bor.go[v][j]]= (suspicious_words[i][bor.go[v][j]]+suspicious_words[i-1][v])%10000;
                        suspicious_words[i][bor.go[v][j]]= (suspicious_words[i][bor.go[v][j]]+not_suspicious_words[i-1][v])%10000;
                        new_starts.insert(bor.go[v][j]);
                    }
                }
            }
            curr_starts = new_starts;
        }
        int answer= 0;
        for (int i=0;i<bor.tree.size();++i){
            answer = (answer+suspicious_words[length_of_words][i])%10000;
        }
        std::cout<<answer;
    }
