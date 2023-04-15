    #include<iostream>
    #include<string>
    #include<vector>
    #include<cstring>
     
    int getnum(char c){
        return c - 'a';
    }
     
    std::string s;
     
    struct Node{
        std::vector<int> to;
        int l, r;
        int par;
        int link;
        Node(){
            to = std::vector<int> (26, -1);
            l = 0;
            r = 0;
            par = 0;
            link = 0;
        }
        Node(int l, int r, int par, int link): 
                l(l), r(r), par(par), link(link) {
            to = std::vector<int> (26, -1);
        }
    };
     
    std::vector<Node> t;
    int cur_end, cur_pos, size, cur_sym, cur_word;
     
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
        cur_word = 0;
     
    	t.emplace_back(-1, -1, 0, 1);
        t.emplace_back(-1, -1, 0, 0);
        size = 2;
     
        for(int i = 0; i < 26; ++i){
            t[1].to[i] = 0;
        }
     
    	for (cur_sym = 0; cur_sym < s.size(); ++cur_sym){
    		add(getnum(s[cur_sym]));
        }
    }
     
    bool find(std::string a, int flag){
        int v = 0;
        int p = 0;
        while (p < a.size()){
            if(t[v].to[getnum(a[p])] == -1){
                return false;
            }
            int new_v = t[v].to[getnum(a[p])];
            int l = t[new_v].l;
            int r = t[new_v].r;
            for(int j = l; j <= r; ++j){
                if(p >= a.size()){
                    return true;
                }
                if (j >= flag){
                    return false;
                }
                if(s[j] != a[p]){
                    return false;
                }
                ++p;
            }
            if (p >= a.size()){
                return true;
            }
            v = new_v;
        }
    }
     
    int main(){
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
     
        s ="";
        build();
     
        std::string a;
        char c;
        std::vector<std::string> reqs;
        std::vector<int> flags;
        while(std::cin>>c){
            if(c == '$'){
                break;
            }
            std::cin>>a;
            for(int i = 0; i < a.size(); ++i){
                if(a[i] < 'a'){
                    a[i] = a[i] - 'A' + 'a';
                }
            }
            if(c == '?'){
                flags.push_back(s.size());
                reqs.push_back(a);
            } else {
                s += a;
            }
        }
        flags.push_back(s.size());
        int cur_flag = 0;
        for (cur_sym = 0; cur_sym < s.size(); ++cur_sym){
            // while(cur_sym >= flags[cur_flag]){
            //     ++cur_flag;
            // }
    		add(getnum(s[cur_sym]));
        }
        for(int i = 0; i < reqs.size(); ++i){
            if(find(reqs[i], flags[i])){ //т е допустимо ходить по позициям до flags[i]
                std::cout<<"YES"<<'\n';
            } else {
                std::cout<<"NO"<<'\n';
            }
        }
    }
