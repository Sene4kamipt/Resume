#include <iostream>
    #include<vector>
    #include<string>
    #include<cstring>
    #include<algorithm>
    int main(){
        std::string name;
        std::cin>>name;
        name+="#";
        const int cnt_size = std::max(name.size(),size_t(53));
        std::vector<int> cnt(cnt_size);
        std::vector<int>sorted_str(name.size());
        std::vector<int>classes_of_eq(name.size());
        for (int i=0; i<name.size();++i){
            if (name[i]=='#'){
                ++cnt[0];
            }
            else{
                if (name[i]>='a'){
                    ++cnt[name[i]-'a'+26+1];
                }
                else{
                    ++cnt[name[i]-'A'+1];
                }
            }
        }
        for (int i=1;i<cnt_size;++i){
            cnt[i]+=cnt[i-1];
        }
        for (int i = name.size()-1;i>=0;--i){
            if(name[i]=='#'){
                sorted_str[--cnt[0]]= name.size()-1;
            }
            else{
                if (name[i]>='a'){
                    sorted_str[--cnt[name[i]-'a'+27]]=i;
                }
                else{
                    sorted_str[--cnt[name[i]-'A'+1]]=i;
                }
            }
        }
        classes_of_eq[sorted_str[0]]=0;
        for (int i =1;i<name.size();++i){
            classes_of_eq[sorted_str[i]] = classes_of_eq[sorted_str[i-1]];
            if (name[sorted_str[i]]!=name[sorted_str[i-1]]){
                ++classes_of_eq[sorted_str[i]];
            }
        }
        int curr_2 = 1;
        std::vector<int>new_sorted_str(name.size());
        std::vector<int>new_classes_of_eq(name.size());
        while (curr_2<name.size()){
            for (int i=0; i<name.size();++i){
                new_sorted_str[i] = sorted_str[i]-curr_2;
                if (new_sorted_str[i]<0){
                    new_sorted_str[i]+=name.size();
                }
            }
            cnt = std::vector<int>(cnt_size,0);
            for(int i=0;i<name.size();++i){
                ++cnt[classes_of_eq[i]];
            }
            for (int i=1;i<cnt_size;++i){
                cnt[i]+=cnt[i-1];
            }
            for (int i =name.size()-1;i>=0;--i){
                sorted_str[--cnt[classes_of_eq[new_sorted_str[i]]]]=new_sorted_str[i];
            }
            new_classes_of_eq[sorted_str[0]]=0;
            for (int i=1;i<name.size();++i){
                new_classes_of_eq[sorted_str[i]] = new_classes_of_eq[sorted_str[i-1]];
                if(classes_of_eq[sorted_str[i]]!=classes_of_eq[sorted_str[i-1]]){
                    new_classes_of_eq[sorted_str[i]]++;
                }
                else{
                    if(classes_of_eq[(sorted_str[i]+curr_2)%name.size()]!=classes_of_eq[(sorted_str[i-1]+curr_2)%name.size()]){
                        new_classes_of_eq[sorted_str[i]]++;
                    }
                }
            }
            for(int i=0;i<name.size();++i){
                classes_of_eq[i]=new_classes_of_eq[i];
            }
            curr_2*=2;
        }
        std::vector<int> pos(name.size());
        std::vector<int>lcp(name.size());
        for (int i=0;i<name.size();++i){
            pos[sorted_str[i]]=i;
        }
        int k=0;
        for (int i=0;i<name.size();++i){
            k=std::max(k-1,0);
            if (pos[i]==name.size()-1){
                continue;
            }
            int j = sorted_str[pos[i]+1];
            while (name[i+k]==name[j+k]){
                ++k;
            }
            lcp[pos[i]]=k;
        }
        int64_t answer = 0;
        for (int i=0;i<name.size();++i){
            answer+=(name.size()-sorted_str[i] - (i==0?0:lcp[i-1])-1);
        }
        int64_t q;
        std::cin>>q;
        if (q >= answer) {
            for (int i = sorted_str[name.size() - 1]; i < name.size() - 1; ++i) {
                std::cout << name[i];
            }
            return 0;
        }
 
        int summ = 0;
        int pos_word = -1;
        while (summ < q) {
            ++pos_word;
            summ += (name.size() - sorted_str[pos_word] - (pos_word != 0) * lcp[pos_word - 1] - 1);
        }
        for (int i = sorted_str[pos_word]; i < name.size() - 1 + q - summ; ++i) {
            std::cout << name[i];
        }
    }
