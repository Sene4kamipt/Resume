    #include<iostream>
    #include<vector>
     
    void dfs(int start, std::vector<std::vector<int>>& graph, std::vector<bool>& used){
        used[start] = true;
        for(auto to: graph[start]){
            if(used[to]){
                continue;
            }
            dfs(to, graph, used);
        }
    }
     
    int main(){
     
        int first_size, second_size;
        std::cin>>first_size>>second_size;
        std::vector<std::vector<int>> graph_from_1_to_2 (first_size);
        std::vector<int> pairing (first_size);
        for(int i = 0; i < first_size; ++i){
            int cap, to;
            std::cin>>cap;
            for(int j = 0; j < cap; ++j){
                std::cin>>to;
                --to;
                graph_from_1_to_2[i].push_back(to);
            }
        }
        for(int i = 0; i < first_size; ++i){
            int to;
            std::cin>>to;
            --to;
            pairing[i] = to; // if -1 => not in pairing
        }
     
        std::vector<std::vector<int>>graph(first_size + second_size);
        for(int i = 0; i < first_size; ++i){
            for(int j: graph_from_1_to_2[i]){
                if(pairing[i] == j){
                    graph[first_size + j].push_back(i);
                } else {
                    graph[i].push_back(first_size + j);
                }
            }
        }
     
        std::vector<bool> used (first_size + second_size, false);
        for(int i = 0; i < first_size; ++i){
            if(pairing[i] != -1){
                continue;
            }
            dfs(i, graph, used);
        }
     
        std::vector<int> answer_1;
        std::vector<int> answer_2;
        for(int i = 0; i < first_size; ++i){
            if(!used[i]){
                answer_1.push_back(i);
            }
        }
        for(int i = 0; i < second_size; ++i){
            if(used[i + first_size]){
                answer_2.push_back(i);
            }
        }
        std::cout<<answer_1.size() + answer_2.size()<<'\n';
        std::cout<<answer_1.size()<<' ';
        for(int i : answer_1){
            std::cout<<i + 1<<' ';
        }
        std::cout<<'\n';
        std::cout<<answer_2.size()<<' ';
        for(int i : answer_2){
            std::cout<<i + 1<<' ';
        }
     
     
    }
