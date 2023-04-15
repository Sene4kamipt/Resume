    #include<iostream>
    #include<string>
    #include<vector>
    #include<cstring>
     
    int getnum(char c){
        if(c == '$'){
            return 0;
        } else {
            return c - 'a' + 1;
        }
    }
     
    std::string s;
     
    struct Node{
        std::vector<int> to;
        int l, r;
        int par;
        int link;
        int64_t max_leaf;
        int64_t min_leaf;
        int64_t depth;
        Node(){
            to = std::vector<int> (27, -1);
            l = 0;
            r = 0;
            par = 0;
            link = 0;
            min_leaf = INT64_MAX;
            max_leaf = 0;
            depth = 0;
        }
        Node(int l, int r, int par, int link): l(l), r(r), par(par), link(link) {
            to = std::vector<int> (27, -1);
            min_leaf = INT64_MAX;
            max_leaf = 0;
            depth = 0;
        }
    };
     
    std::vector<Node> t;
    int cur_end, cur_pos, size, cur_sym;
    int64_t answer;
     
    void add (int c) {
    	while(true){
            if (t[cur_end].r < cur_pos) {
                if (t[cur_end].to[c] == -1) {
                    t[cur_end].to[c] = size;   
                    ++size;
                    t.emplace_back(cur_sym, s.size() - 1, cur_end, 0); 
                    cur_pos = t[cur_end].r + 1;  
                    cur_end = t[cur_end].link;  
                    continue; 
                }
                cur_end = t[cur_end].to[c]; 
                cur_pos = t[cur_end].l;
            }
            if (cur_pos == -1 || c == getnum(s[cur_pos])) {
                ++cur_pos; 
                break;
            } else {
                t.emplace_back(t[cur_end].l, cur_pos - 1, t[cur_end].par, 0);
                t.emplace_back(cur_sym, s.size() - 1, size, 0); 
                t[size].to[c] = size + 1;  
                t[size].to[getnum(s[cur_pos])] = cur_end;
                t[cur_end].l = cur_pos;  
                t[cur_end].par = size; 
                t[t[size].par].to[getnum(s[t[size].l])] = size;  
                size += 2;
     
                cur_end = t[t[size - 2].par].link;  
                cur_pos = t[size - 2].l;
     
                while(cur_pos <= t[size - 2].r) {  
                    cur_end = t[cur_end].to[getnum(s[cur_pos])];  
                    cur_pos += t[cur_end].r - t[cur_end].l + 1;
                }
                if (cur_pos == t[size - 2].r + 1){
                    t[size - 2].link = cur_end;
                } 
                else {
                    t[size - 2].link = size; 
                }
                cur_pos = t[cur_end].r - (cur_pos - t[size-2].r) + 2;  
            }
        }
    }
     
    void build() {
        cur_pos = 0;
    	cur_end = 0;
     
    	t.emplace_back(-1, -1, 0, 1);
        t.emplace_back(-1, -1, 0, 0);
        size = 2;
     
        for(int i = 0; i < 27; ++i){
            t[1].to[i] = 0;
        }
     
    	for (cur_sym = 0; cur_sym < s.size(); ++cur_sym){
    		add(getnum(s[cur_sym]));
        }
    }
     
    void dfs(int i, int64_t depth){
        t[i].depth = depth;
        int child_num = 0;
        for(int c = 0; c < 27; ++c){
            int j = t[i].to[c];
            if(j == -1){
                continue;
            }
            ++child_num;
            dfs(j, depth + t[j].r - t[j].l + 1);
            t[i].min_leaf = std::min(t[i].min_leaf, t[j].min_leaf + t[j].r - t[j].l + 1);
            t[i].max_leaf = std::max(t[i].max_leaf, t[j].max_leaf + t[j].r - t[j].l + 1);
        }
        if(child_num == 0){
            t[i].min_leaf = 0;
            t[i].max_leaf = 0;
        }
        if(child_num <= 1){
            return;
        }
        int64_t new_ans = t[i].depth * t[i].depth + t[i].depth + t[i].max_leaf - t[i].min_leaf;
        answer = std::max(answer, new_ans);
        return;
    }
     
    int main(){
     
        std::cin >> s;
        s += '$';
        build();
        
        answer = s.size() - 1;
        dfs(0, 0);
     
        std::cout<<answer;
     
    }
